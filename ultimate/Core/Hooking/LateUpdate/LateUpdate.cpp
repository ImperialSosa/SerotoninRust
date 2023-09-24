#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::LateUpdate(AssemblyCSharp::TOD_Sky* _This)
{
	if (!InGame)
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (!_This)
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
		//if (m_settings::Brightnight) {
		//	if (_This->Night())
		//	{
		//		auto Night = _This->Night();

		//		Night->LightIntensity() = 20.f;
		//		Night->AmbientMultiplier() = 2.f;
		//		Night->ReflectionMultiplier() = 1.f;
		//		//_This->Ambient()->Saturation() = 2.f;
		//		//_This->Atmosphere()->Brightness() = 5.f;
		//		//_This->Atmosphere()->Fogginess() = 0.f;
		//		

		//		auto Ambient = Night->AmbientColor();
		//		uintptr_t AmbientColor = *(uintptr_t*)(Ambient + 0x10);
		//		*(Vector4*)(AmbientColor) = { 0.8f, 0.8f, 0.8f, 0.8f };
		//	}
		//}
	}

	return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);
}