#include "Visuals.hpp"
#include "../../Hooking/Hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"

void Visuals::DrawPlayers()
{
	if (!InGame)
		return;

	for (const auto EntityList : VisualsArray)
	{
		const auto BasePlayer = EntityList.BasePlayer;
		if (!IsAddressValid(BasePlayer))
			continue;


		Vector2 w2sPos;
		if (UnityEngine::WorldToScreen(BasePlayer->get_transform()->get_position(), w2sPos))
		{
			int yoffset = 8;
			float distance = AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position().Distance(BasePlayer->get_transform()->get_position());
			std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
			char str[128];
			sprintf(str, XS("[%dm]"), (int)distance);
			player_name = player_name + " " + str;

			UnityEngine::GL().TextCenter(Vector2(w2sPos.x, w2sPos.y + yoffset), player_name.c_str(), Color::White(), Color::Black(), 12);
			yoffset += 13;


			const auto item = BasePlayer->ActiveItem();
			if (IsAddressValid(item))
			{
				auto info = item->info();

				if (IsAddressValid(info))
				{
					auto display_name = info->GetDisplayName(item);
					if (IsAddressValid(display_name))
					{
						auto held_item = utf16_to_utf8(display_name->c_str());
						UnityEngine::GL().TextCenter(Vector2(w2sPos.x, w2sPos.y + yoffset), held_item.c_str(), Color::White(), Color::Black(), 12);
						yoffset += 13;
					}
				}
			}
		}
	}
}

void Visuals::CachePlayers()
{
	if (!InGame)
		return;

	if (!this->VisiblePlayerList)
		this->VisiblePlayerList = AssemblyCSharp::BasePlayer::visiblePlayerList();



	auto Vals = VisiblePlayerList->vals;
	auto size = Vals->count;
	auto buffer = Vals->buffer;
	

	for (std::int32_t index = 0; index < size; index++)
	{
		auto BasePlayer = buffer->m_Items[index];
		if (!IsAddressValid(BasePlayer))
			continue;
	
		VisualsArrayTemp.push_back(VisualsVector(BasePlayer));
	}

	VisualsArray = VisualsArrayTemp;
	VisualsArrayTemp.clear();
}