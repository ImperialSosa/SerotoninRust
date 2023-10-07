#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::LateUpdate(AssemblyCSharp::TOD_Sky* _This)
{
	if (!InGame)
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (!IsAddressValid(_This))
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);
	}

	if (IsAddressValid(_This)) {
		if (m_settings::CustomSky) {
			if (IsAddressValid(_This->Night()))
			{
				auto Night = _This->Night();
				if (IsAddressValid(Night))
				{
					Night->LightIntensity() = 20.f;
					Night->AmbientMultiplier() = 2.f;
					Night->ReflectionMultiplier() = 1.f;
				}

				if (IsAddressValid(_This->Ambient()))
				{
					_This->Ambient()->Saturation() = 2.f;
				}

				if (IsAddressValid(_This->Atmosphere()))
				{
					_This->Atmosphere()->Brightness() = 5.f;
					_This->Atmosphere()->Fogginess() = 0.f;
				}
				
				m_settings::GameTime = 6.5f;

				auto Ambient = Night->AmbientColor();
				if (IsAddressValid(Ambient))
				{
					uintptr_t AmbientColor = *reinterpret_cast<uintptr_t*>(Ambient + 0x10);
					if (IsAddressValid(AmbientColor))
					{
						*reinterpret_cast<Vector4*>(AmbientColor) = { 0.8f, 0.8f, 0.8f, 0.8f };
					}
				}
				//*(Vector4*)(AmbientColor) = { 0.8f, 0.8f, 0.8f, 0.8f };

				auto Clouds = _This->Clouds();
				if (IsAddressValid(Clouds))
				{
					Clouds->Sharpness() = 1.f;
				}
				

				auto CloudColor = Night->CloudColor();
				if (IsAddressValid(CloudColor))
				{
					uintptr_t CloudsColor = *reinterpret_cast<uintptr_t*>(CloudColor + 0x10);
					*reinterpret_cast<Vector4*>(CloudsColor) = { 1.f, 1.f, 1.f, 1.f };
					//*(Vector4*)(CloudsColor) = { 1.f, 1.f, 1.f, 1.f };
				}

				if (IsAddressValid(_This->Stars()))
				{
					_This->Stars()->Brightness() = 150.f;
				}
			}
		}

		if (IsAddressValid(_This->Night()))
		{
			auto Night = _This->Night();

			if (m_settings::Brightnight) {
				Night->LightIntensity() = 20.f;
				Night->AmbientMultiplier() = 4.f;
				Night->ReflectionMultiplier() = 1.f;
			}

			if (m_settings::BrightAmbient) {
				auto Ambient = Night->AmbientColor();
				if (IsAddressValid(Ambient))
				{
					uintptr_t AmbientColor = *reinterpret_cast<uintptr_t*>(Ambient + 0x10);
					*reinterpret_cast<Vector4*>(AmbientColor) = { 0.8f, 0.8f, 0.8f, 0.8f };
				}
				
				//*(Vector4*)(AmbientColor) = { 0.8f, 0.8f, 0.8f, 0.8f };
			}

			if (m_settings::SkyColorNight) {
				auto Sky = Night->SkyColor();
				if (IsAddressValid(Sky))
				{
					uintptr_t SkyColor = *reinterpret_cast<uintptr_t*>(Sky + 0x10);
					*reinterpret_cast<Color*>(SkyColor) = Color(66.f, 245.f, 206.f, 255.f).GetUnityColor();
				}
				//*(Color*)(SkyColor) = Color(66.f, 245.f, 206.f, 255.f).GetUnityColor();
			}

			if (m_settings::SharpClouds) {
				auto Clouds = Night->CloudColor();
				if (IsAddressValid(Clouds))
				{
					uintptr_t CloudColor = *reinterpret_cast<uintptr_t*>(Clouds + 0x10);
					*reinterpret_cast<Color*>(CloudColor) = Color(255.f, 255.f, 255.f, 255.f).GetUnityColor();
				}
				//*(Color*)(CloudColor) = Color(255.f, 255.f, 255.f, 255.f).GetUnityColor();
			}
		}

		if (IsAddressValid(_This->Day()))
		{
			auto Day = _This->Day();

			if (IsAddressValid(Day))
			{
				if (m_settings::SkyColorDay) {
					auto Sky = Day->SkyColor();
					if (IsAddressValid(Sky))
					{
						uintptr_t SkyColor = *reinterpret_cast<uintptr_t*>(Sky + 0x10);
						*reinterpret_cast<Color*>(SkyColor) = Color(66.f, 245.f, 206.f, 255.f).GetUnityColor();
					}
					//*(Color*)(SkyColor) = Color(66.f, 245.f, 206.f, 255.f).GetUnityColor();
				}

				if (m_settings::BrightCave) {
					Day->AmbientMultiplier() = 1.f;
					Day->ReflectionMultiplier() = 1.f;
				}
			}
		
		}

		if (IsAddressValid(_This->Stars()))
		{
			auto Stars = _This->Stars();
			if (IsAddressValid(Stars))
			{
				if (m_settings::Stars) {
					Stars->Brightness() = 150.f;
				}
			}
		}
	}

	return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);
}