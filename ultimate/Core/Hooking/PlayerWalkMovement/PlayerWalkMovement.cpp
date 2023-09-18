#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::PlayerWalkMovement(AssemblyCSharp::PlayerWalkMovement* _This, AssemblyCSharp::InputState* _State, AssemblyCSharp::ModelState* _ModelState)
{
	if (!InGame)
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	if (!_This || !_State || !_ModelState)
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	if (!IsAddressValid(Features().LocalPlayer))
	{
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);
	}

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);



	if (m_settings::AdminFlags)
		_ModelState->remove_flag(RustStructs::ModelState_Flag::Flying);

	auto g_local_player = AssemblyCSharp::LocalPlayer::get_Entity();
	if (g_local_player)
	{
		if (!_This->flying())
		{
			if (m_settings::OmniSprint)
			{
				Vector3 vel = _This->get_TargetMovement();
				_ModelState->SetSprinting(true);

				float max_speed = (g_local_player->IsSwimming() || _ModelState->get_ducked() > 0.5) ? 1.7f : 5.5f;
				if (vel.Length() > 0.f) {
					Vector3 target_vel = Vector3(vel.x / vel.Length() * max_speed, vel.y, vel.z / vel.Length() * max_speed);
					_This->set_TargetMovement(target_vel);
				}
			}
		}

		if (m_settings::InteractiveDebug && UnityEngine::Input::GetKey(m_settings::InteractiveKey))
		{
			_ModelState->remove_flag(RustStructs::ModelState_Flag::Aiming);
			_ModelState->SetMounted(true);
		}

		if (m_settings::StopPlayer && m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
		{
			Vector3 vel = _This->get_TargetMovement();

			float max_speed = (_This->swimming() || _This->ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.Length() > 0.f) {
				_This->set_TargetMovement(Vector3());
			}
		}
	}
}