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
	/*	char str[256];
		sprintf(str, XS("Hit: %ls for %d hp"), instance->get_displayName()->c_str(), (int)hitinfo->damageTypes()->Total());

		std::string strz = str;
		const auto string = std::wstring(strz.begin(), strz.end());
		notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());*/



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