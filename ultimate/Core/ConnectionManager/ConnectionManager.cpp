#include "ConnectionManager.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

#include "../Features/Visuals/Visuals.hpp"
#include "../Features/Features/Features.hpp"


void ConnectionManager::ResetPlayerCache()
{
	Visuals().Instance()->VisiblePlayerList = nullptr;
	Features().Instance()->LocalPlayer = nullptr;

	auto camera = UnityEngine::Camera::get_main();
	if (IsAddressValid(camera))
	{
		auto target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
		//// Clear the target instance
		target.Clear();
	}

	translated_map.clear();
	VisualsArray.clear();
	VisualsArrayTemp.clear();

	PrefabVectorList.clear();
	PrefabListTemp.clear();

	Features().BulletTPAngle = Vector3();
	Features().ManipulationAngle = Vector3();

	m_settings::MaxVerticalFlyhack = 0;
	m_settings::VerticalFlyhack = 0;
	m_settings::MaxHorisontalFlyhack = 0;
	m_settings::HorisontalFlyhack = 0;

	//m_settings::DrawPlayerChams = false;
	m_settings::did_reload = false;
	m_settings::just_shot = false;
	m_settings::time_since_last_shot = 0.0f;
	m_settings::fixed_time_last_shot = 0.0f;

	m_settings::can_manipulate = false;
	m_settings::StartShooting = false;
	m_settings::Manipulation_Indicator = false;
	m_settings::Thickbullet_Indicator = false;
	m_settings::last_tick_time = 0.f;
	m_settings::max_spoofed_eye_distance = 0.f;
}

bool ConnectionManager::IsConnected()
{
	const auto Network = Network::Net::get_cl();

	if (!IsAddressValid(Network))
		return false;

	if (!Network->IsConnected())
	{
		auto LocalPlayer = AssemblyCSharp::LocalPlayer().get_Entity();
		if (!IsAddressValid(LocalPlayer))
			return false;

		if (LocalPlayer)
			LocalPlayer->net() = nullptr;

		this->ResetPlayerCache();

		return false;
	}

	const auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();

	if (!IsAddressValid(LocalPlayer) || !IsAddressValid(LocalPlayer->net()))
	{
		this->ResetPlayerCache();

		return false;
	}


	return LocalPlayer->IsAlive() && !LocalPlayer->IsSleeping();
}