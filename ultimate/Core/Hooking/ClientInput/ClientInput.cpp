#include "../hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"
#include "../../Features/Visuals/Visuals.hpp"
#include "../../Features/EyeHack/EyeHack.hpp"
#include "../../Includes/colorsettings.hpp"

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
				float num6 = _This->GetJumpHeight() + num5 + 3.2f;
				if (flyhackDistanceVertical > num6) {
					return true;
				}
				float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7 + 3.2f;
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
					float num6 = _This->GetJumpHeight() + num5 + 3.2f;

					m_settings::MaxVerticalFlyhack = num6;
					m_settings::VerticalFlyhack = flyhackDistanceVertical;

					float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num8 = 5.f + num7;

					m_settings::MaxHorisontalFlyhack = num8 + 3.2f;
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

inline bool FirstInit = false;

void GenerateAndCachePoints(float radiusX, float radiusY, float radiusZ, int baseNumPoints) {

	// Adjust the number of points to generate "x" angles
	int numPoints = baseNumPoints;

	if (Features().cachedPoints.empty()) {
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

			Features().cachedPoints.push_back(Vector3(x, y, z));
		}

		for (int i = 0; i < numPoints / 2; i++) {
			float theta = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
			float phi = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle

			float x = radiusX * Math::sinf(phi) * Math::cosf(theta);
			float y = radiusY * Math::sinf(phi) * Math::sinf(theta);
			float z = radiusZ * Math::cosf(phi);

			Features().cachedPoints.push_back(Vector3(x, y, z));
		}
	}
}

