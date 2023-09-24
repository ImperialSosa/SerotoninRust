#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"
#include "../../Features/Notifications/Notifications.hpp"


void Hooks::OnAttacked(AssemblyCSharp::BasePlayer* instance, AssemblyCSharp::HitInfo* hitinfo)
{
	if (!InGame)
		return Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);

	if (instance->IsPlayer())
	{
		/*if (hitinfo->DidHit()) {
			if (ExplosionAsset)
			{
				if (hitinfo->Initiator() == AssemblyCSharp::LocalPlayer::get_Entity() && UnityEngine::Time::get_realtimeSinceStartup() - instance->lastHeadshotSoundTime() > 0.01f)
				{
					auto camera = UnityEngine::Camera::get_main();
					if (IsAddressValid(camera)) {
						auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
						if (IsAddressValid(m_target.m_player))
						{
							ExplosionAsset->set_active(true);
							UnityEngine::GameObject().Instantiate(ExplosionAsset, m_target.m_position, m_target.m_player->eyes()->get_rotation());
						}
						else
						{
							ExplosionAsset->set_active(false);
						}
					}
					else {
						ExplosionAsset->set_active(false);
					}
					instance->lastHeadshotSoundTime() = UnityEngine::Time::get_realtimeSinceStartup();
				}
				
			}
		}*/


		if (m_settings::CustomHitSounds)
		{
			if(hitinfo->Initiator() == AssemblyCSharp::LocalPlayer::get_Entity() && UnityEngine::Time::get_realtimeSinceStartup() - instance->lastHeadshotSoundTime() > 0.01f)
			{
				typedef NTSTATUS(WINAPI * tPlaySoundW)(LPCWSTR, HMODULE, DWORD);
				tPlaySoundW PlaySoundW_ = nullptr;

				const auto image_winmm = GetImage(HASH(L"Winmm.dll"));

				if (IsAddressValid(image_winmm))
					PlaySoundW_ = (tPlaySoundW)(GetImageExport(image_winmm, HASH("PlaySoundW")));
				
				PlaySoundW_(XS(L"C:\\hitsound.wav"), NULL, 0x0001);
				instance->lastHeadshotSoundTime() = UnityEngine::Time::get_realtimeSinceStartup();
			}
		}

		if (m_settings::DisableHitSounds)
		{
			return;
		}

		if (m_settings::HitboxOverride)
		{
			int selectedHitbox = m_settings::SelectedHitbox;

			if (selectedHitbox == 0)
			{
				hitinfo->HitBone() = AssemblyCSharp::StringPool::Get(XS("Head"));
			}
		}

		if (m_settings::HitMaterial == 0) //flesh
		{
			auto stringpol = AssemblyCSharp::StringPool::Get(XS("Flesh"));
			hitinfo->HitMaterial() = stringpol;
		}
		else if (m_settings::HitMaterial == 1) //glass
		{
			auto stringpol = AssemblyCSharp::StringPool::Get(XS("Glass"));
			hitinfo->HitMaterial() = stringpol;
		}
		else if (m_settings::HitMaterial == 2) //metal
		{
			auto stringpol = AssemblyCSharp::StringPool::Get(XS("Metal"));
			hitinfo->HitMaterial() = stringpol;
		}
		else if (m_settings::HitMaterial == 3) //water
		{
			auto stringpol = AssemblyCSharp::StringPool::Get(XS("Water"));
			hitinfo->HitMaterial() = stringpol;
		}

	}
	
	Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);
}