#include "Prediction.hpp"
#include "../../Features/Features/Features.hpp"


void Hooks::ProjectileShootHook(ProtoBuf::ProjectileShoot* _This, ProtoBuf::Stream* Stream)
{
	if(!InGame)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if(!m_settings::SilentAim)
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(AimbotTarget.m_player))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
	if (!IsAddressValid(BaseProjectile))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	if (BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);


	if (!Features().LocalPlayer->IsWeapon())
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto PrimaryMagazine = BaseProjectile->primaryMagazine();
	if (!IsAddressValid(PrimaryMagazine))
		return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto AmmoType = PrimaryMagazine->ammoType();
	if (!IsAddressValid(AmmoType))
		return 	Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);

	auto created_projectiles = BaseProjectile->createdProjectiles();
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


		AssemblyCSharp::ItemModProjectile* itemModProjectile = AmmoType->GetComponent<AssemblyCSharp::ItemModProjectile>((FPSystem::Type*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS(""), XS("ItemModProjectile"))));


		if (AimbotTarget.m_heli && m_settings::HeliAimbot)
		{
			Vector3 aim_angle = GetAimDirectionToTarget(Features().LocalPlayer, BaseProjectile, AimbotTarget.m_position, AimbotTarget.m_velocity, itemModProjectile, StartPosition) - StartPosition;
			m_aim_angle = (aim_angle).Normalized() * OriginalVelocity.Length();
		}
		else
		{
			Vector3 aim_angle = GetAimDirectionToTarget(Features().LocalPlayer, BaseProjectile, Features().BulletTPAngle, AimbotTarget.m_velocity, itemModProjectile, StartPosition) - StartPosition;
			m_aim_angle = (aim_angle).Normalized() * OriginalVelocity.Length();
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
		if (!c_projectile) continue;

		if (aimbot_percentage <= (int)m_settings::AimbotAccuracy)
		{
			if (AimbotTarget.m_player || manipulated) {
				c_projectile->currentVelocity() = m_aim_angle;
			}
		}



		LaunchedProjectileSize = created_projectiles_size;

		if (m_settings::BulletTP)
		{
			if (CalledLaunchFromHook)
			{
				c_projectile->integrity() = 0.f;
				LaunchedProjectilesArray[index] = c_projectile;
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

	return Hooks::ProjectileShootHookhk.get_original< decltype(&ProjectileShootHook)>()(_This, Stream);
}