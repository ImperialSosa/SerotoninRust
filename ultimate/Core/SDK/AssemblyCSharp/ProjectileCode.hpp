#pragma once
#include "AssemblyCSharp.hpp"
#include "../../Features/Features/Features.hpp"

inline float GetHitDist(AssemblyCSharp::Projectile* pr) {
	float travel = pr->traveledTime();

	float num6 = (travel + 2 / 60 + 0.03125f) * 1.5f;
	float maxdist = 0.1f + num6 * 5.5f;
	return maxdist;
}


inline bool heli_magic(AssemblyCSharp::Projectile* pr, Vector3 point) {
	auto distt = GetHitDist(pr);
	auto target = AssemblyCSharp::BasePlayer::GetAimbotTarget(point, distt);
	if (pr->IsAlive() && target.m_player && !target.m_team || target.m_heli) {
		if (!AssemblyCSharp::IsVisible(target.m_position, point)) {
			return false;
		}

		auto ht = pr->hitTest();
		ht->DidHit() = true;
		ht->HitEntity() = target.m_player;
		UnityEngine::Transform* Transform;

		if (!target.m_heli) {
			Transform = target.m_player->get_bone_transform(target.m_bone);
		}
		else
		{
			Transform = target.m_player->get_bone_transform(19);
		}

		if (!Transform)
			return false;

		ht->HitTransform() = Transform;

		Vector3 hitpoint = Transform->InverseTransformPoint(point);
		ht->HitPoint() = hitpoint;

		*reinterpret_cast<Vector3*>(ht + 0x14) = point;

		AssemblyCSharp::HitTest* test = (AssemblyCSharp::HitTest*)ht;
		bool result = pr->DoHit(test, point, Vector3());
		//Sphere(point, 0.015f, col(1, 0, 0, 1), 20, true);
		return true;
	}
	return false;
}




