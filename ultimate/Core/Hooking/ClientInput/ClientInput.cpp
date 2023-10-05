#include "../hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"
#include "../../Features/Visuals/Visuals.hpp"
#include "../../Features/EyeHack/EyeHack.hpp"

float flyhackDistanceVertical = 0.f;
float flyhackDistanceHorizontal = 0.f;
float flyhackPauseTime;

bool TestFlying(AssemblyCSharp::BasePlayer* _This, Vector3 oldPos, Vector3 newPos)
{
	if (!InGame)
		return false;

	if (auto LocalPlayer = _This)
	{
		flyhackPauseTime = maxx(0.f, flyhackPauseTime - UnityEngine::Time::get_fixedDeltaTime());
		bool inAir = false;

		float radius = LocalPlayer->GetRadius();
		float height = LocalPlayer->GetHeight(false);

		Vector3 vector = (oldPos + newPos) * 0.5f;
		Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
		Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
		float radius2 = radius - 0.05f;

		bool a = UnityEngine::Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, RustStructs::Ignore);
		inAir = !a;

		if (inAir)
		{
			bool flag = false;

			Vector3 vector4 = newPos - oldPos;
			float num3 = Math::abs(vector4.y);
			float num4 = vector4.Magnitude2D();

			if (vector4.y >= 0.f) {
				flyhackDistanceVertical += vector4.y;
				flag = true;
			}
			if (num3 < num4) {
				flyhackDistanceHorizontal += num4;
				flag = true;
			}
			if (flag) {
				float num5 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num6 = _This->GetJumpHeight() + num5 + 4.f;
				if (flyhackDistanceVertical > num6) {
					return true;
				}
				float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7 + 4.f;
				if (flyhackDistanceHorizontal > num8) {
					return true;
				}
			}
		}
		else
		{
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
	}
	return false;
}

bool CheckFlyhack(AssemblyCSharp::BasePlayer* _This, bool PreventFlyhack)
{
	if (!InGame)
		return false;

	bool result;

	if (!IsAddressValid(_This->lastSentTick()))
		return false;

	if (!IsAddressValid(_This->get_transform()))
		return false;

	if (auto LocalPlayer = _This)
	{
		if (auto Transform = LocalPlayer->get_transform())
		{
			if (!_This->IsDead() && !_This->IsSleeper())
			{
				if (LocalPlayer->lastSentTick() && LocalPlayer->get_transform())
				{
					Vector3 oldPos = LocalPlayer->lastSentTick()->position();

					Vector3 modelPos = LocalPlayer->get_transform()->get_position();

					result = TestFlying(LocalPlayer, oldPos, modelPos);

					float num5 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num6 = _This->GetJumpHeight() + num5 + 4.f;

					m_settings::MaxVerticalFlyhack = num6;
					m_settings::VerticalFlyhack = flyhackDistanceVertical;

					float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num8 = 5.f + num7;

					m_settings::MaxHorisontalFlyhack = num8 + 4.f;
					m_settings::HorisontalFlyhack = flyhackDistanceHorizontal;

					if (result && PreventFlyhack)
					{
						const auto last_sent_tick = LocalPlayer->lastSentTick();
						const auto player_movement = LocalPlayer->movement();
						if (player_movement && last_sent_tick) {
							auto LastSentTickPos = last_sent_tick->position();
							reinterpret_cast<AssemblyCSharp::BaseMovement*>(player_movement)->set_TargetMovement(Vector3());
							reinterpret_cast<AssemblyCSharp::BaseMovement*>(player_movement)->TeleportTo(Vector3(LastSentTickPos.x, LastSentTickPos.y - 0.001, LastSentTickPos.z), LocalPlayer);
							if (const auto rigid_body = player_movement->body()) {
								rigid_body->set_velocity(Vector3());
							}
						}
					}
					return result;
				}
			}
		}
	}

	return false;
}

bool TestInsideTerrain(Vector3 pos)
{
	if (!AssemblyCSharp::TerrainMeta::get_Terrain()) return false;
	if (!AssemblyCSharp::TerrainMeta::get_HeightMap()) return false;
	if (!AssemblyCSharp::TerrainMeta::get_Terrain()) return false;
	if (!AssemblyCSharp::TerrainMeta::get_Collision()) return false;

	float height = AssemblyCSharp::TerrainMeta::get_HeightMap()->GetHeight(pos);

	if (pos.y > height - 0.3f)
		return false;

	float gaysex = AssemblyCSharp::TerrainMeta::get_Position().y + AssemblyCSharp::TerrainMeta::get_Terrain()->SampleHeight(pos);
	return pos.y <= gaysex - 0.3f && !AssemblyCSharp::TerrainMeta::get_Collision()->GetIgnore(pos, 0.01f);
}

bool IsInsideTerrain(bool prevent = false)
{
	BasePlayer* player = AssemblyCSharp::LocalPlayer::get_Entity();
	if (!IsAddressValid(player))
		return false;

	bool result = TestInsideTerrain(player->get_transform()->get_position());

	if (prevent && result)
		player->ForcePositionTo(player->lastSentTick()->position());
	return result;
}

inline void DoOreAttack(Vector3 pos, AssemblyCSharp::BaseEntity* p, AssemblyCSharp::BaseMelee* w)
{
	if (!InGame)
		return;

	if (!IsAddressValid(p)) return;
	if (!IsAddressValid(w)) return;

	if (w->nextAttackTime() >= UnityEngine::Time::get_time()) return;
	if (w->timeSinceDeploy() < w->deployDelay()) return;

	auto g_hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
	if (!IsAddressValid(g_hit_test_class))
		return;
	
	auto g_hit_test = (AssemblyCSharp::HitTest*)CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);
	if (!IsAddressValid(g_hit_test))
		return;


	auto trans = p->get_transform();
	if (!IsAddressValid(trans))
		return;


	UnityEngine::Ray r = UnityEngine::Ray(AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position(), (pos - AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position()).Normalized());

	g_hit_test->MaxDistance() = 1000.f;
	g_hit_test->HitTransform() = trans;
	g_hit_test->AttackRay() = r;
	g_hit_test->DidHit() = true;
	g_hit_test->HitEntity() = p;
	g_hit_test->HitPoint() = trans->InverseTransformPoint(pos);
	g_hit_test->HitNormal() = trans->InverseTransformDirection(pos);
	g_hit_test->damageProperties() = w->damageProperties();

	w->StartAttackCooldown(w->repeatDelay());

	return w->ProcessAttack((AssemblyCSharp::HitTest*)g_hit_test);
}

void VelocityChecks(Vector3 LocalPos, Vector3 AimbotTarget) {
	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
	if (IsAddressValid(LocalPlayer)) {
		auto ActiveItem = LocalPlayer->ActiveItem();
		auto HeldItem = ActiveItem->GetHeldEntity();
		auto PrefabID = HeldItem->prefabID();
		if (IsAddressValid(ActiveItem)) {
			if (PrefabID == 2836331625 || PrefabID == 4279856314 || PrefabID == 2545523575 || PrefabID == 3759841439) //bow  Nailgun mp4a5 custom-smg
			{
				if (!AssemblyCSharp::IsVisible(LocalPos, AimbotTarget)) {
					m_settings::ValidVelocity = false;
				}
				else
					m_settings::ValidVelocity = true;
			}
			else
				m_settings::ValidVelocity = true;
		}
		else
			m_settings::ValidVelocity = true;
	}
}

