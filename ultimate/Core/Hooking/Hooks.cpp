#include "Hooks.hpp"

void Hooks::BeginHooks()
{
	Hooks::Update_hk.PointerSwapHook(XS("MainMenuSystem"), HASH("Update"), &Hooks::Update_, XS(""), 0);
	Hooks::OnGUIhk.PointerSwapHook(XS("PostProcessDebug"), HASH("OnGUI"), &Hooks::OnGUI, XS("UnityEngine.Rendering.PostProcessing"), 0);
	Hooks::DoAttackhk.VirtualFunctionHook(XS("BaseProjectile"), HASH("DoAttack"), &Hooks::DoAttack, XS(""), 0);

}