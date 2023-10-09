#pragma once
#include "AssemblyCSharp.hpp"


namespace O::Projectile {
	constexpr auto initialVelocity = 0x18;
	constexpr auto drag = 0x24;
	constexpr auto gravityModifier = 0x28;
	constexpr auto thickness = 0x2C;
	constexpr auto initialDistance = 0x30;
	constexpr auto remainInWorld = 0x34;
	constexpr auto stickProbability = 0x38;
	constexpr auto breakProbability = 0x3C;
	constexpr auto conditionLoss = 0x40;
	constexpr auto ricochetChance = 0x44;
	constexpr auto penetrationPower = 0x48;
	constexpr auto waterIntegrityLoss = 0x4C;
	constexpr auto damageProperties = 0x50;
	constexpr auto damageDistances = 0x58;
	constexpr auto createDecals = 0x80;
	constexpr auto doDefaultHitEffects = 0x81;
	constexpr auto flybySound = 0x88;
	constexpr auto flybySoundDistance = 0x90;
	constexpr auto closeFlybySound = 0x98;
	constexpr auto closeFlybyDistance = 0xA0;
	constexpr auto tumbleSpeed = 0xA4;
	constexpr auto tumbleAxis = 0xA8;
	constexpr auto swimScale = 0xB4;
	constexpr auto swimSpeed = 0xC0;
	constexpr auto owner = 0xD0;
	constexpr auto sourceWeaponPrefab = 0xD8;
	constexpr auto sourceProjectilePrefab = 0xE0;
	constexpr auto mod = 0xE8;
	constexpr auto projectileID = 0xF0;
	constexpr auto seed = 0xF4;
	constexpr auto clientsideEffect = 0xF8;
	constexpr auto clientsideAttack = 0xF9;
	constexpr auto integrity = 0xFC;
	constexpr auto maxDistance = 0x100;
	constexpr auto modifier = 0x104;
	constexpr auto invisible = 0x114;
	constexpr auto currentVelocity = 0x118;
	constexpr auto currentPosition = 0x124;
	constexpr auto traveledDistance = 0x130;
	constexpr auto traveledTime = 0x134;
	constexpr auto launchTime = 0x138;
	constexpr auto sentPosition = 0x13C;
	constexpr auto previousPosition = 0x148;
	constexpr auto previousVelocity = 0x154;
	constexpr auto previousTraveledTime = 0x160;
	constexpr auto isUnderwater = 0x164;
	constexpr auto isRicochet = 0x165;
	constexpr auto isRetiring = 0x166;
	constexpr auto flybyPlayed = 0x167;
	constexpr auto wasFacingPlayer = 0x168;
	constexpr auto flybyPlane = 0x16C;
	constexpr auto flybyRay = 0x17C;
	constexpr auto cleanupAction = 0x198;
	constexpr auto hitTest = 0x1A0;
	constexpr auto swimRandom = 0x1A8;
	constexpr auto _waterMaterialID = 0x4;
	constexpr auto cachedWaterString = 0x8;
};

template<typename t>
t read(uintptr_t addr) {
	if (addr < 0xffffff)
		return t();
	if (addr > 0x7fffffff0000)
		return t();

	return *reinterpret_cast<t*>(addr);
}

template<typename t>
bool write(uintptr_t addr, t buffer) {
	*reinterpret_cast<t*>(addr) = buffer;
	return true;
}


#define safe_read(Addr, Type) read<Type>((DWORD64)Addr)
#define safe_write(Addr, Data, Type) write<Type>((DWORD64)Addr, Data);

class Projectile_c : AssemblyCSharp::Projectile {
public:
	IL2CPP_CLASS("Projectile");
	IL2CPP_FIELD(float, thickness);
	IL2CPP_FIELD(Vector3, currentPosition);
	IL2CPP_FIELD(Vector3, sentPosition);