inline bool FirstInit = false;

std::vector<Vector3> cachedPoints;

void GenerateAndCachePoints(float radiusX, float radiusY, float radiusZ, int baseNumPoints) {

	// Adjust the number of points to generate "x" angles
	int numPoints = baseNumPoints;

	if (cachedPoints.empty()) {
		for (int i = 0; i < numPoints / 2; i++) {
			float theta = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
			float phi = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle

			//float x = radiusX * Math::sinf(phi) * Math::cosf(theta);
			//float y = radiusY * Math::sinf(phi) * Math::sinf(theta);
			//float z = radiusZ * Math::cosf(phi);

			float rX = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * radiusX;
			float rY = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * radiusY;
			float rZ = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * radiusZ;

			float x = rX * Math::sinf(phi) * Math::cosf(theta);
			float y = rY * Math::sinf(phi) * Math::sinf(theta);
			float z = rZ * Math::cosf(phi);

			cachedPoints.push_back(Vector3(x, y, z));
		}

		for (int i = 0; i < numPoints / 2; i++) {
			float theta = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
			float phi = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle

			float x = radiusX * Math::sinf(phi) * Math::cosf(theta);
			float y = radiusY * Math::sinf(phi) * Math::sinf(theta);
			float z = radiusZ * Math::cosf(phi);

			cachedPoints.push_back(Vector3(x, y, z));
		}
	}
}

