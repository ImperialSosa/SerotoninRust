#include "../hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"

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
				float num6 = _This->GetJumpHeight() + num5 + 3.5f;
				if (flyhackDistanceVertical > num6) {
					return true;
				}
				float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7 + 3.5;
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
					float num6 = _This->GetJumpHeight() + num5 + 3.0f;

					m_settings::MaxVerticalFlyhack = num6;
					m_settings::VerticalFlyhack = flyhackDistanceVertical;

					float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num8 = 5.f + num7;

					m_settings::MaxHorisontalFlyhack = num8 + 3.0f;
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



inline void DoOreAttack(Vector3 pos, AssemblyCSharp::BaseEntity* p, AssemblyCSharp::BaseMelee* w)
{
	if (!InGame)
		return;

	if (!IsAddressValid(p)) return;
	if (!IsAddressValid(w)) return;

	if (w->nextAttackTime() >= UnityEngine::Time::get_time()) return;
	if (w->timeSinceDeploy() < w->deployDelay()) return;

	auto g_hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
	auto g_hit_test = (AssemblyCSharp::HitTest*)CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);

	auto trans = p->get_transform();
	if (!trans) return;
	UnityEngine::Ray r = UnityEngine::Ray(AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position(), (pos - AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position()).Normalized());

	g_hit_test->MaxDistance() = 1000.f;
	g_hit_test->HitTransform() = trans;
	g_hit_test->AttackRay() = r;
	g_hit_test->DidHit() = true;
	g_hit_test->HitEntity() = p;
	g_hit_test->HitPoint() = trans->InverseTransformPoint(pos);
	g_hit_test->HitNormal() = Vector3(0, 0, 0); //trans->InverseTransformDirection(pos)
	g_hit_test->damageProperties() = w->damageProperties();

	w->StartAttackCooldown(w->repeatDelay());

	return w->ProcessAttack((AssemblyCSharp::HitTest*)g_hit_test);
}

inline bool FirstInit = false;