	IL2CPP_FIELD(Vector3, currentVelocity);
	IL2CPP_FIELD(Vector3, initialVelocity);
	IL2CPP_FIELD(Vector3, previousPosition);
	IL2CPP_FIELD(Vector3, previousVelocity);
	IL2CPP_FIELD(AssemblyCSharp::HitTest*, hitTest);
	IL2CPP_FIELD(float, traveledTime);
	IL2CPP_FIELD(float, traveledDistance);
	IL2CPP_FIELD(float, gravityModifier);
	IL2CPP_FIELD(float, drag);
	IL2CPP_FIELD(float, closeFlybyDistance);
	IL2CPP_FIELD(float, tumbleSpeed);
	IL2CPP_FIELD(float, maxDistance);
	IL2CPP_FIELD(bool, createDecals);
	IL2CPP_FIELD(Vector3, tumbleAxis);
	IL2CPP_FIELD(float, previousTraveledTime);
	IL2CPP_FIELD(float, launchTime);
	IL2CPP_FIELD(Vector3, swimScale);
	IL2CPP_FIELD(float, penetrationPower);
	IL2CPP_FIELD(int, seed);
	IL2CPP_FIELD(float, flybySoundDistance);
	IL2CPP_FIELD(float, swimRandom);
	IL2CPP_FIELD(Vector3, swimSpeed);

	IL2CPP_FIELD(int, projectileID);
	IL2CPP_FIELD(float, initialDistance);
	IL2CPP_FIELD(float, integrity);
	IL2CPP_FIELD(AssemblyCSharp::BasePlayer*, owner);
	IL2CPP_FIELD(bool, isRicochet);
	IL2CPP_FIELD(AssemblyCSharp::AttackEntity*, sourceWeaponPrefab);
	IL2CPP_FIELD(AssemblyCSharp::DamageProperties*, damageProperties);
	IL2CPP_FIELD(float, ricochetChance);

	bool IsAlive() {
		return (this->integrity() > 0.001f && this->traveledDistance() < this->maxDistance());
	}

	struct TraceInfo {

		bool valid; // 0x0
		float distance; // 0x4
		DWORD64 entity; // 0x8   //BasePlayer
		Vector3 point; // 0x10
		Vector3 normal; // 0x1C
		DWORD64/*Transform*/ bone; // 0x28
		DWORD64 material; // 0x30
		unsigned int partID; // 0x38
		DWORD64 collider; // 0x40
	};

	inline Vector3 SimulateProjectilezzzzz(Vector3& position, Vector3& velocity, float& partialTime, float travelTime, Vector3 gravity, float drag)
	{
		float num = 0.03125f;
		Vector3 origin = position;
		if (partialTime > 0)
		{
			float num2 = num - partialTime;
			if (travelTime < num2)
			{
				origin = position;
				position += velocity * travelTime;
				partialTime += travelTime;
				return origin;
			}
			origin = position;
			position += velocity * num2;
			velocity += gravity * num;
			velocity -= velocity * drag * num;
			travelTime -= num2;
		}

		int num3 = int(travelTime / num);

		for (int i = 0; i < num3; i++)
		{
			origin = position;
			position += velocity * num;
			velocity += gravity * num;
			velocity -= velocity * drag * num;
		}
		partialTime = travelTime - num * (float)num3;
		if (partialTime > 0)
		{
			origin = position;
			position += velocity * partialTime;
		}
		return origin;
	}

	inline Vector3 Simulatezzzzz(bool returnvelocity, bool sendtoserver) {
		Vector3 pos = sentPosition(); Vector3 prev = tumbleAxis(); float part = tumbleSpeed(); float travel = maxx(traveledTime() - closeFlybyDistance(), 0);

		Vector3 gr = UnityEngine::Physics::get_gravity(); //static Vector3 get_gravity();


		Vector3 origin = SimulateProjectilezzzzz(pos, prev, part, travel, gr * gravityModifier(), drag());

		if (sendtoserver) {
			sentPosition() = (pos);
			tumbleAxis() = (prev);
			tumbleSpeed() = (part);
			closeFlybyDistance() = (traveledTime());
		}

		if (returnvelocity) return prev;

		return origin;
	}