void Hooks::ClientInput(AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2)
{
	if(!InGame)
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		Features().Instance()->LocalPlayer = a1;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(ToAddress(Hooks::ProjectileShootHookhk.get_original<void*>()))
		|| !IsAddressValid(ToAddress(Hooks::OnInputhk.get_original<void*>()))
		|| !IsAddressValid(ToAddress(Hooks::PPA_WriteToStreamhk.get_original<void*>())))
	{
		Hooks::ProjectileShootHookhk.VirtualFunctionHook(XS("ProjectileShoot"), HASH("WriteToStream"), &Hooks::ProjectileShootHook, XS("ProtoBuf"), 1);
		Hooks::PPA_WriteToStreamhk.VirtualFunctionHook(XS("PlayerProjectileAttack"), HASH("WriteToStream"), &Hooks::PPA_WriteToStream, XS("ProtoBuf"), 1);
		Hooks::OnInputhk.VirtualFunctionHook(XS("BaseMelee"), HASH("OnInput"), &Hooks::OnInput, XS(""), 0);
	}

	if (!FirstInit)
	{
		Hooks::TryToMovehk.VirtualFunctionHook(XS("ItemIcon"), HASH("TryToMove"), &Hooks::TryToMove, XS(""), 0);
		Hooks::PlayerWalkMovementhk.VirtualFunctionHook(XS("PlayerWalkMovement"), HASH("ClientInput"), &Hooks::PlayerWalkMovement, XS(""), 2);
		Hooks::BlockSprinthk.VirtualFunctionHook(XS("BasePlayer"), HASH("BlockSprint"), &Hooks::BlockSprint, XS(""), 1);
		Hooks::LateUpdatehk.PointerSwapHook(XS("TOD_Sky"), HASH("LateUpdate"), &Hooks::LateUpdate, XS(""), 0);
		FirstInit = true;
	}

	if (m_settings::MemoryAimbot && UnityEngine::Input::GetKey(RustStructs::KeyCode::F)) {
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				auto LocalPos = LocalPlayer->get_bone_transform(47)->get_position();
				auto TargetBone = AimbotTarget.m_player->get_bone_transform(AimbotTarget.m_bone)->get_position();
				auto CameraPos = camera->get_positionz();
				
				//Vector3 angle_to = calculate_angle(LocalPos, TargetBone);
				//angle_to = LocalPlayer->input()->bodyAngles().lerp(angle_to, (1.f - 0.f));
				
				//LocalPlayer->input()->bodyAngles() = angle_to;
			}
		}
	}

	if (m_settings::Flyhack_Indicator)
		CheckFlyhack(a1, m_settings::AntiFlyKick);

	float timeSinceLastTick = (UnityEngine::Time::get_realtimeSinceStartup() - Features().Instance()->LocalPlayer->lastSentTickTime());
	float last_tick_time = maxx(0.f, minm(timeSinceLastTick, 1.f));
	m_settings::last_tick_time = last_tick_time;

	float num = 1.5f;
	float eye_clientframes = 2.0f;
	float eye_serverframes = 2.0f;
	float num2 = eye_clientframes / 60.f;
	float num3 = eye_serverframes * Max3(UnityEngine::Time::get_deltaTime(), UnityEngine::Time::get_smoothDeltaTime(), UnityEngine::Time::get_fixedDeltaTime());
	float num4 = (last_tick_time + num2 + num3) * num;

	float num5 = Features().Instance()->LocalPlayer->MaxEyeVelocity() + Features().Instance()->LocalPlayer->GetParentVelocity().Magnitude();
	float num6 = Features().Instance()->LocalPlayer->BoundsPadding() + num4 * num5;

	m_settings::max_spoofed_eye_distance = num6;


	if (m_settings::WaitForInstantHit)
	{
		auto desynctime = UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;


		if (desyncpercentage >= 0.85f)
		{
			InstantHitReady = true;
		}
		else
		{
			InstantHitReady = false;
		}
	}

	if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = .99f;
	}
	else
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = 0.05f;
	}

	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
	auto camera = UnityEngine::Camera::get_main();
	if (IsAddressValid(camera)) {
		auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (IsAddressValid(AimbotTarget.m_player)) {
			Features().TargetID = AimbotTarget.m_player->userID();

			if (m_settings::Manipulation) {
				auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(Features().CachedManipPoint);

				if (AssemblyCSharp::IsVisible(LocalPlayer->eyes()->get_position(), Features().CachedManipPoint) &&
					AssemblyCSharp::IsVisible(Features().CachedManipPoint, Features().CachedBulletTPPosition)
					&& distance < 9
					&& !Features().CachedManipPoint.IsZero()
					&& AimbotTarget.m_player->userID() == Features().TargetID
					&& !AimbotTarget.m_player == NULL) {
					Features().PointVisible = true;
				}
				else {
					Features().CachedManipPoint = LocalPlayer->eyes()->get_position();
					Features().PointVisible = false;
				}

				if (m_settings::DrawManipPoints && Features().CachedManipPoint != LocalPlayer->eyes()->get_position() && Features().PointVisible)
				{
					UnityEngine::DDraw().Sphere(Features().CachedManipPoint, 0.1f, Color::Blue(), 0.05f, 0);
				}
			}
			else
				Features().CachedManipPoint = LocalPlayer->eyes()->get_position();
		}
	}
	

	if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				Features().Instance()->FindManipulationAngles(num6);
			}
		}
	}
	else
	{
		Features().PointVisible = false;
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		if (IsAddressValid(LocalPlayer)) {
			Features().CachedManipPoint = LocalPlayer->eyes()->get_position();
			Features().ManipulationAngle = LocalPlayer->eyes()->get_position();
		}
		//Features().ManipulationAngle = Vector3();
		m_settings::can_manipulate = false;
		m_settings::StartShooting = false;
		m_settings::Manipulation_Indicator = false;
	}

	if (IsAddressValid(camera))
	{
		auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (IsAddressValid(AimbotTarget.m_player)) {
			if (m_settings::CacheBulletTP) {
				{
					static float CachedGeneratedPoints;
					static bool Cached = false;
					if (!Cached) {
						CachedGeneratedPoints = m_settings::LOSCheckAmount;
						Cached = true;
					}
					if (CachedGeneratedPoints > m_settings::LOSCheckAmount || CachedGeneratedPoints < m_settings::LOSCheckAmount) {
						Cached = false;
						Features().GeneratedPoints = false;
					}

					if (!Features().GeneratedPoints) {
						GenerateAndCachePoints(2, 2, 2, m_settings::LOSCheckAmount);
						Features().GeneratedPoints = true;
					}
				}

				//Features().ConstantLOSCheck = false;

				if (Features().LOSTargetID != AimbotTarget.m_player->userID() || !AimbotTarget.m_player) {
					Features().LOSPoint = Vector3::Zero;
					Features().ConstantLOSCheck = false;
					Features().VerifiedLOSPoint = false;
				}

				if (m_settings::AdvancedChecks) {
					auto distance = AimbotTarget.m_player->get_transform()->get_position().Distance(Features().LOSPoint);
					if (AssemblyCSharp::IsVisible(Features().CachedManipPoint, Features().LOSPoint) &&
						AssemblyCSharp::IsVisible(Features().LOSPoint, AimbotTarget.m_position) &&
						distance < 2.2) {
						Features().VerifiedLOSPoint = true;
						Features().CachedBulletTPPosition = Features().LOSPoint;
					}
					else {
						Features().LOSPoint = Vector3::Zero;
						Features().VerifiedLOSPoint = false;
						Features().ConstantLOSCheck = false;
					}
				}
				else {
					if (AssemblyCSharp::IsVisible(Features().CachedManipPoint, Features().LOSPoint)) {
						Features().VerifiedLOSPoint = true;
					}
					else {
						Features().LOSPoint = Vector3::Zero;
						Features().VerifiedLOSPoint = false;
						Features().ConstantLOSCheck = false;
					}
				}

				if (!Features().VerifiedLOSPoint) {
					for (const Vector3& point : cachedPoints) {
						//UnityEngine::DDraw().Sphere(AimbotTarget.m_position + point, 0.05f, Color::Red(), 0.05f, 0);
						if (m_settings::AdvancedChecks) {
							if (AssemblyCSharp::IsVisible(Features().CachedManipPoint, AimbotTarget.m_position + point) &&
								AssemblyCSharp::IsVisible(AimbotTarget.m_position + point, AimbotTarget.m_position)) {
								Features().ConstantLOSCheck = true; 
								Features().VerifiedLOSPoint = true;
								Features().LOSPoint = AimbotTarget.m_position + point;
								Features().LOSTargetID = AimbotTarget.m_player->userID();
								break;  
							}
						}
						else {
							if (AssemblyCSharp::IsVisible(Features().CachedManipPoint, AimbotTarget.m_position + point)) {
								Features().VerifiedLOSPoint = true;
								Features().ConstantLOSCheck = true;  
								Features().LOSPoint = AimbotTarget.m_position + point;
								break;  
							}
						}
					}
				}

				//if (Features().VerifiedLOSPoint)
				//	Features().CachedBulletTPPosition = Features().LOSPoint;

				if (m_settings::ShowCachedPoint) {
					UnityEngine::DDraw().Sphere(Features().LOSPoint, 0.05f, Color::Green(), 0.05f, 0);
				}
			}
		}
	}

	if (m_settings::SnickerBullet) {
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		auto EyePos = LocalPlayer->eyes()->get_position();
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				UnityEngine::DDraw().Arrow(EyePos, Features().CachedManipPoint, 0.1f, Color(1.f, 0.f, 0.f, 1.f), 0.02f);
				UnityEngine::DDraw().Arrow(Features().CachedManipPoint, Features().CachedBulletTPPosition, 0.1f, Color(0.f, 1.f, 0.f, 1.f), 0.02f);
				UnityEngine::DDraw().Arrow(Features().CachedBulletTPPosition, AimbotTarget.m_position, 0.1f, Color(0.f, 0.f, 1.f, 1.f), 0.02f);
			}
		}
	}

	if (CalledLaunchFromHook)
	{
		AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), XS("client.prediction 0"), nullptr);
	}
	else
	{
		AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), XS("client.prediction 1"), nullptr);
	}

	if (IsAddressValid(camera)) {
		auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (IsAddressValid(AimbotTarget.m_player)) {
			if (m_settings::BulletTP)
			{
				if (m_settings::CacheBulletTP) {
					if (Features().ConstantLOSCheck) {
						Features().Instance()->FindBulletTPAngles(num6);
					}
					else
					{
						Features().CachedBulletTPPosition = AimbotTarget.m_position;
						Features().BulletTPAngle = Vector3(0, 0, 0);
						
						Features().BulletTPPointVisible = false;
						m_settings::Thickbullet_Indicator = false;
						m_settings::Thickbullet_AutoShoot = false;
					}
				}
				else
					Features().Instance()->FindBulletTPAngles(num6);
			}
			else if (!Features().BulletTPAngle.IsZero()) {
				Features().CachedBulletTPPosition = AimbotTarget.m_position;
				Features().BulletTPAngle = Vector3(0, 0, 0);
				Features().BulletTPPointVisible = false;
				m_settings::Thickbullet_Indicator = false;
				m_settings::Thickbullet_AutoShoot = false;
			}
			else
				Features().CachedBulletTPPosition = AimbotTarget.m_position;
		}
		else {
			m_settings::Thickbullet_AutoShoot = false;
			m_settings::Thickbullet_Indicator = false;
		}
	}

	if (m_settings::BulletTP)
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {

			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				if (AimbotTarget.m_player->IsConnected())
				{
					AimbotTarget.m_player->get_transform()->set_rotation(Vector4(0.f, 0.f, 0.f, 1.f)); //Fix all player rotations for bullet tp to not have invalids.
				}
			}
		}
	}

	static bool StartShooting = false;

	if (m_settings::Autoshoot) {

		if (m_settings::BehindWall) {
			if (m_settings::Manipulation && m_settings::BulletTP) {
				if (m_settings::Thickbullet_AutoShoot && m_settings::StartShooting && m_settings::Manipulation_Indicator)
					StartShooting = true;
				else
					StartShooting = false;
			}
		}
		else if (m_settings::Thickbullet_AutoShoot) {
			if (m_settings::BulletTP)
				StartShooting = true;
			else
				StartShooting = false;
		}
		else if (m_settings::StartShooting) {
			if (m_settings::Manipulation)
				StartShooting = true;
			else
				StartShooting = false;
		}
		else
			StartShooting = false;
	}

	auto BaseProjectile = a1->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();

	if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
	{
		Features().BaseProjectile = BaseProjectile;

		if (IsAddressValid(Features().LocalPlayer) && IsAddressValid(Features().BaseProjectile))
		{

			//autoshoot
			auto camera = UnityEngine::Camera::get_main();
			if (IsAddressValid(camera))
			{
				auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
				if (IsAddressValid(AimbotTarget.m_player))
				{

					if (Features().BulletTPAngle.IsZero())
						Features().BulletTPAngle = AimbotTarget.m_position;

					if (m_settings::Autoshoot && !BaseProjectile->IsA(AssemblyCSharp::FlintStrikeWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()))
					{
						if (m_settings::WaitForInstantHit)
						{
							if (InstantHitReady)
							{
								if (StartShooting)
								{
									CalledLaunchFromHook = true;
									BaseProjectile->DoAttackRecreation();
									CalledLaunchFromHook = false;

								}
							}
						}
						else
						{
							if (!m_settings::AlwaysAutoshoot && UnityEngine::Input::GetKey(m_settings::AutoshootKey))
							{
								if (StartShooting)
								{
									CalledLaunchFromHook = true;
									BaseProjectile->DoAttackRecreation();
									
								}
							}
							else if (m_settings::AlwaysAutoshoot)
							{
								if (StartShooting)
								{
									CalledLaunchFromHook = true;
									BaseProjectile->DoAttackRecreation();								
								}
							}
							CalledLaunchFromHook = false;
						}
					}

					//bullet queue
					if (m_settings::InstantKill && AimbotTarget.m_player->IsAlive())
					{
						if (m_settings::WaitForInstantHit)
						{
							if (InstantHitReady)
							{
								if (!BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseLauncher::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CompoundBowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CrossbowWeapon::StaticClass()))
								{
									if (BaseProjectile->primaryMagazine()->contents() > 0)
									{

										if (m_settings::WaitForBulletTP)
										{

											Vector3 pos = AimbotTarget.m_position;

											if (Features().BulletTPAngle.IsZero())
												Features().BulletTPAngle = AimbotTarget.m_position;

											if (StartShooting)
											{

												float maxpacketsperSECOND = 1;
												if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
												{
													CalledLaunchFromHook = true;
													for (int i = 0; i < 4; i++)
													{
														BaseProjectile->primaryMagazine()->contents()--;

														BaseProjectile->LaunchProjectile();
														BaseProjectile->UpdateAmmoDisplay();
														BaseProjectile->ShotFired();
														BaseProjectile->DidAttackClientside();
														break;
													}
													//a1->SendClientTick();
													RPC_Counter3.Increment();
													CalledLaunchFromHook = false;
												}
											}
										}
										else
										{
											if (Features().BulletTPAngle.IsZero())
												Features().BulletTPAngle = AimbotTarget.m_position;

											if (StartShooting)
											{
												float maxpacketsperSECOND = 1;
												if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
												{
													CalledLaunchFromHook = true;

													int magazineContents = BaseProjectile->primaryMagazine()->contents();
													for (int i = 0; i < 4; i++)
													{
														BaseProjectile->primaryMagazine()->contents()--;

														BaseProjectile->LaunchProjectile();
														BaseProjectile->UpdateAmmoDisplay();
														BaseProjectile->ShotFired();
														BaseProjectile->DidAttackClientside();
														break;
													}
													RPC_Counter3.Increment();
													CalledLaunchFromHook = false;

												}

											}

										}

									}
								}
							}
						}
						else
						{
							if (!BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseLauncher::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CompoundBowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CrossbowWeapon::StaticClass()))
							{
								if (BaseProjectile->primaryMagazine()->contents() > 0)
								{

									if (m_settings::WaitForBulletTP)
									{

										Vector3 pos = AimbotTarget.m_position;

										if (Features().BulletTPAngle.IsZero())
											Features().BulletTPAngle = AimbotTarget.m_position;

										if (StartShooting)
										{

											float maxpacketsperSECOND = 1;
											if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
											{
												CalledLaunchFromHook = true;
												for (int i = 0; i < 4; i++)
												{
													BaseProjectile->primaryMagazine()->contents()--;

													BaseProjectile->LaunchProjectile();
													BaseProjectile->UpdateAmmoDisplay();
													BaseProjectile->ShotFired();
													BaseProjectile->DidAttackClientside();
													break;
												}
												//a1->SendClientTick();
												RPC_Counter3.Increment();
												CalledLaunchFromHook = false;
											}

										}
									}
									else
									{
										if (Features().BulletTPAngle.IsZero())
											Features().BulletTPAngle = AimbotTarget.m_position;

										if (StartShooting)
										{
											float maxpacketsperSECOND = 1;
											if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
											{
												CalledLaunchFromHook = true;

												int magazineContents = BaseProjectile->primaryMagazine()->contents();
												for (int i = 0; i < 4; i++)
												{
													BaseProjectile->primaryMagazine()->contents()--;

													BaseProjectile->LaunchProjectile();
													BaseProjectile->UpdateAmmoDisplay();
													BaseProjectile->ShotFired();
													BaseProjectile->DidAttackClientside();
													break;
												}
												RPC_Counter3.Increment();
												CalledLaunchFromHook = false;

											}

										}

									}

								}
							}
						}
					}
				}
			}

			if (m_settings::VelocityAimbot) {
				auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
				if (IsAddressValid(LocalPlayer)) {
					auto camera = UnityEngine::Camera::get_main();
					if (IsAddressValid(camera)) {
						auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
						if (IsAddressValid(AimbotTarget.m_player)) {
							auto LocalPos = LocalPlayer->get_bone_transform(48)->get_position();

							VelocityChecks(LocalPos, Features().BulletTPAngle);
						}
						else
							m_settings::ValidVelocity = true;
					}
					else
						m_settings::ValidVelocity = true;
				}
				else
					m_settings::ValidVelocity = true;
			}
			else
				m_settings::ValidVelocity = true;

			if (m_settings::NormalFastBullet && !m_settings::VelocityAimbot) {
				auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
				auto ActiveItem = LocalPlayer->ActiveItem();
				auto HeldItem = ActiveItem->GetHeldEntity();
				auto PrefabID = HeldItem->prefabID();

				if (ActiveItem) {
					static float orig[10];

					if (PrefabID == 1978739833 || PrefabID == 1537401592 || PrefabID == 3474489095 || PrefabID == 3243900999 || //ak, compound, doublebarrel, tommy
						PrefabID == 2696589892 || PrefabID == 1877401463 || PrefabID == 4231282088 || PrefabID == 563371667 || //waterpipe, spas-12, semi-rifle, semi-pistol
						PrefabID == 2477536592 || PrefabID == 554582418 || PrefabID == 3305012504 || PrefabID == 636374895 ||  //revolver, pump, python, prototype-17
						PrefabID == 4279856314 || PrefabID == 2293870814 || PrefabID == 844375121 || PrefabID == 2836331625 || //nailgun, m92-pistol, lr-300, hunting-bow
						PrefabID == 2176761593) { //eoka
						orig[0] = 1.f;
					}
					else if (PrefabID == 2545523575 || PrefabID == 3759841439) { //mp4a5, custom-smg
						orig[0] = 0.8f;
					}
					else if (PrefabID == 3459133190) { //hmlmg
						orig[0] = 1.2f;
					}
					else if (PrefabID == 1440914039) {//m249
						orig[0] = 1.3f;
					}
					else if (PrefabID == 1517089664) { //m39 rifle
						orig[0] = 1.25f;
					}
					else if (PrefabID == 2620171289) {//l96
						orig[0] = 3.f;
					}
					else if (PrefabID == 1665481300) { //bolty
						orig[0] = 1.75f;
					}
					else if (PrefabID == 2727391082) { //crossbow
						orig[0] = 1.5f;
					}
					else {
						orig[0] = 1.f;
					}

					BaseProjectile->projectileVelocityScale() = orig[0] + 0.39f;
				}
			}
			else {
				auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
				auto ActiveItem = LocalPlayer->ActiveItem();
				auto HeldItem = ActiveItem->GetHeldEntity();
				auto PrefabID = HeldItem->prefabID();

				if (ActiveItem) {
					static float orig[10];

					if (PrefabID == 1978739833 || PrefabID == 1537401592 || PrefabID == 3474489095 || PrefabID == 3243900999 || //ak, compound, doublebarrel, tommy
						PrefabID == 2696589892 || PrefabID == 1877401463 || PrefabID == 4231282088 || PrefabID == 563371667 || //waterpipe, spas-12, semi-rifle, semi-pistol
						PrefabID == 2477536592 || PrefabID == 554582418 || PrefabID == 3305012504 || PrefabID == 636374895 ||  //revolver, pump, python, prototype-17
						PrefabID == 4279856314 || PrefabID == 2293870814 || PrefabID == 844375121 || PrefabID == 2836331625 || //nailgun, m92-pistol, lr-300, hunting-bow
						PrefabID == 2176761593) { //eoka
						orig[0] = 1.f;
					}
					else if (PrefabID == 2545523575 || PrefabID == 3759841439) { //mp4a5, custom-smg
						orig[0] = 0.8f;
					}
					else if (PrefabID == 3459133190) { //hmlmg
						orig[0] = 1.2f;
					}
					else if (PrefabID == 1440914039) {//m249
						orig[0] = 1.3f;
					}
					else if (PrefabID == 1517089664) { //m39 rifle
						orig[0] = 1.25f;
					}
					else if (PrefabID == 2620171289) {//l96
						orig[0] = 3.f;
					}
					else if (PrefabID == 1665481300) { //bolty
						orig[0] = 1.75f;
					}
					else if (PrefabID == 2727391082) { //crossbow
						orig[0] = 1.5f;
					}
					else {
						orig[0] = 1.f;
					}

					BaseProjectile->projectileVelocityScale() = orig[0];
				}
			}

			
			m_settings::reload_time = BaseProjectile->reloadTime();

			if (m_settings::AutoReload)
			{
				if (BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->HasReloadCooldown() && !BaseProjectile->IsA(AssemblyCSharp::FlintStrikeWeapon::StaticClass()))
				{

					if (!m_settings::did_reload)
						m_settings::time_since_last_shot = (UnityEngine::Time::get_fixedTime() - m_settings::fixed_time_last_shot);

					if (m_settings::just_shot && (m_settings::time_since_last_shot > 0.2f))
					{
						BaseProjectile->ServerRPC(XS("StartReload"));
						BaseProjectile->SendSignalBroadcast(RustStructs::Signal::Reload, XS(""));

						m_settings::reload_reset_2 = false;
						m_settings::just_shot = false;
						//CanReload = false;
					}
					if (m_settings::time_since_last_shot > (BaseProjectile->reloadTime() - (BaseProjectile->reloadTime() / 10)) && !m_settings::did_reload)
					{
						BaseProjectile->ServerRPC(XS("Reload"));
						m_settings::did_reload = true;
						m_settings::time_since_last_shot = 0;
						m_settings::reload_reset = false;
						//CanReload = BaseProjectile->primaryMagazine()->contents() < BaseProjectile->primaryMagazine()->capacity();

					}
				}
				else
				{
					m_settings::reload_reset = false;
					m_settings::reload_reset_2 = false;
					m_settings::did_reload = false;
					m_settings::just_shot = false;
					m_settings::fixed_time_last_shot = 0;
					m_settings::time_since_last_shot = 0;
				}
			}
			else
			{
				m_settings::reload_reset = false;
				m_settings::reload_reset_2 = false;
				m_settings::did_reload = false;
				m_settings::just_shot = false;
				m_settings::fixed_time_last_shot = 0;
				m_settings::time_since_last_shot = 0;
			}

			//Features().AutoReload(Features().BaseProjectile);


			if (m_settings::RemoveAttackAnimations)
			{
				auto ActiveModel = AssemblyCSharp::BaseViewModel::get_ActiveModel();

				if (IsAddressValid(ActiveModel))
				{
					if (IsAddressValid(ActiveModel->animator()))
					{
						if (IsAddressValid(BaseProjectile))
						{
							if (!BaseProjectile->HasAttackCooldown())
							{
								if (BaseProjectile->timeSinceDeploy() > BaseProjectile->deployDelay())
								{
									if (BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
									{
										if (a1->input()->state()->IsDown(RustStructs::BUTTON::FIRE_PRIMARY))
											ActiveModel->animator()->set_speed(-1);
									}
								}
							}
						
						}
					}
				}
			}

			if (m_settings::NoWeaponBob)
			{
				auto ActiveModel = AssemblyCSharp::BaseViewModel::get_ActiveModel();

				if (IsAddressValid(ActiveModel))
				{
					


					if (IsAddressValid(ActiveModel->bob()))
					{
						ActiveModel->bob()->bobAmountRun() = { 0.f, 0.f, 0.f, 0.f };
						ActiveModel->bob()->bobAmountWalk() = { 0.f, 0.f, 0.f, 0.f };
						//ActiveModel->bob()->bobSpeedWalk() = 0.f;
						//ActiveModel->bob()->bobSpeedRun() = 0.f;
					}

					if (IsAddressValid(ActiveModel->sway()))
					{
						ActiveModel->sway()->positionalSwaySpeed() = { 0 };
						ActiveModel->sway()->positionalSwayAmount() = { 0 };
					}

					if (IsAddressValid(ActiveModel->lower()))
					{
						ActiveModel->lower()->lowerOnSprint() = false;
						ActiveModel->lower()->lowerWhenCantAttack() = false;
						ActiveModel->lower()->shouldLower() = false;
					}
				}
			}

			if (IsAddressValid(Features().BaseProjectile) && Features().BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !Features().BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::Planner::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::JackHammer::StaticClass()))
			{

				if (m_settings::ChangeRecoil)
				{
					if (const auto RecoilProperties = Features().BaseProjectile->recoil())
					{
						static float orig[6];
						static bool StoreOrig = false;

						if (const auto newRecoilOverride = RecoilProperties->newRecoilOverride())
						{
							if (!StoreOrig)
							{
								orig[0] = newRecoilOverride->recoilYawMin();
								orig[1] = newRecoilOverride->recoilYawMax();
								orig[2] = newRecoilOverride->recoilPitchMin();
								orig[3] = newRecoilOverride->recoilPitchMax();
								orig[4] = newRecoilOverride->ADSScale();
								orig[5] = newRecoilOverride->movementPenalty();

								StoreOrig = true;
							}

							const float amount = m_settings::recoilPercent / 100;
							newRecoilOverride->recoilYawMin() = orig[0] * amount;
							newRecoilOverride->recoilYawMax() = orig[1] * amount;
							newRecoilOverride->recoilPitchMin() = orig[2] * amount;
							newRecoilOverride->recoilPitchMax() = orig[3] * amount;
							newRecoilOverride->ADSScale() = orig[4] * amount;
							newRecoilOverride->movementPenalty() = orig[5] * amount;

							/*	newRecoilOverride->recoilYawMin() = 0;
								newRecoilOverride->recoilYawMax() = 0;
								newRecoilOverride->recoilPitchMin() = 0;
								newRecoilOverride->recoilPitchMax() = 0;
								newRecoilOverride->ADSScale() = 0;
								newRecoilOverride->movementPenalty() = 0;*/
						}
						else
						{
							if (!StoreOrig)
							{
								orig[0] = newRecoilOverride->recoilYawMin();
								orig[1] = newRecoilOverride->recoilYawMax();
								orig[2] = newRecoilOverride->recoilPitchMin();
								orig[3] = newRecoilOverride->recoilPitchMax();
								orig[4] = newRecoilOverride->ADSScale();
								orig[5] = newRecoilOverride->movementPenalty();

								StoreOrig = true;
							}

							const float amount = m_settings::recoilPercent / 100;
							newRecoilOverride->recoilYawMin() = orig[0] * amount;
							newRecoilOverride->recoilYawMax() = orig[1] * amount;
							newRecoilOverride->recoilPitchMin() = orig[2] * amount;
							newRecoilOverride->recoilPitchMax() = orig[3] * amount;
							newRecoilOverride->ADSScale() = orig[4] * amount;
							newRecoilOverride->movementPenalty() = orig[5] * amount;
						}
					}
				}

				if (m_settings::ForceAutomatic)
				{
					Features().BaseProjectile->automatic() = true;
				}

				if (m_settings::NoSpread)
				{
					Features().BaseProjectile->stancePenalty() = 0.f;
					Features().BaseProjectile->aimconePenalty() = 0.f;
					Features().BaseProjectile->aimCone() = 0.f;
					Features().BaseProjectile->hipAimCone() = 0.f;
					Features().BaseProjectile->aimconePenaltyPerShot() = 0.f;
				}

				static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
				float current_time = UnityEngine::Time::get_realtimeSinceStartup();

				if (m_settings::WeaponSpammer && UnityEngine::Input::GetKey(m_settings::WeaponSpamKey))
				{
					float delay = m_settings::WeaponSpamDelay / 100;
					if (current_time - send_time > delay)
					{
						Features().BaseProjectile->SendSignalBroadcast(RustStructs::Signal::Attack, XS(""));
						send_time = current_time;
					}
				}
			}
		}
	}

	if (IsAddressValid(BaseProjectile) && a1->IsMelee() || a1->IsWeapon())
	{
		if (m_settings::WeaponChams) {
			if (IsAddressValid(AssemblyCSharp::BaseViewModel::get_ActiveModel()))
			{
				AssemblyCSharp::BaseViewModel::get_ActiveModel()->useViewModelCamera() = false;
			}

			auto g_render = AssemblyCSharp::BaseViewModel::get_ActiveModel()->GetComponentsInChildren(FPSystem::Type::Renderer());
			if (IsAddressValid(g_render))
			{
				auto size = g_render->max_length;
				for (int i = 0; i < size; i++)
				{
					auto MainRenderer = g_render->m_Items[i];
					if (!IsAddressValid(MainRenderer))
						continue;

					auto material = MainRenderer->material();

					if (!IsAddressValid(material))
						continue;

					if (material->get_name()->Contains(XS("sparks2"))
						|| material->get_name()->Contains(XS("puff-3"))
						|| material->get_name()->Contains(XS("c4_smoke_01"))
						|| material->get_name()->Contains(XS("HeavyRefract"))
						|| material->get_name()->Contains(XS("pfx_smoke_whispy_1_white_viewmodel"))
						|| material->get_name()->Contains(XS("Ak47uIce Specular"))
						//|| Material->name()->Contains(E(L"ak47_barrel_ice"
						//|| Material->name()->Contains(E(L"ak47_maggrip_ice"
						|| material->get_name()->Contains(XS("muzzle_embers"))
						|| material->get_name()->Contains(XS("c4charge"))
						|| material->get_name()->Contains(XS("pfx_smoke_rocket"))
						|| material->get_name()->Contains(XS("pfx_smoke_rocket_thicksoftblend"))
						|| material->get_name()->Contains(XS("holosight.georeticle (Instance)"))
						|| material->get_name()->Contains(XS("vfx_embers (Instance)"))
						|| material->get_name()->Contains(XS("pfx_smoke_whispy_1_white  (Instance)"))
						|| material->get_name()->Contains(XS("flame-mlrs-cone (Instance)"))
						|| material->get_name()->Contains(XS("vfx_heatshimmer (Instance)"))
						|| material->get_name()->Contains(XS("lasersight (Instance)"))

						|| material->get_name()->Contains(XS("muzzle_fumes1"))
						|| material->get_name()->Contains(XS("muzzle_fumes2"))
						|| material->get_name()->Contains(XS("muzzle_fumes3"))
						|| material->get_name()->Contains(XS("wispy-2"))
						|| material->get_name()->Contains(XS("quickblast-1"))
						|| material->get_name()->Contains(XS("muzzle_flash-front-3x3"))
						|| material->get_name()->Contains(XS("muzzle_flash-cross"))
						|| material->get_name()->Contains(XS("muzzle_flash-side-1x4")))
						continue;

					//if ( Material->name( )->Contains( L"Hand" ) || Material->name( )->Contains( L"Arm" ) || Material->name( )->Contains( L"Glove" ) )

					//LOG("[DEBUG] matz - %ls", material->get_name()->c_str());

					int selectedChams = m_settings::WeaponSelectedChams;

					switch (selectedChams) {
					case 0:
						if (FireBundleA) {
							if (!FireShaderA) //Blue Fire
								FireShaderA = FireBundleA->LoadAsset<UnityEngine::Shader>(XS("new amplifyshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!FireMaterialA)
								FireMaterialA = FireBundleA->LoadAsset<UnityEngine::Material>(XS("fire.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != FireShaderA)
							{
								MainRenderer->set_material(FireMaterialA);
								FireMaterialA->set_shader(FireShaderA);
							}
						}
						break;
					case 1:
						if (FireBundleB) {
							if (!FireShaderB) //Red Fire
								FireShaderB = FireBundleB->LoadAsset<UnityEngine::Shader>(XS("new amplifyshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!FireMaterialB)
								FireMaterialB = FireBundleB->LoadAsset<UnityEngine::Material>(XS("fire2.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != FireShaderB)
							{
								MainRenderer->set_material(FireMaterialB);
								FireMaterialB->set_shader(FireShaderB);
							}
						}
						break;
					case 2:
						if (LightningBundle) {
							if (!LightningShader) //Lightning
								LightningShader = LightningBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!LightningMaterial)
								LightningMaterial = LightningBundle->LoadAsset<UnityEngine::Material>(XS("lightning.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != LightningShader)
							{
								MainRenderer->set_material(LightningMaterial);
								LightningMaterial->set_shader(LightningShader);
							}
						}
						break;
					case 3:
						if (GeometricBundle) {
							if (!GeometricShader) //Geometric Disolve
								GeometricShader = GeometricBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro geometric dissolve.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!GeometricMaterial)
								GeometricMaterial = GeometricBundle->LoadAsset<UnityEngine::Material>(XS("galaxy.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != GeometricShader)
							{
								MainRenderer->set_material(GeometricMaterial);
								GeometricMaterial->set_shader(GeometricShader);
							}
						}
						break;
					case 4:
						if (GalaxyBundle) {
							if (!GalaxyShader) //Galaxy
								GalaxyShader = GalaxyBundle->LoadAsset<UnityEngine::Shader>(XS("galaxymaterial.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!GalaxyMaterial)
								GalaxyMaterial = GalaxyBundle->LoadAsset<UnityEngine::Material>(XS("galaxymaterial_12.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != GalaxyShader)
							{
								MainRenderer->set_material(GalaxyMaterial);
								GalaxyMaterial->set_shader(GalaxyShader);
							}
						}
						break;
					case 5:
						if (WireFrameBundle) {
							if (!WireFrameShader) //Galaxy
								WireFrameShader = WireFrameBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro wireframe.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!WireFrameMaterial)
								WireFrameMaterial = WireFrameBundle->LoadAsset<UnityEngine::Material>(XS("wireframe.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != WireFrameShader)
							{
								MainRenderer->set_material(WireFrameMaterial);
								WireFrameMaterial->set_shader(WireFrameShader);
								//WireFrameMaterial->SetColor("_Color", Color::Red());
							}
						}
						break;

					}
				}
			}
		}
	}

	Features().RemoveCollision();

	if (m_settings::NoMovementRestrictions)
	{
		AssemblyCSharp::LocalPlayer::get_Entity()->clothingBlocksAiming() = false;
	}

	if (m_settings::InstantHeal)
	{
		float nextActionTime = 0, period = 1.4721;
		auto health = a1->_health();

		auto Held = a1->ActiveItem();

		if (IsAddressValid(Held))
		{
			auto HeldEntity = Held->heldEntity();
			if (HeldEntity)
			{
				if (!strcmp(HeldEntity->class_name(), XS("MedicalTool"))) {
					//auto medical = reinterpret_cast<AssemblyCSharp::MedicalTool*>(m_base_projectile);
					auto Time = UnityEngine::Time::get_time();

					if (BaseProjectile->timeSinceDeploy() > BaseProjectile->deployDelay() && BaseProjectile->nextAttackTime() <= Time) {
						if (Time > nextActionTime) {
							nextActionTime = Time + period;
							if (health < 99)
								BaseProjectile->ServerRPC(XS("UseSelf"));
						}
					}
				}
			}
		}
	}

	if (m_settings::NoSway)
	{
		AssemblyCSharp::LocalPlayer::get_Entity()->clothingAccuracyBonus() = 1.f;
	}

	if (m_settings::PlayerChams)
		ConVar::Culling::entityMinCullDist() = m_settings::PlayerESPDistance;

	static bool ResetGameTime = false;
	if (m_settings::TimeChanger || m_settings::RemoveUnderwaterEffects || ResetGameTime)
	{
		auto admin_c = CIl2Cpp::FindClass(XS("ConVar"), XS("Admin"));
		auto instance = uint64_t(admin_c->static_fields);

		if (m_settings::TimeChanger) {
			*(float*)(instance + 0x0) = m_settings::GameTime;
			ResetGameTime = true;
		}
		if (!m_settings::TimeChanger && ResetGameTime) {
			*(float*)(instance + 0x0) = -1;
			ResetGameTime = false;
		}

		if (m_settings::RemoveUnderwaterEffects) {
			*(bool*)(instance + 0x11) = false;
		}
	}

	auto base_melee = a1->GetHeldEntityCast<AssemblyCSharp::BaseMelee>();

	if (m_settings::AutoFarmOre)
	{
		if (IsAddressValid(base_melee))
		{
			if (base_melee->class_name_hash() == HASH("BaseMelee") || base_melee->class_name_hash() == HASH("JackHammer"))
			{
				f_object ore_hot_spot = f_object::get_closest_object(a1->get_bone_transform(47)->get_position(),
					XS(""),
					Vector3(),
					Vector3(),
					Vector3(),
					true,
					XS("OreHotSpot"));
				if (ore_hot_spot.valid) {
					Vector3 local = a1->ClosestPoint(ore_hot_spot.position);
					if (local.get_3d_dist(ore_hot_spot.position) <= 3.5f) {
						DoOreAttack(ore_hot_spot.position, (AssemblyCSharp::BaseEntity*)ore_hot_spot.entity, base_melee);
					}
				}
			}
		}
		
	}

	if (m_settings::AutoFarmTree)
	{
		if (IsAddressValid(base_melee))
		{
			if (base_melee->class_name_hash() == HASH("BaseMelee") || base_melee->class_name_hash() == HASH("Chainsaw"))
			{
				f_object tree_entity = f_object::get_closest_object(a1->get_bone_transform(48)->get_position(),
					XS(""),
					Vector3(),
					Vector3(),
					Vector3(),
					true,
					XS("TreeEntity"));
				if (tree_entity.valid) {
					tree_entity.position = Vector3();
					f_object tree_marker = f_object::get_closest_object(a1->get_bone_transform(48)->get_position(),
						XS(""),
						Vector3(),
						Vector3(),
						Vector3(),
						true,
						XS("TreeMarker"));
					if (tree_marker.valid) {
						Vector3 locala = a1->ClosestPoint(tree_marker.position);
						if (locala.get_3d_dist(tree_marker.position) <= 3.5f) {
							tree_entity.position = tree_marker.position;
							Vector3 local = a1->ClosestPoint(tree_entity.position);
							if (local.get_3d_dist(tree_entity.position) <= 3.5f) {
								DoOreAttack(tree_entity.position, (AssemblyCSharp::BaseEntity*)tree_entity.entity, base_melee);
							}
						}
					}
				}
			}
		}
	}


	//UnityEngine::RenderSettings::set_skybox(nullptr);

	if (m_settings::AdminFlags)
	{
		a1->playerFlags() |= RustStructs::PlayerFlags::IsAdmin;
	}

	if (m_settings::AdminCheat)
	{
		if (UnityEngine::Input::GetKeyDown(m_settings::AdminCheatKey) && !DoNoclip)
			DoNoclip = true;
		else if (UnityEngine::Input::GetKeyDown(m_settings::AdminCheatKey) && DoNoclip)
			DoNoclip = false;


		if (DoNoclip)
			a1->GetBaseMovement()->adminCheat() = true;
		else
			a1->GetBaseMovement()->adminCheat() = false;
	}
	else
		DoNoclip = false;

	if (m_settings::TeleportMax)
	{
		auto Movement = a1->movement();

		if (IsAddressValid(Movement)) {
			if (UnityEngine::Input::GetKey(m_settings::TeleportMaxKey))
				Movement->capsuleHeight() = 8.5f;
			else
				Movement->capsuleHeight() = 1.8f;	
		}
	}

	if (m_settings::NoAttackRestrictions)
	{
		//Shooting whilst mounted
		if (const auto Mounted = a1->mounted())
		{
			Mounted->canWieldItems() = true;
		}

		//CanAttack
		if (const auto ModelState = a1->modelState())
		{
			ModelState->set_flag(RustStructs::ModelState_Flag::OnGround);
			a1->GetBaseMovement()->set_Grounded(1.f);
		}
	}

	if (m_settings::PlayerFov || m_settings::Zoom)
	{
		auto g_graphics_ = CIl2Cpp::FindClass(XS("ConVar"), XS("Graphics"));
		auto instance = std::uint64_t(g_graphics_->static_fields);
		bool zooming = false;

		if (m_settings::Zoom && UnityEngine::Input::GetKey(m_settings::ZoomKey))
			zooming = true;
		else
			zooming = false;

		if (zooming)
			*(float*)(instance + 0x18) = m_settings::ZoomAmount;
		else if (!zooming && m_settings::PlayerFov)
			*(float*)(instance + 0x18) = m_settings::PlayerFovAmount;
		else
			*(float*)(instance + 0x18) = 90.f;
	}

	if (const auto LocalMovement = a1->movement())
	{
		if (m_settings::SpiderMan)
		{
			LocalMovement->groundAngle() = 0.f;
			LocalMovement->groundAngleNew() = 0.f;
		}

		if (m_settings::SmallerLocalRadius)
		{
			LocalMovement->capsule()->set_radius(0.44);
		}

		if (m_settings::InfiniteJump)
		{
			LocalMovement->landTime() = 0.f;
			LocalMovement->jumpTime() = 0.f;
			LocalMovement->groundTime() = 100000.f;
		}

		if (m_settings::AlwaysSprint)
		{
			LocalMovement->sprintForced() = true;
		}
	}

	if (m_settings::RotationAimbot)
	{
		if (UnityEngine::Input::GetKey(m_settings::RotationKey))
		{
			auto camera = UnityEngine::Camera::get_main();
			if (IsAddressValid(camera)) {
				auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
				if (IsAddressValid(m_target.m_player)) {
					auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
					if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()))
					{
						if (AssemblyCSharp::IsVisible(Features().LocalPlayer->eyes()->get_position(), m_target.m_position))
						{
							auto PrimaryMagazine = BaseProjectile->primaryMagazine();
							if (IsAddressValid(PrimaryMagazine))
							{
								auto AmmoType = PrimaryMagazine->ammoType();
								if (IsAddressValid(AmmoType))
								{
									AssemblyCSharp::ItemModProjectile* itemModProjectile = AmmoType->GetComponent<AssemblyCSharp::ItemModProjectile>((FPSystem::Type*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS(""), XS("ItemModProjectile"))));
									if (IsAddressValid(itemModProjectile))
									{
										itemModProjectile->projectileSpread() = m_settings::SilentSpread / 100;
										itemModProjectile->projectileVelocitySpread() = m_settings::SilentSpread / 100;

										Vector3 Local = a1->get_bone_transform(RustStructs::bones::head)->get_position();

										Vector3 aim_angle = GetAimDirectionToTarget(a1, BaseProjectile, m_target.m_position, m_target.m_velocity, itemModProjectile, Local);

										auto posnormal = (aim_angle - Local).Normalized();
										Vector4 toQuat = Vector4::QuaternionLookRotation(posnormal, Vector3(0, 1, 0));
										a1->eyes()->SetBodyRotation(toQuat);


									}
									
								}
								
							}
							
						}
					}
				}

			}
		}
	}

	if (m_settings::InstantRevive && UnityEngine::Input::GetKey(m_settings::InstantReviveKey))
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {

			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				AimbotTarget.m_player->ServerRPC(XS("RPC_Assist"));
			}
		}
	}

	if (m_settings::AntiDeathBarrier)
	{
		IsInsideTerrain(m_settings::AntiDeathBarrier);
	}

	if (m_settings::AdjustNoClipSpeed)
	{
		ConVar::Player::noclipspeed() = 5.f;
		ConVar::Player::noclipspeedfast() = 10.f;
		ConVar::Player::noclipspeedslow() = 2.f;
	}

	if (m_settings::FixDebugCamera)
	{
		AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), XS("client.camspeed 1"), nullptr);
	}

	if (m_settings::KeepTargetAlive && UnityEngine::Input::GetKey(m_settings::KeepAliveKey))
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {

			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				AimbotTarget.m_player->ServerRPC(XS("RPC_KeepAlive"));
			}
		}
	}

	if (m_settings::LootBodyThruWall && UnityEngine::Input::GetKey(m_settings::LootBodyThruWallKey))
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {

			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				AimbotTarget.m_player->ServerRPC(XS("RPC_LootPlayer"));
			}
		}
	}

	if (m_settings::LootCorpseThruWall && UnityEngine::Input::GetKey(m_settings::LootCorpseThruWallKey))
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {

			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				AimbotTarget.m_player->ServerRPC(XS("RPC_LootCorpse"));
			}
		}
	}

	Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);


	if (m_settings::FloorHugger)
	{
		auto modelstate = a1->modelState();

		if (IsAddressValid(modelstate))
		{
			modelstate->remove_flag(RustStructs::ModelState_Flag::OnGround);
			modelstate->flags() |= 32768;
		}
	}


	if (m_settings::Spinbot)
	{
		Vector3 remain;
		remain.x = 100;
		remain.y = my_rand() % 999 + -999;
		remain.z = 100;

		if (const auto aimAngles = a2)
		{
			if (const auto CurrentAimAngle = aimAngles->current())
			{
				CurrentAimAngle->aimAngles() = remain;
			}
		}
	}
}