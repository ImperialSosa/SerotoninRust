#include "../hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::ClientInput(AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2)
{
	if(!InGame)
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		Features().Instance()->LocalPlayer = a1;

	if (!IsAddressValid(ToAddress(Hooks::ProjectileShootHookhk.get_original<void*>())))
	{
		Hooks::ProjectileShootHookhk.VirtualFunctionHook(XS("ProjectileShoot"), HASH("WriteToStream"), &Hooks::ProjectileShootHook, XS("ProtoBuf"), 1);
	}



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

	if (UnityEngine::Input::GetKey(RustStructs::F))
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = .99f;
	}
	else
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = 0.05f;
	}

	if (UnityEngine::Input::GetKey(RustStructs::F))
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


	if (UnityEngine::Input::GetKey(RustStructs::C))
	{
		Features().Instance()->FindBulletTPAngles(num6);
	}
	else if (!Features().BulletTPAngle.IsZero()) {
		Features().BulletTPAngle = Vector3(0, 0, 0);
		m_settings::Thickbullet_Indicator = false;
		m_settings::Thickbullet_AutoShoot = false;
	}

	Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);
}