void Hooks::ClientInput(AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2)
{
	if (!InGame)
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

	if (m_settings::Flyhack_Indicator)
		CheckFlyhack(a1, m_settings::AntiFlyKick);

	//if (m_settings::BlockServerCommands)
	//{
	//	typedef FPSystem::List<uintptr_t>* (*AAA)();
	//	FPSystem::List<uintptr_t>* command_list = ((AAA)(m_game_assembly + 15031808))(); //ConsoleSystem.Index$$get_All

	//	if (command_list)
	//	{
	//		LOG(XS("[DEBUG] FoundCommandList"));
	//		auto size = *reinterpret_cast<int*>(command_list + 0x18);
	//		for (size_t i = 0; i < size; i++)
	//		{
	//			auto cmd = *reinterpret_cast<uintptr_t*>(command_list + 0x20 + i * 0x8);
	//			if (!cmd) continue;
	//			auto name = (FPSystem::String*)*reinterpret_cast<uintptr_t*>((uintptr_t)cmd + 0x10);
	//			if (!LI_FN(wcscmp)(name->str, XS(L"noclip")) //||
	//				//!LI_FN(wcscmp)(name->str, XS(L"debugcamera")) ||
	//				//!LI_FN(wcscmp)(name->str, XS(L"debug.debugcamera")) ||
	//				//!LI_FN(wcscmp)(name->str, XS(L"camspeed")) ||
	//				//!LI_FN(wcscmp)(name->str, XS(L"camlerp"))
	//				)
	//			{
	//				bool r = false;

	//				*reinterpret_cast<bool*>((uintptr_t)cmd + 0x58) = r;
	//			}
	//		}
	//	}
	//}

	if (m_settings::RocketPrediction)
	{
		auto BaseProjectile = a1->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
		if (IsAddressValid(BaseProjectile))
		{
			auto Held = a1->ActiveItem();

			if (IsAddressValid(Held))
			{
				auto HeldEntity = Held->heldEntity();
				if (HeldEntity)
				{
					auto PrefabID = HeldEntity->prefabID();

					//LOG(XS("[DEBUG] PrefabID: %zu"), PrefabID);

					//[28700] [DEBUG] PrefabID: 601440135
					if (PrefabID == 601440135)
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
									auto normalized = a1->eyes()->BodyForward().normalizeeee();

									Vector3 position = a1->eyes()->get_position(), lastposition = position, velCheck = normalized * (itemModProjectile->projectileVelocity());

									auto stats = BaseProjectile->get_stats(Held->info()->itemid());

									for (float travelTime = 0.f; travelTime < 8.f; travelTime += 0.03125f)
									{
										position += velCheck * 0.03125f;
										if (!AssemblyCSharp::IsVisible(position, lastposition, 0.18f))
											break;
										//UnityEngine::DDraw::Line(position, lastposition, Color{ 1, 0, 0, 1.f }, 0.02f, false, false);
										velCheck.y -= 9.81f * stats.gravity_modifier * 0.03125f;
										velCheck -= velCheck * stats.drag * 0.03125f;
										lastposition = position;
									}
									UnityEngine::DDraw::Sphere(position, 0.5f, Color{ 1, 1, 0, 1.f }, 0.01f, false);
								}
							}
						}
					}
				}
			}
		}
	}

	if (m_settings::GestureSpam)
	{
		float last_gesture_rpc = 0.f;

		if (UnityEngine::Time::get_fixedTime() > last_gesture_rpc + 0.35f)
		{
			switch (m_settings::gesture) {
			case 0:
				break;
			case 1:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("clap"));
				break;
			case 2:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("friendly"));
				break;
			case 3:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("thumbsdown"));
				break;
			case 4:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("thumbsup"));
				break;
			case 5:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("ok"));
				break;
			case 6:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("point"));
				break;
			case 7:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("shrug"));
				break;
			case 8:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("victory"));
				break;
			case 9:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("wave"));
				break;
			case 10:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("dance.cabbagepatch"));
				break;
			case 11:
				a1->SendSignalBroadcast(RustStructs::Signal::Gesture, XS("dance.twist"));
				break;
			}
			last_gesture_rpc = UnityEngine::Time::get_fixedTime();
		}
	}

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
	auto EyePos = LocalPlayer->eyes()->get_position();
	auto camera = UnityEngine::Camera::get_main();
	if (IsAddressValid(camera))
	{
		auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (IsAddressValid(AimbotTarget.m_player))
		{
			auto LocalPos = LocalPlayer->get_bone_transform(47)->get_position();
			auto TargetBone = AimbotTarget.m_player->get_bone_transform(AimbotTarget.m_bone)->get_position();

			if (m_settings::MemoryAimbot && UnityEngine::Input::GetKey(m_settings::MemoryAimbotKey)) {

				Vector3 va = LocalPlayer->input()->bodyAngles();
				Vector2 vb = { va.x, va.y };

				auto calc = [&](const Vector3& src, const Vector3& dst) {
					Vector3 d = src - dst;
					return Vector2(RAD2DEG(Math::my_asin(d.y / d.length())), RAD2DEG(-Math::my_atan2(d.x, -d.z)));
					};
				auto normalize = [&](float& yaw, float& pitch) {
					if (pitch < -270) pitch = -270;
					else if (pitch > 180) pitch = 180;
					if (yaw < -360) yaw = -360;
					else if (yaw > 360) yaw = 360;
					};
				auto step = [&](Vector2& angles) {
					bool smooth = true;
					Vector3 v = va;
					Vector2 va = { v.x, v.y };
					Vector2 angles_step = angles - va;
					normalize(angles_step.x, angles_step.y);

					if (smooth) {
						float factor_pitch = m_settings::AimbotSmoothness / 10;
						if (angles_step.x < 0.f) {
							if (factor_pitch > Math::fabsf(angles_step.x)) {
								factor_pitch = Math::fabsf(angles_step.x);
							}
							angles.x = va.x - factor_pitch;
						}
						else {
							if (factor_pitch > angles_step.x) {
								factor_pitch = angles_step.x;
							}
							angles.x = va.x + factor_pitch;
						}
					}
					if (smooth) {
						float factor_yaw = m_settings::AimbotSmoothness / 10;
						if (angles_step.y < 0.f) {
							if (factor_yaw > Math::fabsf(angles_step.y)) {
								factor_yaw = Math::fabsf(angles_step.y);
							}
							angles.y = va.y - factor_yaw;
						}
						else {
							if (factor_yaw > angles_step.y) {
								factor_yaw = angles_step.y;
							}
							angles.y = va.y + factor_yaw;
						}
					}
					};

				auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
				if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()))
				{
					if (AssemblyCSharp::IsVisible(Features().LocalPlayer->eyes()->get_position(), AimbotTarget.m_position))
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

									Vector3 aim_angle = GetAimDirectionToTarget(a1, BaseProjectile, AimbotTarget.m_position, AimbotTarget.m_velocity, itemModProjectile, Local);

									Vector2 offset = calc(LocalPos, aim_angle) - vb; //eyes, targetpos
									Vector2 ai = vb + offset;
									step(ai);
									step(ai);
									normalize(ai.x, ai.y);
									Vector3 i = { ai.x, ai.y, 0.0f };

									LocalPlayer->input()->bodyAngles() = i;
								}
							}
						}
					}
				}
			}

			{				
				Features().TargetID = AimbotTarget.m_player->userID();

				if (m_settings::Manipulation) {
					auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(Features().CachedManipPoint);

					if (AssemblyCSharp::IsVisible(EyePos, Features().CachedManipPoint) &&
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
					Features().CachedManipPoint = EyePos;
			}

			if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
			{
				Features().Instance()->FindManipulationAngles(num6);							
			}
			else
			{
				Features().PointVisible = false;
				if (IsAddressValid(LocalPlayer)) {
					Features().CachedManipPoint = EyePos;
					Features().ManipulationAngle = EyePos;
				}
				//Features().ManipulationAngle = Vector3();
				m_settings::can_manipulate = false;
				m_settings::StartShooting = false;
				m_settings::Manipulation_Indicator = false;
			}

			if (m_settings::CacheBulletTP) {
				{
					static float CachedGeneratedPoints;
					if (!CachedPointss) {
						CachedGeneratedPoints = m_settings::LOSCheckAmount;
						CachedPointss = true;
					}
					if (CachedGeneratedPoints > m_settings::LOSCheckAmount || CachedGeneratedPoints < m_settings::LOSCheckAmount) {
						CachedPointss = false;
						Features().GeneratedPoints = false;
					}

					if (!Features().GeneratedPoints) {
						GenerateAndCachePoints(2, 2, 2, m_settings::LOSCheckAmount);
						Features().GeneratedPoints = true;
					}
				}

				//Features().ConstantLOSCheck = false;
				 
				if (IsAddressValid(AimbotTarget.m_player)) {
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
						for (const Vector3& point : Features().cachedPoints) {
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
				else
				{
					Features().VerifiedLOSPoint = false;
					Features().ConstantLOSCheck = false;
					Features().CachedBulletTPPosition = Vector3::Zero;
					Features().LOSPoint = Vector3::Zero;
				}
			}
			
			if (m_settings::SnickerBullet) {
				UnityEngine::DDraw().Arrow(EyePos, Features().CachedManipPoint, 0.1f, Color(1.f, 0.f, 0.f, 1.f), 0.02f);
				UnityEngine::DDraw().Arrow(Features().CachedManipPoint, Features().CachedBulletTPPosition, 0.1f, Color(0.f, 1.f, 0.f, 1.f), 0.02f);
				UnityEngine::DDraw().Arrow(Features().CachedBulletTPPosition, AimbotTarget.m_position, 0.1f, Color(0.f, 0.f, 1.f, 1.f), 0.02f);							
			}

			if (m_settings::BulletTP)
			{
				if (IsAddressValid(AimbotTarget.m_player)) {
					if (m_settings::CacheBulletTP) {
						if (Features().ConstantLOSCheck) {
							Features().Instance()->FindBulletTPAngles(num6);
						}
						else
						{

							Features().CachedBulletTPPosition = AimbotTarget.m_position;
							Features().BulletTPAngle = Vector3::Zero;

							Features().BulletTPPointVisible = false;
							m_settings::Thickbullet_Indicator = false;
							m_settings::Thickbullet_AutoShoot = false;
						}
					}
					else
						Features().Instance()->FindBulletTPAngles(num6);
				}
			}
			else if (!Features().BulletTPAngle.IsZero()) {
				if (IsAddressValid(AimbotTarget.m_player)) 
					Features().CachedBulletTPPosition = AimbotTarget.m_position;
				Features().BulletTPAngle = Vector3(0, 0, 0);
				Features().BulletTPPointVisible = false;
				m_settings::Thickbullet_Indicator = false;
				m_settings::Thickbullet_AutoShoot = false;
			}
			else {
				if (IsAddressValid(AimbotTarget.m_player)) 
					Features().CachedBulletTPPosition = AimbotTarget.m_position;
			}
			
			if (m_settings::BulletTP)
			{
				if (IsAddressValid(AimbotTarget.m_player)) {
					if (AimbotTarget.m_player->IsConnected())
					{
						AimbotTarget.m_player->get_transform()->set_rotation(Vector4(0.f, 0.f, 0.f, 1.f)); //Fix all player rotations for bullet tp to not have invalids.
					}
				}
			}

			if (m_settings::Autoshoot && UnityEngine::Input::GetKey(m_settings::AutoshootKey)) {

				if (AssemblyCSharp::IsVisible(LocalPlayer->get_bone_transform(47)->get_position(), AimbotTarget.m_player->get_bone_transform(AimbotTarget.m_bone)->get_position())) {
					Features().PointVisible = true;
					StartShooting = true;
				}
				else if (m_settings::BehindWall) {
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
			else {
				StartShooting = false;
			}

			auto BaseProjectile = a1->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();

			if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
			{
				Features().BaseProjectile = BaseProjectile;

				if (IsAddressValid(Features().LocalPlayer) && IsAddressValid(Features().BaseProjectile))
				{

					if (Features().BulletTPAngle.IsZero())
						Features().BulletTPAngle = AimbotTarget.m_position;

					if (m_settings::Autoshoot && !BaseProjectile->IsA(AssemblyCSharp::FlintStrikeWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CrossbowWeapon::StaticClass()))
					{
						if (m_settings::WaitForInstantHit)
						{
							if (InstantHitReady)
							{
								if (StartShooting && Features().PointVisible)
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
								if (StartShooting && Features().PointVisible)
								{
									float last_shoot_timezz = 0.f;
									float lastShotTime = BaseProjectile->lastShotTime() - UnityEngine::Time::get_time();

									if (BaseProjectile->IsA(AssemblyCSharp::BowWeapon::StaticClass()))
									{
										if (IsAddressValid(BaseProjectile->primaryMagazine()))
										{
											if (BaseProjectile->primaryMagazine()->contents() > 0)
											{
												if (!BaseProjectile->HasAttackCooldown())
												{
													if (lastShotTime < -0.1f) {
														BaseProjectile->SendSignalBroadcast(RustStructs::Signal::Attack, XS(""));
														BaseProjectile->LaunchProjectile();
														BaseProjectile->primaryMagazine()->contents()--;
														BaseProjectile->UpdateAmmoDisplay();
														BaseProjectile->ShotFired();
														BaseProjectile->DidAttackClientside();
														BaseProjectile->BeginCycle();
														BaseProjectile->StartAttackCooldown(BaseProjectile->repeatDelay() - 0.1f);
													}
												}
												
											}
										}

									}
									else
									{
										CalledLaunchFromHook = true;
										BaseProjectile->DoAttackRecreation();
										CalledLaunchFromHook = false;
									}
								}
							}
							else if (m_settings::AlwaysAutoshoot)
							{
								if (AssemblyCSharp::IsVisible(Features().CachedManipPoint, Features().CachedBulletTPPosition))
								{
									CalledLaunchFromHook = true;
									BaseProjectile->DoAttackRecreation();
									CalledLaunchFromHook = false;
								}
							}
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

										Vector3 pos = AimbotTarget.m_position;

										if (Features().BulletTPAngle.IsZero())
											Features().BulletTPAngle = AimbotTarget.m_position;

										if (StartShooting && Features().PointVisible)
										{

											float maxpacketsperSECOND = 2;
											if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
											{
												CalledLaunchFromHook = true;
												for (int i = 0; i < 5; i++)
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

										if (StartShooting && Features().PointVisible)
										{

											float maxpacketsperSECOND = 2;
											if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
											{
												CalledLaunchFromHook = true;
												for (int i = 0; i < 5; i++)
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

										if (StartShooting && Features().PointVisible)
										{
											float maxpacketsperSECOND = 2;
											if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
											{
												CalledLaunchFromHook = true;

												int magazineContents = BaseProjectile->primaryMagazine()->contents();
												for (int i = 0; i < 5; i++)
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

			if (m_settings::RotationAimbot)
			{
				if (UnityEngine::Input::GetKey(m_settings::RotationKey))
				{
					if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()))
					{
						if (AssemblyCSharp::IsVisible(Features().LocalPlayer->eyes()->get_position(), AimbotTarget.m_position))
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

										Vector3 aim_angle = GetAimDirectionToTarget(a1, BaseProjectile, AimbotTarget.m_position, AimbotTarget.m_velocity, itemModProjectile, Local);

										auto posnormal = (aim_angle - Local).Normalized();
										Vector4 toQuat = Vector4::QuaternionLookRotation(posnormal, Vector3(0, 1, 0));

										int aimbot_percentage = (my_rand() % (100 - 1 + 1)) + 1;
										if (aimbot_percentage <= (int)m_settings::AimbotAccuracy)
										{
											a1->eyes()->SetBodyRotation(toQuat);
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
				if (AimbotTarget.m_player->HasFlag(RustStructs::PlayerFlags::Wounded))
					AimbotTarget.m_player->ServerRPC(XS("RPC_Assist"));								
			}

			if (m_settings::HammerSpam && UnityEngine::Input::GetKey(m_settings::HammerSpamKey))
			{
				auto DistanceToPlayer = AimbotTarget.m_position.Distance(a1->get_positionz());

				if (DistanceToPlayer < 5.f)
				{
					if (BaseProjectile->IsA(AssemblyCSharp::Hammer::StaticClass()))
					{
						auto hammer = reinterpret_cast<AssemblyCSharp::Hammer*>(BaseProjectile);

						auto hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
						if (!IsAddressValid(hit_test_class))
							return;

						AssemblyCSharp::HitTest* hit_test = (AssemblyCSharp::HitTest*)CIl2Cpp::il2cpp_object_new((void*)hit_test_class);
						if (IsAddressValid(hit_test))
						{
							hit_test->MaxDistance() = 1000.f;
							hit_test->HitTransform() = AimbotTarget.m_player->get_bone_transform(47);
							hit_test->AttackRay() = UnityEngine::Ray(a1->eyes()->get_position(), (AimbotTarget.m_position - a1->eyes()->get_position()).Normalized());
							hit_test->DidHit() = true;
							hit_test->HitEntity() = AimbotTarget.m_player;

							if (m_settings::HammerMaterialType == 0)
							{
								hit_test->HitMaterial() = CIl2Cpp::il2cpp_string_new(XS("Glass"));
							}
							else if (m_settings::HammerMaterialType == 1)
							{
								hit_test->HitMaterial() = CIl2Cpp::il2cpp_string_new(XS("Water"));
							}


							hit_test->HitPoint() = AimbotTarget.m_player->model()->eyeBone()->InverseTransformPoint(AimbotTarget.m_player->model()->eyeBone()->get_position() + Vector3(UnityEngine::Random::Range(-0.2f, 0.2f), UnityEngine::Random::Range(-0.2f, 0.2f), UnityEngine::Random::Range(-0.2f, 0.2f)));
							hit_test->HitNormal() = AimbotTarget.m_player->model()->eyeBone()->InverseTransformPoint(AimbotTarget.m_player->model()->eyeBone()->get_position() + Vector3(UnityEngine::Random::Range(-0.2f, 0.2f), UnityEngine::Random::Range(-0.2f, 0.2f), UnityEngine::Random::Range(-0.2f, 0.2f)));
							hit_test->damageProperties() = hammer->damageProperties();

							hammer->StartAttackCooldown(0.f);
							hammer->ProcessAttack(hit_test);

						}
					}
				}									
			}

			if (m_settings::KeepTargetAlive && UnityEngine::Input::GetKey(m_settings::KeepAliveKey))
			{
				if (AimbotTarget.m_player->HasFlag(RustStructs::PlayerFlags::Wounded))
					AimbotTarget.m_player->ServerRPC(XS("RPC_KeepAlive"));							
			}

			if (m_settings::LootBodyThruWall && UnityEngine::Input::GetKey(m_settings::LootBodyThruWallKey))
			{
				AimbotTarget.m_player->ServerRPC(XS("RPC_LootPlayer"));							
			}

			if (m_settings::LootCorpseThruWall && UnityEngine::Input::GetKey(m_settings::LootCorpseThruWallKey))
			{
				AimbotTarget.m_player->ServerRPC(XS("RPC_LootCorpse"));							
			}
		}
		else {
			m_settings::Thickbullet_AutoShoot = false;
			m_settings::Thickbullet_Indicator = false;
			m_settings::Manipulation_Indicator = false;
			StartShooting = false;
			Features().VerifiedLOSPoint = false;
			Features().ConstantLOSCheck = false;
			Features().CachedBulletTPPosition = Vector3::Zero;
			Features().LOSPoint = Vector3::Zero;
			Features().CachedManipPoint = EyePos;
			Features().ManipulationAngle = EyePos;
			Features().PointVisible = false;
			Features().BulletTPPointVisible = false;
			Features().BulletTPAngle = Vector3::Zero;
		}
	}
	else {
		m_settings::Thickbullet_AutoShoot = false;
		m_settings::Thickbullet_Indicator = false;
		m_settings::Manipulation_Indicator = false;
		StartShooting = false;
		Features().VerifiedLOSPoint = false;
		Features().ConstantLOSCheck = false;
		Features().CachedBulletTPPosition = Vector3::Zero;
		Features().LOSPoint = Vector3::Zero;
		Features().CachedManipPoint = EyePos;
		Features().ManipulationAngle = EyePos;
		Features().PointVisible = false;
		Features().BulletTPPointVisible = false;
		Features().BulletTPAngle = Vector3::Zero;
	}


	//AssemblyCSharp::UIWounded::recoveryChance() = 100.f;

	/*if (CalledLaunchFromHook)
	{
		AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), XS("client.prediction 0"), nullptr);
	}
	else
	{
		AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), XS("client.prediction 1"), nullptr);
	}*/

	auto BaseProjectile = a1->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();

	if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
	{
		Features().BaseProjectile = BaseProjectile;

		if (IsAddressValid(Features().LocalPlayer) && IsAddressValid(Features().BaseProjectile))
		{

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
								orig[0] = RecoilProperties->recoilYawMin();
								orig[1] = RecoilProperties->recoilYawMax();
								orig[2] = RecoilProperties->recoilPitchMin();
								orig[3] = RecoilProperties->recoilPitchMax();
								orig[4] = RecoilProperties->ADSScale();
								orig[5] = RecoilProperties->movementPenalty();

								StoreOrig = true;
							}

							const float amount = m_settings::recoilPercent / 100;
							RecoilProperties->recoilYawMin() = orig[0] * amount;
							RecoilProperties->recoilYawMax() = orig[1] * amount;
							RecoilProperties->recoilPitchMin() = orig[2] * amount;
							RecoilProperties->recoilPitchMax() = orig[3] * amount;
							RecoilProperties->ADSScale() = orig[4] * amount;
							RecoilProperties->movementPenalty() = orig[5] * amount;
						}
					}
				}

				//if (m_settings::SilentSpread != 100)
				//{
				//	static float orig[6];
				//	static bool StoreOrig = false;

				//	if (!StoreOrig)
				//	{
				//		
				//		orig[0] = BaseProjectile->aimCone();
				//		orig[1] = BaseProjectile->hipAimCone();
				//		orig[2] = BaseProjectile->aimConePenaltyMax();
				//		orig[3] = BaseProjectile->aimconePenaltyPerShot();
				//		orig[4] = BaseProjectile->stancePenaltyScale();

				//		if (const auto RecoilProperties = Features().BaseProjectile->recoil())
				//		{
				//			if (const auto newRecoilOverride = RecoilProperties->newRecoilOverride())
				//			{
				//				orig[5] = newRecoilOverride->aimconeCurveScale();
				//			}
				//		}

				//		StoreOrig = true;
				//	}

				//	if (m_settings::SilentSpread != 100) {
				//		const float amount = m_settings::SilentSpread;
				//		BaseProjectile->aimCone() = orig[0] * amount;
				//		BaseProjectile->hipAimCone() = orig[1] * amount;
				//		BaseProjectile->aimConePenaltyMax() = orig[2] * amount;
				//		BaseProjectile->aimconePenaltyPerShot() = orig[3] * amount;
				//		BaseProjectile->stancePenaltyScale() = orig[4] * amount;

				//		if (const auto RecoilProperties = Features().BaseProjectile->recoil())
				//		{
				//			if (const auto newRecoilOverride = RecoilProperties->newRecoilOverride())
				//			{
				//				orig[5] = orig[5] * amount;;
				//			}
				//		}
				//	}
				//}

				if (m_settings::ForceAutomatic)
				{
					if (Features().BaseProjectile->automatic() != true)
						Features().BaseProjectile->automatic() = true;
				}

				if (m_settings::NoSpread)
				{
					if (Features().BaseProjectile->stancePenalty() != 0.f)
						Features().BaseProjectile->stancePenalty() = 0.f;

					if (Features().BaseProjectile->aimconePenalty() != 0.f)
						Features().BaseProjectile->aimconePenalty() = 0.f;

					if (Features().BaseProjectile->aimCone() != 0.f)
						Features().BaseProjectile->aimCone() = 0.f;

					if (Features().BaseProjectile->hipAimCone() != 0.f)
						Features().BaseProjectile->hipAimCone() = 0.f;

					if (Features().BaseProjectile->aimconePenaltyPerShot() != 0.f)
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

					if (m_settings::IgnoreArms)
					{
						if (material->get_name()->Contains(XS("Hand")) // hand
							|| material->get_name()->Contains(XS("Glove")) // globves
							|| material->get_name()->Contains(XS("Arm"))) // full arms 
						{
							continue;
						}
					}

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
								auto GChams_BlueFlameColor1 = Color{ ColorSettings::GChams_BlueFlameColor1.r, ColorSettings::GChams_BlueFlameColor1.g, ColorSettings::GChams_BlueFlameColor1.b, ColorSettings::GChams_BlueFlameColor1.a };
								auto GChams_BlueFlameColor2 = Color{ ColorSettings::GChams_BlueFlameColor2.r, ColorSettings::GChams_BlueFlameColor2.g, ColorSettings::GChams_BlueFlameColor2.b, ColorSettings::GChams_BlueFlameColor2.a };


								MainRenderer->set_material(FireMaterialA);
								FireMaterialA->set_shader(FireShaderA);

								FireMaterialA->SetColor("_FlameColor", GChams_BlueFlameColor2);
								FireMaterialA->SetColor("_Flamecolor2", GChams_BlueFlameColor1);

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
								auto GChams_RedFlameColor1 = Color{ ColorSettings::GChams_RedFlameColor1.r, ColorSettings::GChams_RedFlameColor1.g, ColorSettings::GChams_RedFlameColor1.b, ColorSettings::GChams_RedFlameColor1.a };
								auto GChams_RedFlameColor2 = Color{ ColorSettings::GChams_RedFlameColor2.r, ColorSettings::GChams_RedFlameColor2.g, ColorSettings::GChams_RedFlameColor2.b, ColorSettings::GChams_RedFlameColor2.a };

								MainRenderer->set_material(FireMaterialB);
								FireMaterialB->set_shader(FireShaderB);

								FireMaterialB->SetColor("_FlameColor", GChams_RedFlameColor2);
								FireMaterialB->SetColor("_Flamecolor2", GChams_RedFlameColor1);

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
					case 6:
						if (RPBGalaxyBundle) {
							if (!RPBGalaxyShader) //Galaxy
								RPBGalaxyShader = RPBGalaxyBundle->LoadAsset<UnityEngine::Shader>(XS("galaxymaterial.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!RPBGalaxyMaterial)
								RPBGalaxyMaterial = RPBGalaxyBundle->LoadAsset<UnityEngine::Material>(XS("galaxymaterial_03.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != RPBGalaxyShader)
							{
								MainRenderer->set_material(RPBGalaxyMaterial);
								RPBGalaxyMaterial->set_shader(RPBGalaxyShader);
							}
						}
						break;
					case 7:
						if (GlitterBundle) {
							auto GChams_GlitterColor = Color{ ColorSettings::GChams_GlitterColor.r, ColorSettings::GChams_GlitterColor.g, ColorSettings::GChams_GlitterColor.b, ColorSettings::GChams_GlitterColor.a };
							
							if (!GlitterShader) //Glitter
								GlitterShader = GlitterBundle->LoadAsset<UnityEngine::Shader>(XS("el_glitter.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!GlitterMaterial)
								GlitterMaterial = GlitterBundle->LoadAsset<UnityEngine::Material>(XS("el_glitter.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != GlitterShader)
							{
								MainRenderer->set_material(GlitterMaterial);
								GlitterMaterial->set_shader(GlitterShader);
								GlitterMaterial->SetColor("_FresnelColor", GChams_GlitterColor);
								GlitterMaterial->SetColor("_GlitterColor", GChams_GlitterColor);
								GlitterMaterial->SetColor("_ExteriorDesignColor", GChams_GlitterColor);
							}
						}
						break;
					case 8:
						if (DamascusBundle) {
							auto GChams_DamascusColor1 = Color{ ColorSettings::GChams_DamascusColor1.r, ColorSettings::GChams_DamascusColor1.g, ColorSettings::GChams_DamascusColor1.b, ColorSettings::GChams_DamascusColor1.a };
							auto GChams_DamascusColor2 = Color{ ColorSettings::GChams_DamascusColor2.r, ColorSettings::GChams_DamascusColor2.g, ColorSettings::GChams_DamascusColor2.b, ColorSettings::GChams_DamascusColor2.a };
							auto GChams_DamascusGradient1 = Color{ ColorSettings::GChams_DamascusGradient1.r, ColorSettings::GChams_DamascusGradient1.g, ColorSettings::GChams_DamascusGradient1.b, ColorSettings::GChams_DamascusGradient1.a };
							auto GChams_DamascusPattern1 = Color{ ColorSettings::GChams_DamascusPattern1.r, ColorSettings::GChams_DamascusPattern1.g, ColorSettings::GChams_DamascusPattern1.b, ColorSettings::GChams_DamascusPattern1.a };

							if (!DamascusShader) //Glitter
								DamascusShader = DamascusBundle->LoadAsset<UnityEngine::Shader>(XS("el_designshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

							if (!DamascusMaterial)
								DamascusMaterial = DamascusBundle->LoadAsset<UnityEngine::Material>(XS("el_designeffect.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

							if (material->shader() != DamascusShader)
							{
								MainRenderer->set_material(DamascusMaterial);
								DamascusMaterial->set_shader(DamascusShader);
								DamascusMaterial->SetColor("_FresnelColor", GChams_DamascusGradient1);
								DamascusMaterial->SetColor("_InteriorColor", GChams_DamascusPattern1);
								DamascusMaterial->SetColor("_ExteriorTopColor", GChams_DamascusColor2);
								DamascusMaterial->SetColor("_ExteriorBottomColor", GChams_DamascusColor1);
								DamascusMaterial->SetFloat("_ExteriorGradientPos", m_settings::DGradientPos);
								DamascusMaterial->SetFloat("_ExterioirGredientSpread", m_settings::DGradientSpread);
							}
						}
						break;
					}
				}
			}
		}
	}

	Features().RemoveCollision();

	if (m_settings::AtmosphereContrast || m_settings::Rainbows || m_settings::NoClouds || m_settings::NoSun || m_settings::NoFog || m_settings::NoRain || m_settings::NoThunder || m_settings::NoWind || m_settings::RainbowSky) {
		if (m_settings::NoClouds)
			ConVar::Weather::set_cloud_opacity(0.f);
		else
			ConVar::Weather::set_cloud_opacity(-1.f);

		if (m_settings::NoAtmosphere)
			ConVar::Weather::set_atmosphere_brightness(5.f);
		else
			ConVar::Weather::set_atmosphere_brightness(-1.f);

		if (m_settings::AtmosphereContrast)
			ConVar::Weather::set_atmosphere_contrast(5.f);
		else
			ConVar::Weather::set_atmosphere_contrast(-1.f);

		if (m_settings::RainbowSky)
			ConVar::Weather::set_atmosphere_rayleigh(m_settings::RainbowAmount);
		else
			ConVar::Weather::set_atmosphere_rayleigh(-1.f);

		if (m_settings::NoFog)
			ConVar::Weather::set_fog(0.f);
		else
			ConVar::Weather::set_fog(-1.f);

		if (m_settings::Waves)
			ConVar::Weather::set_ocean_scale(5.f);
		else
			ConVar::Weather::set_ocean_scale(-1.f);

		if (m_settings::NoRain)
			ConVar::Weather::set_rain(0.f);
		else
			ConVar::Weather::set_rain(-1.f);

		if (m_settings::Rainbows)
			ConVar::Weather::set_rainbow(1.f);
		else
			ConVar::Weather::set_rainbow(-1.f);

		if (m_settings::NoThunder)
			ConVar::Weather::set_thunder(0.f);
		else
			ConVar::Weather::set_thunder(-1.f);

		if (m_settings::NoWind)
			ConVar::Weather::set_wind(0.f);
		else
			ConVar::Weather::set_wind(-1.f);
	}

	if (m_settings::NoMovementRestrictions)
	{
		if (AssemblyCSharp::LocalPlayer::get_Entity()->clothingBlocksAiming() != false)
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
			if (IsAddressValid(HeldEntity))
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
		if (AssemblyCSharp::LocalPlayer::get_Entity()->clothingAccuracyBonus() != 1.f)
			AssemblyCSharp::LocalPlayer::get_Entity()->clothingAccuracyBonus() = 1.f;
	}

	if (m_settings::PlayerChams) {
		if (ConVar::Culling::entityMinCullDist() != m_settings::PlayerESPDistance)
			ConVar::Culling::entityMinCullDist() = m_settings::PlayerESPDistance;
	}

	static bool ResetGameTime = false;
	if (m_settings::TimeChanger || m_settings::RemoveUnderwaterEffects || ResetGameTime)
	{
		auto admin_c = CIl2Cpp::FindClass(XS("ConVar"), XS("Admin"));
		auto instance = uint64_t(admin_c->static_fields);

		if (m_settings::TimeChanger) {
			if (*(float*)(instance + 0x0) != m_settings::GameTime)
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
			if (Mounted->canWieldItems() != true)
				Mounted->canWieldItems() = true;
		}

		//CanAttack
		if (const auto ModelState = a1->modelState())
		{
			ModelState->set_flag(RustStructs::ModelState_Flag::OnGround);
			a1->GetBaseMovement()->set_Grounded(1.f);
		}
	}

	static bool ResetPlayerFov = false;
	static bool HasResetPlayerFov = false;
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
		 
		if (m_settings::PlayerFov) {
			ResetPlayerFov = true;
			HasResetPlayerFov = false;
		}
	}
	if (ResetPlayerFov && !m_settings::PlayerFov)
	{
		auto g_graphics_ = CIl2Cpp::FindClass(XS("ConVar"), XS("Graphics"));
		auto instance = std::uint64_t(g_graphics_->static_fields);

		if (!HasResetPlayerFov) {
			*(float*)(instance + 0x18) = 90.f;
			HasResetPlayerFov = true;
		}
		ResetPlayerFov = false;
	}

	if (const auto LocalMovement = a1->movement())
	{
		if (m_settings::SpiderMan)
		{
			if (LocalMovement->groundAngle() != 0.f)
				LocalMovement->groundAngle() = 0.f;

			if (LocalMovement->groundAngleNew() != 0.f)
				LocalMovement->groundAngleNew() = 0.f;
		}

		if (m_settings::SmallerLocalRadius)
		{
			LocalMovement->capsule()->set_radius(0.44);
		}

		if (m_settings::InfiniteJump)
		{
			if (LocalMovement->landTime() != 0.f)
				LocalMovement->landTime() = 0.f;

			if (LocalMovement->jumpTime() != 0.f)
				LocalMovement->jumpTime() = 0.f;

			if (LocalMovement->groundTime() != 100000.f)
				LocalMovement->groundTime() = 100000.f;
		}

		if (m_settings::AlwaysSprint)
		{
			if (LocalMovement->sprintForced() != true)
				LocalMovement->sprintForced() = true;
		}
	}

	//if (m_settings::SilentSpread != 100)
	//{
	//	auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
	//	if (IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()))
	//	{
	//		auto PrimaryMagazine = BaseProjectile->primaryMagazine();
	//		if (IsAddressValid(PrimaryMagazine))
	//		{
	//			auto AmmoType = PrimaryMagazine->ammoType();
	//			if (IsAddressValid(AmmoType))
	//			{
	//				AssemblyCSharp::ItemModProjectile* itemModProjectile = AmmoType->GetComponent<AssemblyCSharp::ItemModProjectile>((FPSystem::Type*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS(""), XS("ItemModProjectile"))));
	//				if (IsAddressValid(itemModProjectile))
	//				{
	//					itemModProjectile->projectileSpread() = m_settings::SilentSpread / 100;
	//					itemModProjectile->projectileVelocitySpread() = m_settings::SilentSpread / 100;
	//				}
	//			}
	//		}
	//		
	//	}
	//}

	if (m_settings::AntiDeathBarrier)
	{
		IsInsideTerrain(m_settings::AntiDeathBarrier);
	}

	if (m_settings::AdjustNoClipSpeed)
	{
		if (ConVar::Player::noclipspeed() != 5.f)
			ConVar::Player::noclipspeed() = 5.f;

		if (ConVar::Player::noclipspeedfast() != 10.f)
			ConVar::Player::noclipspeedfast() = 10.f;

		if (ConVar::Player::noclipspeedslow() != 2.f)
			ConVar::Player::noclipspeedslow() = 2.f;
	}

	if (ConVar::Effects::_antialiasing() != 0)
		ConVar::Effects::_antialiasing() = 0;

	if (m_settings::FixDebugCamera)
	{
		AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), XS("client.camspeed 1"), nullptr);
	}

	if (m_settings::Suicide && UnityEngine::Input::GetKey(m_settings::SuicideKey))
	{
		a1->OnLand(-8.0001f - 100);
	}

	Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);
	
	//auto modelstate = a1->modelState();

	//if (IsAddressValid(modelstate))
	//{
	//	modelstate->remove_flag(RustStructs::ModelState_Flag::OnGround);
	//	modelstate->flags() |= 32768;
	////	modelstate->waterLevel() = 0.8;

	//	a1->playerFlags() &= ~2;

	//	
	//	a1->movement()->swimming() = true;
	//	
	//}

	//if (m_settings::FloorHugger)
	////{
	//	auto modelstate = a1->modelState();

	//	if (IsAddressValid(modelstate))
	//	{
	//		modelstate->remove_flag(RustStructs::ModelState_Flag::OnGround);
	//		modelstate->flags() |= 32768;


	//		//a1->ServerRPC("RequestParachuteDeploy");

	//		auto playermodel = a1->playerModel();
	//		if (playermodel)
	//		{
	//			auto animator = playermodel->get_animator();
	//			if (animator)
	//			{
	//				animator->SetTriggerID(playermodel->deployParachuteTrigger());
	//			}
	//		}

	//	}
	//}


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