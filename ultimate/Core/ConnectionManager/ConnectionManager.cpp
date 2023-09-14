#include "ConnectionManager.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

#include "../Features/Visuals/Visuals.hpp"
#include "../Features/Features/Features.hpp"


void ConnectionManager::ResetPlayerCache()
{
	Visuals().Instance()->VisiblePlayerList = nullptr;
	Features().Instance()->LocalPlayer = nullptr;

	auto target = AssemblyCSharp::BasePlayer::GetAimbotTarget();
	// Clear the target instance
	target.Clear();
	translated_map.clear();
	VisualsArray.clear();
	VisualsArrayTemp.clear();
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

	return LocalPlayer->IsAlive();
}