	bool BulletTP(AssemblyCSharp::Projectile* instance, Vector3 NextCurrentPosition, Vector3 CurrentPosition, Vector3 CurrentVelocity, float deltaTime)
	{

		if (RPC_Counter.Calculate() > 100)
		{
			return false;
		}

		auto camera = UnityEngine::Camera::get_main();
		if (!camera)
			return false;


		auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (!m_target.m_player)
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

		if (m_target.m_player->mounted())
		{
			if (Distance > 7.5f)
			{
				return false;
			}
		}
		else
		{
			if (Distance > 3.5f)
			{
				return false;
			}
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
			auto g_hit_test_class = AssemblyCSharp::HitTest::StaticClass();
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

	inline float GetHitDist() {
		float travel = traveledTime();

		float num6 = (travel + 2 / 60 + 0.03125f) * 1.5f;
		float maxdist = 0.1f + num6 * 5.5f;
		return maxdist;
	}


	inline bool DoFatBulletHit(Projectile_c* pr, Vector3 point) {
		float maxDist = GetHitDist();
		auto target = AssemblyCSharp::BasePlayer::GetAimbotTarget(point, maxDist);

		if (pr->IsAlive() && target.m_player && !target.m_team || target.m_heli) {
			if (!AssemblyCSharp::IsVisible(target.m_position, point)) {
				return false;
			}

			auto ht = hitTest();
			safe_write(ht + 0x66, true, bool); //DidHit
			safe_write(ht + 0x88, (DWORD64)target.m_player, DWORD64); //HitEntity
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

			safe_write(ht + 0xB0, (uintptr_t)Transform, DWORD64);

			Vector3 hitpoint = Transform->InverseTransformPoint(point);
			safe_write(ht + 0x90, hitpoint, Vector3); //hitPoint
			safe_write(ht + 0x14, point, Vector3);


			AssemblyCSharp::HitTest* test = (AssemblyCSharp::HitTest*)ht;
			bool result = pr->DoHit(test, point, Vector3());
			//Sphere(point, 0.015f, col(1, 0, 0, 1), 20, true);
			return true;
		}
		return false;
	}

	inline void UpdateHitTest(TraceInfo info) {
		auto ht = hitTest();

		safe_write(ht + 0x66, true, bool); //DidHit
		safe_write(ht + 0x88, info.entity, DWORD64); //HitEntity
		safe_write(ht + 0xA8, info.distance, float); //HitDistance

		if (info.material != 0) {
			FPSystem::String* material = (AssemblyCSharp::AssetNameCache::GetName(info.material));
			safe_write(ht + 0xC0, material, FPSystem::String*); //HitMaterial  
		}

		safe_write(ht + 0xB8, info.partID, unsigned int); //HitPart
		safe_write(ht + 0xB0, info.bone, DWORD64); //HitTransform
		safe_write(ht + 0x90, info.point, Vector3); //HitPoint
		safe_write(ht + 0x9C, info.normal, Vector3); //HitNormal
		safe_write(ht + 0x78, info.collider, DWORD64); //collider


		auto go = (info.collider) ? reinterpret_cast<UnityEngine::Component*>(info.collider)->get_gameObject() : reinterpret_cast<UnityEngine::Component*>(info.bone)->get_gameObject();

		safe_write(ht + 0x70, go, UnityEngine::GameObject*); //gameObject
		if (info.bone != 0) {

			auto htt = safe_read(ht + 0xB0, UnityEngine::Transform*);
			Vector3 hitpoint = htt->InverseTransformPoint(info.point);
			safe_write(ht + 0x90, hitpoint, Vector3); //hitPoint

			Vector3 normalpoint = htt->InverseTransformDirection(info.normal);
			safe_write(ht + 0x9C, normalpoint, Vector3); //HitNormal
		}

	}
	inline bool DoHit2(Projectile_c* pr, DWORD64 ht, Vector3 point, Vector3 normal, TraceInfo info, bool& exit) {
		bool result = false;
		if (!IsAlive())
			return result;

		auto material = info.material != 0 ? AssemblyCSharp::AssetNameCache::GetName(info.material)->c_str() : (XS(L"generic"));

		bool canIgnore = AssemblyCSharp::IsVisible(sentPosition(), currentPosition() + currentVelocity().Normalized() * 0.01f);
		if (!canIgnore) {
			integrity() = (0);
			return true;
		}

		float org;
		if (canIgnore) {
			Vector3 attackStart = Simulatezzzzz(false, true);

			safe_write(ht + 0x14, UnityEngine::Ray(attackStart, Vector3()), UnityEngine::Ray);
		}

		if (canIgnore && String::wcscmp(material, XS(L"Flesh"))) {
			DWORD64 Tra = safe_read(ht + 0xB0, DWORD64);
			if (Tra) {
				auto st = XS("head");
				reinterpret_cast<UnityEngine::Transform*>(Tra)->set_name(st);
			}

			result = pr->DoHit((AssemblyCSharp::HitTest*)ht, point, normal);
			sentPosition() = (currentPosition());

		}
		return result;
	}

	inline bool DoMovement(float deltaTime, Projectile_c* pr) {
		if (!pr)
			return false;

		if (!this)
			return false;

		if (!pr->isAuthoritative())
			return false;


		if (pr->swimScale() != Vector3(0.f,0.f,0.f))
		{
			if (pr->swimRandom() == 0.f)
			{
				pr->swimRandom() = UnityEngine::Random::Range(0.f, 20.f);
			}
			float num = UnityEngine::Time::get_time() + pr->swimRandom();
			Vector3 vector = Vector3(Math::sinf(num * pr->swimSpeed().x) * pr->swimScale().x, Math::cosf(num * pr->swimSpeed().y) * pr->swimScale().y, Math::cosf(num * pr->swimSpeed().z) * pr->swimScale().z);
			vector = pr->get_transform()->InverseTransformDirection(vector);
			pr->currentVelocity() += vector;
		}

		Vector3 a = currentVelocity() * deltaTime;
		float magnitude = a.Length();
		float num2 = 1 / magnitude;
		Vector3 vec2 = a * num2;
		bool flag = false;

		Vector3 vec3 = currentPosition() + vec2 * magnitude;
		float num3 = traveledTime() + deltaTime;

		float v38 = deltaTime + this->traveledTime();

		auto ht = hitTest();
		if (!ht) {
			/*HitTest_TypeInfo*/

			auto g_hit_test_class = AssemblyCSharp::HitTest::StaticClass();
			auto g_hit_test = CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);
			ht = (AssemblyCSharp::HitTest*)g_hit_test;
			hitTest() = (AssemblyCSharp::HitTest*)g_hit_test;
		}
		UnityEngine::Ray ray = UnityEngine::Ray(currentPosition(), vec2);
		ht->AttackRay() = ray;
		ht->MaxDistance() = magnitude;
	
		AssemblyCSharp::BasePlayer* ow = this->owner();
		ht->ignoreEntity() = ow;
		ht->Radius() = 0.f;
		ht->Forgiveness() = 0.5f;


		if (!pr->owner() || ow->userID() == pr->owner()->userID()) {
			ht->type() = 0x2;
		}
		else ht->type() = 0x1; //Type	`

		if (sourceWeaponPrefab()) {
			ht->BestHit() = true;
			ht->damageProperties() = damageProperties();
		}
	OFFSET:
		typedef DWORD64(__stdcall* Unknown)(DWORD64);
		DWORD64 st = safe_read(m_game_assembly + 53648824, DWORD64); //Method$Facepunch.Pool.GetList\u003CTraceInfo\u003E() address
		if (!st)
		{
			goto OFFSET;
		}

		Unknown get_list = (Unknown)(m_game_assembly + 18733264);//Method$Facepunch.Pool.GetList\u003CTraceInfo\u003E() MethodAddress
		if (!get_list)
		{
			goto OFFSET;
		}

		DWORD64 rs = get_list(st);
		if (!rs)
		{
			goto OFFSET;
		}


		int layerMask = 1270440721;

		if (m_settings::PierceMaterials)
		{
			layerMask &= ~256; //Deployed
			layerMask &= ~1; //Default
			layerMask &= ~1073741824; //tree
			layerMask &= ~16; //Water
			layerMask &= ~134217728; //Vehicle_Large
			layerMask &= ~32768; //Vehicle_World
			layerMask &= ~8192; //Vehicle_Detailed
			layerMask &= ~1073741824; //tree
		}

		AssemblyCSharp::GameTrace::TraceAll(ToAddress(ht), rs, layerMask /*mask*/);

		static bool traceall = false;


		ht = hitTest();
		ht->MaxDistance() = 0.f;


		int size = safe_read(rs + 0x18, int);

		DWORD64 lst = safe_read(rs + 0x10, DWORD64);

		auto camera = UnityEngine::Camera::get_main();
		if (!camera)
			return false;

		auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (!m_target.m_player)
			return false;

		float real_travel_time = this->traveledTime();
		Vector3 vel = this->currentVelocity();

		if (m_target.m_player->mounted() || m_target.m_heli)
		{
			if (DoFatBulletHit(pr, currentPosition()))
			{
				RPC_Counter.Reset();

				this->currentVelocity() = (vel);
				this->traveledTime() = (real_travel_time);
				integrity() = (0);
				flag = true;
				return false;
			}
		}
		else
		{
			if (BulletTP(this, vec3, currentPosition(), currentVelocity(), deltaTime))
			{
				RPC_Counter.Reset();
				integrity() = (0);
				flag = true;
				//this->Retire();
				return false;
			}
		}

		for (int i = 0; i < size && this->IsAlive() && !flag; i++) {
			TraceInfo Trace = safe_read(lst + 0x20 + (i * sizeof(TraceInfo)), TraceInfo);
			if (Trace.valid) {
				this->UpdateHitTest(Trace);

				Vector3 vec4 = reinterpret_cast<AssemblyCSharp::HitTest*>(ht)->HitPointWorld(); //Vector3 HitPointWorld();
				Vector3 normal = reinterpret_cast<AssemblyCSharp::HitTest*>(ht)->HitNormalWorld(); //Vector3 HitNormalWorld();


				float magnitude2 = (vec4 - currentPosition()).Length();
				float num5 = magnitude2 * num2 * deltaTime;

				traveledDistance() = (traveledDistance() + magnitude2);
				traveledTime() = (traveledTime() + num5);
				currentPosition() = (vec4);

				bool exit = false;
				if (this->DoHit2(pr, ToAddress(ht), vec4, normal, Trace, exit)) {
					flag = true;
				}

				if (exit) {
					return true;
				}
			}
		}

		if (this->integrity() > 0.001 && this->maxDistance() > this->traveledDistance())
		{
			if (flag && traveledTime() < num3)
			{
				DoMovement(num3 - traveledTime(), this);
				return false;
			}


			if (!flag && this->IsAlive()) {
				float magnitude3 = (vec3 - currentPosition()).Length();
				float num6 = magnitude3 * num2 * deltaTime;
				traveledDistance() = (traveledDistance() + magnitude3);
				traveledTime() = (traveledTime() + num6);
				currentPosition() = (vec3);
			}
		}

		

		return false;
	}
	inline void DoVelocityUpdate(float deltaTime) {
		if (!this)
			return;

		Vector3 gr = UnityEngine::Physics::get_gravity(); //static Vector3 get_gravity();

		Vector3 tr = (gr * gravityModifier() * deltaTime);
		currentVelocity() = (currentVelocity() + tr);

		Vector3 dr = (currentVelocity() * drag() * deltaTime);
		currentVelocity() = (currentVelocity() - dr);
	}
};
