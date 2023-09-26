#include "Prediction.hpp"
#include "../../Features/Features/Features.hpp"

void VelocityAimbot(AssemblyCSharp::BaseProjectile* BaseProjectile)
{
	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
	auto ActiveItem = LocalPlayer->ActiveItem();
	auto HeldItem = ActiveItem->GetHeldEntity();
	auto PrefabID = HeldItem->prefabID();

	auto camera = UnityEngine::Camera::get_main();
	if (IsAddressValid(camera)) {
		auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
		if (IsAddressValid(m_target.m_player)) {
			if (m_settings::VelocityAimbot)
			{
				if (IsAddressValid(ActiveItem)) {
					if (PrefabID == 2836331625 || PrefabID == 4279856314) //bow / Nailgun
					{
						if (AssemblyCSharp::IsVisible(LocalPlayer->get_bone_transform(48)->get_position(), Features().BulletTPAngle))
						{
							BaseProjectile->projectileVelocityScale() = 1.f;
							m_settings::DoVelocityPrediction = false;
						}
						else {

							m_settings::DoVelocityPrediction = true;
							auto TotalHeight = Features().BulletTPAngle.y;

							if (m_target.m_distance <= 95)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.41;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.46;
								else
									BaseProjectile->projectileVelocityScale() = 0.36;
							}
							else if (m_target.m_distance > 95 && m_target.m_distance <= 120)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.46;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.51;
								else
									BaseProjectile->projectileVelocityScale() = 0.41;
							}
							else if (m_target.m_distance > 120 && m_target.m_distance <= 140)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.51;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.56;
								else
									BaseProjectile->projectileVelocityScale() = 0.46; //0.455
							}
							else if (m_target.m_distance > 140 && m_target.m_distance <= 180)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.56;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.61;
								else
									BaseProjectile->projectileVelocityScale() = 0.51;
							}
							else if (m_target.m_distance > 180 && m_target.m_distance <= 220)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.61;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.65;
								else
									BaseProjectile->projectileVelocityScale() = 0.56;
							}
							else if (m_target.m_distance > 220 && m_target.m_distance <= 275)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.65;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.71;
								else
									BaseProjectile->projectileVelocityScale() = 0.61;
							}
							else if (m_target.m_distance > 275 && m_target.m_distance <= 300)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.71;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.76;
								else
									BaseProjectile->projectileVelocityScale() = 0.66;
							}
							else if (m_target.m_distance > 300 && m_target.m_distance <= 335)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.76;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.81;
								else
									BaseProjectile->projectileVelocityScale() = 0.71;
							}
							else if (m_target.m_distance > 335 && m_target.m_distance <= 360)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.81;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.86;
								else
									BaseProjectile->projectileVelocityScale() = 0.76;
							}
							else if (m_target.m_distance > 360 && m_target.m_distance <= 380)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.86;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.91;
								else
									BaseProjectile->projectileVelocityScale() = 0.81;
							}
							else if (m_target.m_distance > 380 && m_target.m_distance <= 400)
							{
								if (TotalHeight > 25 && TotalHeight <= 50)
									BaseProjectile->projectileVelocityScale() = 0.91;
								else if (TotalHeight > 50)
									BaseProjectile->projectileVelocityScale() = 0.96;
								else
									BaseProjectile->projectileVelocityScale() = 0.86;
							}
						}
					}
					else if (PrefabID == 2545523575 || PrefabID == 3759841439) { //mp4a5, custom-smg
						if (AssemblyCSharp::IsVisible(LocalPlayer->get_bone_transform(48)->get_position(), Features().BulletTPAngle))
						{
							BaseProjectile->projectileVelocityScale() = 0.8f;
							m_settings::DoVelocityPrediction = false;
						}
						else {

							m_settings::DoVelocityPrediction = true;
							auto TotalHeight = Features().BulletTPAngle.y;

							float Testing = 0.f;
							if (!AssemblyCSharp::IsVisible(LocalPlayer->get_bone_transform(48)->get_position(), Features().BulletTPAngle) && TotalHeight > 10)
								Testing += 0.2f;
							else
								Testing = 0.f;

							if (m_target.m_distance <= 160)
								BaseProjectile->projectileVelocityScale() = 0.27 + Testing;
							else if (m_target.m_distance > 160 && m_target.m_distance <= 170)
								BaseProjectile->projectileVelocityScale() = 0.28 + Testing;
							else if (m_target.m_distance > 170 && m_target.m_distance <= 174)
								BaseProjectile->projectileVelocityScale() = 0.29 + Testing;
							else if (m_target.m_distance > 174 && m_target.m_distance <= 180)
								BaseProjectile->projectileVelocityScale() = 0.30 + Testing;
							else if (m_target.m_distance > 180 && m_target.m_distance <= 190)
								BaseProjectile->projectileVelocityScale() = 0.31 + Testing;
							else if (m_target.m_distance > 190 && m_target.m_distance <= 194)
								BaseProjectile->projectileVelocityScale() = 0.32 + Testing;
							else if (m_target.m_distance > 194 && m_target.m_distance <= 200)
								BaseProjectile->projectileVelocityScale() = 0.33 + Testing;
							else if (m_target.m_distance > 200 && m_target.m_distance <= 205)
								BaseProjectile->projectileVelocityScale() = 0.34 + Testing;
							else if (m_target.m_distance > 205 && m_target.m_distance <= 210)
								BaseProjectile->projectileVelocityScale() = 0.35 + Testing;
							else if (m_target.m_distance > 212 && m_target.m_distance <= 220)
								BaseProjectile->projectileVelocityScale() = 0.36 + Testing;
							else if (m_target.m_distance > 220 && m_target.m_distance <= 225)
								BaseProjectile->projectileVelocityScale() = 0.37 + Testing;
							else if (m_target.m_distance > 225 && m_target.m_distance <= 230)
								BaseProjectile->projectileVelocityScale() = 0.38 + Testing;
							else if (m_target.m_distance > 230 && m_target.m_distance <= 240)
								BaseProjectile->projectileVelocityScale() = 0.39 + Testing;
							else if (m_target.m_distance > 240 && m_target.m_distance <= 245)
								BaseProjectile->projectileVelocityScale() = 0.40 + Testing;
							else if (m_target.m_distance > 245 && m_target.m_distance <= 250)
								BaseProjectile->projectileVelocityScale() = 0.41 + Testing;
							else if (m_target.m_distance > 250 && m_target.m_distance <= 258)
								BaseProjectile->projectileVelocityScale() = 0.42 + Testing;
							else if (m_target.m_distance > 258 && m_target.m_distance <= 265)
								BaseProjectile->projectileVelocityScale() = 0.43 + Testing;
							else if (m_target.m_distance > 265 && m_target.m_distance <= 270)
								BaseProjectile->projectileVelocityScale() = 0.44 + Testing;
							else if (m_target.m_distance > 270 && m_target.m_distance <= 275)
								BaseProjectile->projectileVelocityScale() = 0.45 + Testing;
							else if (m_target.m_distance > 275 && m_target.m_distance <= 285)
								BaseProjectile->projectileVelocityScale() = 0.46 + Testing;
							else if (m_target.m_distance > 285 && m_target.m_distance <= 290)
								BaseProjectile->projectileVelocityScale() = 0.47 + Testing;
							else if (m_target.m_distance > 290 && m_target.m_distance <= 295)
								BaseProjectile->projectileVelocityScale() = 0.48 + Testing;
							else if (m_target.m_distance > 295 && m_target.m_distance <= 300)
								BaseProjectile->projectileVelocityScale() = 0.49 + Testing;
							else if (m_target.m_distance > 300)
								BaseProjectile->projectileVelocityScale() = 0.80f;
						}
					}
					else {
						m_settings::DoVelocityPrediction = false;

						static float orig[10];

						if (PrefabID == 1978739833 || PrefabID == 1537401592 || PrefabID == 3474489095 || PrefabID == 3243900999 || //ak, compound, doublebarrel, tommy
							PrefabID == 2696589892 || PrefabID == 1877401463 || PrefabID == 4231282088 || PrefabID == 563371667 || //waterpipe, spas-12, semi-rifle, semi-pistol
							PrefabID == 2477536592 || PrefabID == 554582418 || PrefabID == 3305012504 || PrefabID == 636374895 ||  //revolver, pump, python, prototype-17
							PrefabID == 2293870814 || PrefabID == 844375121  || PrefabID == 2176761593) {  //m92-pistol, lr-300, eoka
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
			}
		}
	}
}