inline bool bullet_tp(AssemblyCSharp::Projectile* instance, Vector3 NextCurrentPosition, Vector3 CurrentPosition, Vector3 CurrentVelocity, float deltaTime)
{
	if (!instance)
		return false;

	if (Vector3().IsNaNOrInfinity(NextCurrentPosition))
	{
		return false;
	}

	if (Vector3().IsNaNOrInfinity(CurrentPosition))
	{
		return false;
	}

	if (Vector3().IsNaNOrInfinity(CurrentVelocity))
	{
		return false;
	}

	if (RPC_Counter.Calculate() > 100)
	{
		return false;
	}

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return false;

	auto m_target = AssemblyCSharp::BasePlayer().GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(m_target.m_player))
		return false;

	if (m_target.m_heli)
		return false;


	auto Line = NextCurrentPosition - CurrentPosition;
	auto LineLength = Line.Magnitude();
	Line.UnityNormalize();

	auto CenterPosition = m_target.m_player->PivotPoint() + Vector3(0.f, 0.9f, 0.f);
	auto v = CenterPosition - CurrentPosition;
	auto d = v.Dot(Line);

	if (d < 0.0f)
	{
		d = 0.0f;
	}
	else if (d > LineLength)
	{
		d = LineLength;
	}

	auto OriginalClosestPointOnLine = CurrentPosition + Line * d;
	auto ClosestPointOnLine = OriginalClosestPointOnLine;

	auto ClosestPoint = m_target.m_player->ClosestPoint(ClosestPointOnLine);
	auto OriginalDistance = m_target.m_player->Distance(ClosestPointOnLine);
	auto Distance = OriginalDistance;

	Vector3 HitPointWorld = ClosestPoint;

	if (Distance > 3.5f)
	{
		return false;
	}


	if (Distance > 1.2f)
	{
		auto endPositionTrajectoryUsage = Distance - 1.2f + 0.01f;
		auto amountNeeded = endPositionTrajectoryUsage / Distance;
		auto direction = HitPointWorld - ClosestPointOnLine;
		auto newPosition = ClosestPointOnLine + (direction * amountNeeded);

		if (ClosestPointOnLine.Distance(newPosition) > 1.f || !AssemblyCSharp::IsVisible_2(ClosestPointOnLine, newPosition, 10551296, 0.f))
			return false;

		ClosestPointOnLine = newPosition;
		Distance = m_target.m_player->Distance(ClosestPointOnLine);
	}

	if (Distance > 1.f)
	{
		auto playerDistanceUsage = minm(0.19f, Distance - 1.f);
		auto amountNeeded = 1.f - playerDistanceUsage / Distance;
		auto direction = HitPointWorld - ClosestPointOnLine;
		auto newPosition = ClosestPointOnLine + (direction * amountNeeded);

		HitPointWorld = newPosition;
	}

	if (!AssemblyCSharp::IsVisible_2(ClosestPointOnLine, HitPointWorld, 10551296, 0.f) || !AssemblyCSharp::IsVisible_2(CurrentPosition, OriginalClosestPointOnLine, 10551296, 0.f) ||
		!AssemblyCSharp::IsVisible_2(OriginalClosestPointOnLine, ClosestPointOnLine, 10551296, 0.f) || !AssemblyCSharp::IsVisible_2(CenterPosition, HitPointWorld, 10551296, 0.f))
	{
		return false;
	}

	static uintptr_t PlayerProjectileUpdateClass = 0; if (!PlayerProjectileUpdateClass) PlayerProjectileUpdateClass = (uintptr_t)CIl2Cpp::FindClass(XS("ProtoBuf"), XS("PlayerProjectileUpdate"));

	instance->previousPosition() = instance->currentPosition();
	instance->currentPosition() = OriginalClosestPointOnLine;
	instance->traveledDistance() += instance->previousPosition().Distance(instance->currentPosition());
	instance->traveledTime() += instance->previousPosition().Distance(instance->currentPosition()) / CurrentVelocity.Length();

	if (ProtoBuf::PlayerProjectileUpdate* playerProjectileUpdate = reinterpret_cast<ProtoBuf::PlayerProjectileUpdate*>(CIl2Cpp::il2cpp_object_new((void*)PlayerProjectileUpdateClass)))
	{
		playerProjectileUpdate->projectileID() = instance->projectileID();
		playerProjectileUpdate->travelTime() = instance->traveledTime();
		playerProjectileUpdate->curVelocity() = instance->currentVelocity();
		playerProjectileUpdate->curPosition() = instance->currentPosition();

		instance->owner()->SendProjectileUpdate(playerProjectileUpdate);
		RPC_Counter.Increment();

		if (m_settings::Thickbullet_Arrows)
		{
			UnityEngine::DDraw().Arrow(instance->previousPosition(), instance->currentPosition(), 0.1f, Color(0.f, 1.f, 0.f, 1.f), 30.f);
		}
	}

	instance->previousPosition() = instance->currentPosition();
	instance->currentPosition() = ClosestPointOnLine;
	instance->traveledDistance() += instance->previousPosition().Distance(instance->currentPosition());
	instance->traveledTime() += instance->previousPosition().Distance(instance->currentPosition()) / CurrentVelocity.Length();

	if (ProtoBuf::PlayerProjectileUpdate* playerProjectileUpdate = reinterpret_cast<ProtoBuf::PlayerProjectileUpdate*>(CIl2Cpp::il2cpp_object_new((void*)PlayerProjectileUpdateClass)))
	{
		playerProjectileUpdate->projectileID() = instance->projectileID();
		playerProjectileUpdate->travelTime() = instance->traveledTime();
		playerProjectileUpdate->curVelocity() = instance->currentVelocity();
		playerProjectileUpdate->curPosition() = instance->currentPosition();

		instance->owner()->SendProjectileUpdate(playerProjectileUpdate);
		RPC_Counter.Increment();

		if (m_settings::Thickbullet_Arrows)
		{
			UnityEngine::DDraw().Arrow(instance->previousPosition(), instance->currentPosition(), 0.1f, Color(1.f, 0.f, 0.f, 1.f), 30.f);
		}
	}



	AssemblyCSharp::HitTest* hTest = instance->hitTest();
	if (!hTest)
	{
		auto g_hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
		hTest = (AssemblyCSharp::HitTest*)CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);
	}

	if (HitPointWorld == instance->currentPosition())
	{
		HitPointWorld.y += 0.01f;
	}

	UnityEngine::Ray ray = UnityEngine::Ray(instance->currentPosition(), (HitPointWorld - instance->currentPosition()).Normalized());

	hTest->MaxDistance() = 1000.0f;
	hTest->AttackRay() = ray;
	hTest->DidHit() = true;
	hTest->HitTransform() = m_target.m_player->get_bone_transform(m_target.m_bone);
	hTest->HitEntity() = m_target.m_player;
	hTest->HitPoint() = hTest->HitTransform()->InverseTransformPoint(HitPointWorld);
	hTest->HitNormal() = hTest->HitTransform()->InverseTransformDirection(HitPointWorld);
	hTest->damageProperties() = instance->damageProperties();
	hTest->HitMaterial() = CIl2Cpp::il2cpp_string_new(XS("Flesh"));

	if (m_settings::Thickbullet_Arrows)
	{
		UnityEngine::DDraw().Arrow(instance->currentPosition(), HitPointWorld, 0.1f, Color(0.f, 0.f, 1.f, 1.f), 30.f);
		UnityEngine::DDraw().Arrow(HitPointWorld, m_target.m_player->ClosestPoint(HitPointWorld), 0.1f, Color(1.f, 1.f, 0.f, 1.f), 30.f);
	}

	instance->DoHit(hTest, hTest->HitPoint(), hTest->HitNormal()); //hTest->HitNormal()
	return true;
}