void Hooks::ClientInput(AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2)
{
	if(!InGame)
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		Features().Instance()->LocalPlayer = a1;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(ToAddress(Hooks::ProjectileShootHookhk.get_original<void*>()))
		|| !IsAddressValid(ToAddress(Hooks::PPA_WriteToStreamhk.get_original<void*>())))
	{
		Hooks::ProjectileShootHookhk.VirtualFunctionHook(XS("ProjectileShoot"), HASH("WriteToStream"), &Hooks::ProjectileShootHook, XS("ProtoBuf"), 1);
		Hooks::PPA_WriteToStreamhk.VirtualFunctionHook(XS("PlayerProjectileAttack"), HASH("WriteToStream"), &Hooks::PPA_WriteToStream, XS("ProtoBuf"), 1);
	}

	if (!FirstInit)
	{
		Hooks::TryToMovehk.VirtualFunctionHook(XS("ItemIcon"), HASH("TryToMove"), &Hooks::TryToMove, XS(""), 0);
		Hooks::PlayerWalkMovementhk.VirtualFunctionHook(XS("PlayerWalkMovement"), HASH("ClientInput"), &Hooks::PlayerWalkMovement, XS(""), 2);
		FirstInit = true;
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

	if (UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = .99f;
	}
	else
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = 0.05f;
	}

	if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		Features().Instance()->FindManipulationAngles(num6);
	}
	else
	{
		Features().ManipulationAngle = Vector3();
		m_settings::can_manipulate = false;
		m_settings::StartShooting = false;
		m_settings::Manipulation_Indicator = false;
	}


	if (m_settings::BulletTP)
	{
		Features().Instance()->FindBulletTPAngles(num6);
	}
	else if (!Features().BulletTPAngle.IsZero()) {
		Features().BulletTPAngle = Vector3(0, 0, 0);
		m_settings::Thickbullet_Indicator = false;
		m_settings::Thickbullet_AutoShoot = false;
	}

	auto BaseProjectile = a1->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
	auto base_melee = a1->GetHeldEntityCast<AssemblyCSharp::BaseMelee>();

	if (IsAddressValid(Features().LocalPlayer) && IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
	{
		Features().AutoShoot(BaseProjectile);
		Features().FastBullet(BaseProjectile);
		Features().BulletQueue(BaseProjectile);
		Features().AutoReload(BaseProjectile);

		if (m_settings::NoWeaponBob)
		{
			auto ActiveModel = AssemblyCSharp::BaseViewModel::get_ActiveModel();

			if (IsAddressValid(ActiveModel))
			{

				if (IsAddressValid(ActiveModel->bob()))
				{
					ActiveModel->bob()->bobAmountRun() = { 0.f, 0.f, 0.f, 0.f };
					ActiveModel->bob()->bobAmountWalk() = { 0.f, 0.f, 0.f, 0.f };
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

		if (BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::Planner::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::JackHammer::StaticClass()))
		{

			if (m_settings::ChangeRecoil)
			{
				if (const auto RecoilProperties = BaseProjectile->recoil())
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
							//orig[4] = newRecoilOverride->ADSScale();
							//orig[5] = newRecoilOverride->movementPenalty();

							StoreOrig = true;
						}

						const float amount = m_settings::recoilPercent / 100;
						const float amountY = m_settings::RecoilPercentY / 100;
						newRecoilOverride->recoilYawMin() = orig[0] * amount;
						newRecoilOverride->recoilYawMax() = orig[1] * amount;
						newRecoilOverride->recoilPitchMin() = orig[2] * amountY;
						newRecoilOverride->recoilPitchMax() = orig[3] * amountY;
						//newRecoilOverride->ADSScale() = orig[4] * amount;
						//newRecoilOverride->movementPenalty() = orig[5] * amount;
					}
					else
					{
						if (!StoreOrig)
						{
							orig[0] = RecoilProperties->recoilYawMin();
							orig[1] = RecoilProperties->recoilYawMax();
							orig[2] = RecoilProperties->recoilPitchMin();
							orig[3] = RecoilProperties->recoilPitchMax();
							//orig[4] = RecoilProperties->ADSScale();
							//orig[5] = RecoilProperties->movementPenalty();

							StoreOrig = true;
						}

						const float amount = m_settings::recoilPercent / 100;
						const float amountY = m_settings::RecoilPercentY / 100;
						RecoilProperties->recoilYawMin() = orig[0] * amount;
						RecoilProperties->recoilYawMax() = orig[1] * amount;
						RecoilProperties->recoilPitchMin() = orig[2] * amountY;
						RecoilProperties->recoilPitchMax() = orig[3] * amountY;
					}
				}
			}

			if (m_settings::ForceAutomatic)
			{
				BaseProjectile->automatic() = true;
			}

			if (m_settings::NoSpread)
			{
				BaseProjectile->stancePenalty() = 0.f;
				BaseProjectile->aimconePenalty() = 0.f;
				BaseProjectile->aimCone() = 0.f;
				BaseProjectile->hipAimCone() = 0.f;
				BaseProjectile->aimconePenaltyPerShot() = 0.f;
			}

			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (m_settings::WeaponSpammer && UnityEngine::Input::GetKey(m_settings::WeaponSpamKey))
			{
				float delay = m_settings::WeaponSpamDelay / 100;
				if (current_time - send_time > delay)
				{
					BaseProjectile->SendSignalBroadcast(RustStructs::Signal::Attack, XS(""));
					send_time = current_time;
				}
			}
		}
		else
		{
			if (m_settings::InstantHeal)
			{

				float nextActionTime = 0, period = 1.4721;
				auto health = a1->_health();

				auto Held = a1->GetHeldItemSafe();

				if (Held)
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

	Features().RemoveCollision();


	if (m_settings::NoMovementRestrictions)
	{
		AssemblyCSharp::LocalPlayer::get_Entity()->clothingBlocksAiming() = false;
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
		if (UnityEngine::Input::GetKey(m_settings::AdminCheatKey))
			a1->GetBaseMovement()->adminCheat() = true;
		else
			a1->GetBaseMovement()->adminCheat() = false;
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