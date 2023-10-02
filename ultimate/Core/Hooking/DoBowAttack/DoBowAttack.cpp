#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::DoAttackBow(AssemblyCSharp::BowWeapon* _This)
{
	if (!InGame)
		return Hooks::DoAttackBowhk.get_original< decltype(&DoAttackBow)>()(_This);

	if (!_This)
		return Hooks::DoAttackBowhk.get_original< decltype(&DoAttackBow)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::DoAttackBowhk.get_original< decltype(&DoAttackBow)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::DoAttackBowhk.get_original< decltype(&DoAttackBow)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::DoAttackBowhk.get_original< decltype(&DoAttackBow)>()(_This);
	}

	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();

	if (m_settings::Autoshoot && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		if (IsAddressValid(LocalPlayer)) {
			auto eyes = LocalPlayer->eyes();
			if (IsAddressValid(eyes)) {
				if (AssemblyCSharp::IsVisible(eyes->get_position() + Features().ManipulationAngle, Features().BulletTPAngle))
				{
					_This->attackReady() = false;
					if (_This->primaryMagazine()->contents() <= 0)
					{
						_This->TryReload();
						return;
					}

					AssemblyCSharp::ItemDefinition* ammoType = _This->primaryMagazine()->ammoType();
					_This->primaryMagazine()->contents()--;
					_This->StartAttackCooldown(_This->repeatDelay());

					_This->GetOwnerPlayer()->SendSignalBroadcast(RustStructs::Signal::Attack, XS(""));
					if (_This->viewModel())
					{
						_This->viewModel()->Play(XS("attack"), 0);
					}

					AssemblyCSharp::ItemModProjectile* component = ammoType->GetComponent<AssemblyCSharp::ItemModProjectile>(FPSystem::Type::ItemModProjectile());

					_This->LaunchProjectileClientside(ammoType, component->numProjectiles(), m_settings::SilentSpread / 100.f);

					_This->TryReload();
					_This->UpdateAmmoDisplay();
					_This->DidAttackClientside();
				}
			}
		}
	}
	else
	{
		return Hooks::DoAttackBowhk.get_original< decltype(&DoAttackBow)>()(_This);
	}
}