inline void do_movement(float delta_time, AssemblyCSharp::Projectile* instance)
{
	if (!instance)
		return;

	Vector3 a = instance->currentVelocity() * delta_time;
	float magnitude = a.Length();
	float num2 = 1 / magnitude;
	Vector3 vec2 = a * num2;
	bool flag = false;

	Vector3 vec3 = instance->currentPosition() + vec2 * magnitude;
	float num3 = instance->traveledTime() + delta_time;

	auto ht = instance->hitTest();
	if (!ht) {
		/*HitTest_TypeInfo*/

		auto g_hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
		auto g_hit_test = CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);
		ht = (AssemblyCSharp::HitTest*)g_hit_test;
		instance->hitTest() = (AssemblyCSharp::HitTest*)g_hit_test;
	}
	UnityEngine::Ray ray = UnityEngine::Ray(instance->currentPosition(), vec2);
	ht->AttackRay() = ray;
	ht->MaxDistance() = magnitude;
	AssemblyCSharp::BasePlayer* ow = instance->owner();
	ht->ignoreEntity() = ow;
	ht->Radius() = 0.f;
	ht->Forgiveness() = 0.2f;
	if (!instance->owner() || ow->userID() == instance->owner()->userID()) {
		ht->type() = 0x2;
	}
	else ht->type() = 0x1; //Type	`

	if (instance->sourceWeaponPrefab()) {
		ht->BestHit() = true;
		ht->damageProperties() = instance->damageProperties();
	}

	ht = instance->hitTest();

	ht->MaxDistance() = 0.f;


	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto m_target = AssemblyCSharp::BasePlayer().GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(m_target.m_player))
		return;


	if (m_target.m_player->mounted() || m_target.m_heli)
	{
		if (heli_magic(instance, instance->currentPosition()))
		{
			RPC_Counter.Reset();
			instance->integrity() = (0);
			flag = true;
		}
	}
	else
	{
		if (bullet_tp(instance, vec3, instance->currentPosition(), instance->currentVelocity(), delta_time))
		{
			RPC_Counter.Reset();
			instance->integrity() = (0);
			flag = true;
		}

	}

	if (!flag && instance->IsAlive()) {
		float magnitude3 = (vec3 - instance->currentPosition()).Length();
		float num6 = magnitude3 * num2 * delta_time;
		instance->traveledDistance() = (instance->traveledDistance() + magnitude3);
		instance->traveledTime() = (instance->traveledTime() + num6);
		instance->currentPosition() = (vec3);
	}
}


inline void do_velocity_update(float delta_time, AssemblyCSharp::Projectile* instance)
{
	if (!instance)
		return;

	Vector3 gr = UnityEngine::Physics::get_gravity();
	Vector3 tr = (gr * instance->gravityModifier() * delta_time);
	instance->currentVelocity() = (instance->currentVelocity() + tr);
	Vector3 dr = (instance->currentVelocity() * instance->drag() * delta_time);
	instance->currentVelocity() = (instance->currentVelocity() - dr);
}