void Hooks::ProjectileShootHook(ProtoBuf::ProjectileShoot* _This, ProtoBuf::Stream* Stream)
{
	if(!InGame)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	m_settings::fixed_time_last_shot = UnityEngine::Time::get_fixedTime();
	m_settings::just_shot = true;
	m_settings::did_reload = false;

	if(!m_settings::SilentAim)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(AimbotTarget.m_player))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (!IsAddressValid(Features().BaseProjectile))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (Features().BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);


	if (!Features().LocalPlayer->IsWeapon())
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto PrimaryMagazine = Features().BaseProjectile->primaryMagazine();
	if (!IsAddressValid(PrimaryMagazine))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto AmmoType = PrimaryMagazine->ammoType();
	if (!IsAddressValid(AmmoType))
		return 	Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto created_projectiles = Features().BaseProjectile->createdProjectiles();
	if (!created_projectiles)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto created_projectiles_ = created_projectiles->_items;
	if (!created_projectiles_)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto created_projectiles_size = created_projectiles->_size;

	auto projectile_shoot_projectiles = _This->projectiles();
	if (!projectile_shoot_projectiles)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto projectile_shoot_items = projectile_shoot_projectiles->_items;
	if (!projectile_shoot_items)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (Features().BulletTPAngle.IsZero())
	{
		Features().BulletTPAngle = AimbotTarget.m_position;
	}

	auto projectile_shoot_size = projectile_shoot_projectiles->_size;

	Vector3 StartPosition;
	Vector3 OriginalVelocity;
	Vector3 m_aim_angle;

	bool visible = false;
	bool manipulated = false;

	//Velocity Bow/Nailgun
	if (m_settings::VelocityAimbot) {
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		auto ActiveItem = LocalPlayer->ActiveItem();
		auto HeldItem = ActiveItem->GetHeldEntity();
		auto PrefabID = HeldItem->prefabID();

		if (ActiveItem) {
			VelocityAimbot(Features().BaseProjectile);
		}
		else
			m_settings::DoVelocityPrediction = false;
	}
	else
		m_settings::DoVelocityPrediction = false;

	for (std::int32_t index = 0; index < projectile_shoot_size; index++)
	{
		auto c_projectile = projectile_shoot_items->m_Items[index];
		if (!c_projectile) continue;

		StartPosition = c_projectile->startPos();
		if (StartPosition.IsZero()) continue;

		OriginalVelocity = c_projectile->startVel();
		if (OriginalVelocity.IsZero()) continue;

		if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
		{
			auto rpcposv2 = StartPosition;
			if (Features().ManipulationAngle != Vector3(0, 0, 0))
			{
				StartPosition += (Features().ManipulationAngle);

				visible = AssemblyCSharp::IsVisible(StartPosition, Features().BulletTPAngle, 0.2f);

				if (StartPosition != rpcposv2)
				{
					manipulated = true;

					if (visible)
					{
						visible = true;

						c_projectile->startPos() = StartPosition;
					}
				}
			}
		}
	}


	for (std::int32_t index = 0; index < created_projectiles_size; index++)
	{
		auto c_projectile = *(AssemblyCSharp::Projectile**)((uintptr_t)created_projectiles_ + 0x20 + index * 0x8);
		if (!c_projectile)
			continue;




		LaunchedProjectileSize = created_projectiles_size;

		if (m_settings::BulletTP)
		{
			if (CalledLaunchFromHook)
			{
				c_projectile->integrity() = 0.f;
				LaunchedProjectilesArray[index] = c_projectile;
			}
		}


		AssemblyCSharp::ItemModProjectile* itemModProjectile = AmmoType->GetComponent<AssemblyCSharp::ItemModProjectile>((FPSystem::Type*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS(""), XS("ItemModProjectile"))));

		if (AimbotTarget.m_heli && m_settings::HeliAimbot)
		{
			Vector3 aim_angle = GetAimDirectionToTarget(Features().LocalPlayer, Features().BaseProjectile, AimbotTarget.m_position, AimbotTarget.m_velocity, itemModProjectile, StartPosition) - StartPosition;
			m_aim_angle = (aim_angle).Normalized() * OriginalVelocity.Length();
		}
		else
		{
			if (m_settings::DoVelocityPrediction) {
				Vector3 a;
				float travel_time = 0.f;
				SimulateProjectile(AimbotTarget.m_player, StartPosition, Features().BulletTPAngle, m_aim_angle, a, travel_time, c_projectile, Features().BaseProjectile, itemModProjectile, AimbotTarget.m_velocity);
			}
			else {
				Vector3 aim_angle = GetAimDirectionToTarget(Features().LocalPlayer, Features().BaseProjectile, Features().BulletTPAngle, AimbotTarget.m_velocity, itemModProjectile, StartPosition) - StartPosition;
				m_aim_angle = (aim_angle).Normalized() * OriginalVelocity.Length();
			}
		}
	}

	int aimbot_percentage = (my_rand() % (100 - 1 + 1)) + 1;
	for (std::int32_t index = 0; index < projectile_shoot_size; index++)
	{
		auto c_projectile = projectile_shoot_items->m_Items[index];
		if (!c_projectile) continue;

		if (aimbot_percentage <= (int)m_settings::AimbotAccuracy)
		{
			if (AimbotTarget.m_player || manipulated) {
				c_projectile->startVel() = m_aim_angle;
			}
		}
	}

	constexpr float delta_time = 0.03125f;

	for (std::int32_t index = 0; index < created_projectiles_size; index++)
	{
		auto c_projectile = *(Projectile**)((uintptr_t)created_projectiles_ + 0x20 + index * 0x8);
		if (!c_projectile) 
			continue;

		if (aimbot_percentage <= (int)m_settings::AimbotAccuracy)
		{
			if (AimbotTarget.m_player || manipulated) {
				c_projectile->initialVelocity() = m_aim_angle;
				c_projectile->currentVelocity() = m_aim_angle;
			}
		}

		if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
		{
			//visible = AssemblyCSharp::IsVisible(StartPosition, m_target.m_position);
			visible = AssemblyCSharp::IsVisible(StartPosition, Features().BulletTPAngle);


			if (visible)
			{
				if (manipulated)
				{
					auto g = c_projectile->get_gameObject();
					if (!IsAddressValid(g))
						continue;


					auto t = g->get_transform();
					if (!IsAddressValid(t))
						continue;

					t->set_position(StartPosition);
				}
			}
		}
	}

	created_projectiles->Clear();

	return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);
}