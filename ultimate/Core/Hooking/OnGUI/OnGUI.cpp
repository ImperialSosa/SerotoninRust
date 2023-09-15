#include "../Hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"

#include "../../Net/net.h"
#include "../../Net/data.h"
#include "../../Net/fnv1a.h"
#include "../../Features/Visuals/Visuals.hpp"
#include "../../MenuFramework/Menu/Menu.hpp"
#include "../../Features/Notifications/Notifications.hpp"


inline UnityEngine::GUISkin* gui_skin = nullptr;

void SetupStyles()
{
	if (UnityEngine::gui_style && gui_skin)
		return;

	if (gui_skin == nullptr || UnityEngine::gui_style == nullptr)
	{
		gui_skin = UnityEngine::GUI::GetSkin();
		UnityEngine::gui_style = gui_skin->m_label();
		static bool FontLoaded = false;
		if (!FontLoaded)
		{
			auto g_font = font_bundle->LoadAsset<uintptr_t>(XS("ubuntu-medium.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));

			gui_skin->m_Font() = ToAddress(g_font);

			UnityEngine::gui_style->SetFontSize(9);

			FontLoaded = true;
		}

		UnityEngine::GUIStyle::SetAlignment(UnityEngine::gui_style, 0);
		UnityEngine::GUI::SetColor(Color::White());
	}

}


void ConnectorClient()
{
	static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
	float current_time = UnityEngine::Time::get_realtimeSinceStartup();

	static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
	float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

	static bool LoadOnce = false;

	connector::cheat_message msg;
	msg.msg = connector::messages::JOIN_SHARED_ESP;
	msg.value = XS("ServerABCD"); //Name of channel
	auto data = connector::data(msg);


	if (current_time - send_time > 0.02f)
	{
		net->run();


		if (net->ready_.load())
		{

			if (!LoadOnce)
			{
				net->send_data(data);

				LOG(XS("[DEBUG] Connected to SharedESP channel"));
				LoadOnce = true;
			}

			if (LoadOnce)
			{
				static bool ReceivedFile1 = false;
				static bool ReceivedFile2 = false;
				static bool ReceivedFile3 = false;
				static bool ReceivedFile4 = false;

				//request your uploaded file anytime else
				if (!ReceivedFile1)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FontsBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
				}

				static bool DataSent = false;
				if (ReceivedFile2 && !DataSent)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "IconsBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent = true;
				}

				static bool DataSent2 = false;
				if (ReceivedFile3 && !DataSent2)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FireBundleA"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent2 = true;
				}

				static bool DataSent3 = false;
				if (ReceivedFile4 && !DataSent3)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FireBundleB"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent3 = true;
				}
				net->shared_files_mutex_.lock();
				if (net->shared_files_.size() > 0)
				{
					for (auto& iter : net->shared_files_) {

						if (!ReceivedFile1) {
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							font_bundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile2 = true;
							ReceivedFile1 = true;
						}

						if (ReceivedFile2 && DataSent)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							MenuIconBundles = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile3 = true;
							ReceivedFile2 = false;
						}

						if (ReceivedFile3 && DataSent2)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							FireBundleA = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile4 = true;
							ReceivedFile3 = false;
						}

						if (ReceivedFile4 && DataSent3)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							FireBundleB = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile4 = false;
						}
					}
				}
				net->shared_files_mutex_.unlock();
			}
		}
		send_time = current_time;
	}
}

void TextDrawBegin()
{
	UnityEngine::GL::PushMatrix();
	UnityEngine::GL::LoadPixelMatrix();
}

void TextDrawEnd()
{
	UnityEngine::GL::PopMatrix();
	UnityEngine::GL::RenderText();
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
bool custom_isalnum(char c) {
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}
bool is_base64(char c) {
	return (custom_isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(const std::string& encoded_string) {
	int in_len = static_cast<int>(encoded_string.size());
	int i = 0, j = 0, in = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string decoded_string;

	while (in_len-- && (encoded_string[in] != '=') && is_base64(encoded_string[in])) {
		char_array_4[i++] = encoded_string[in];
		in++;
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0x0F) << 4) + ((char_array_4[2] & 0x3C) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

			for (i = 0; i < 3; i++) {
				decoded_string += char_array_3[i];
			}
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++) {
			char_array_4[j] = 0;
		}

		for (j = 0; j < 4; j++) {
			char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0x0F) << 4) + ((char_array_4[2] & 0x3C) >> 2);

		for (j = 0; j < i - 1; j++) {
			decoded_string += char_array_3[j];
		}
	}

	return decoded_string;
}
void SetupBundles()
{
	if (m_settings::LoadLightning) {
		if (!LightningBundle)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/lightning.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						LightningBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);
						LOG(XS("[DEBUG] Loaded LightningBundle"));
						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
		}
	}
	if (m_settings::LoadGeometric) {
		if (!GeometricBundle)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/geometric.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						GeometricBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);
						LOG(XS("[DEBUG] Loaded GeometricBundle"));
						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
	}
}
	if (m_settings::LoadGalaxy) {
		if (!GalaxyBundle)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/galaxy.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						GalaxyBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);
						LOG(XS("[DEBUG] Galaxy Bundle Loaded"));
						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
		}
	}
}

void Hooks::OnGUI(AssemblyCSharp::ExplosionsFPS* _This)
{
	screen_center = { UnityEngine::Screen::get_width() / 2.f, UnityEngine::Screen::get_height() / 2.f };
	UnityEngine::screen_size = { (float)UnityEngine::Screen::get_width(), (float)UnityEngine::Screen::get_height() };

	ConnectorClient();

	SetupStyles();

	if (!Hooks::ClientInputhk.IsHooked())
	{
		Hooks::ClientInputhk.VirtualFunctionHook(XS("BasePlayer"), HASH("ClientInput"), &Hooks::ClientInput, XS(""), 1);
	}

	SetupBundles();

	if (MenuIconBundles)
	{
		MenuDraw().RenderMenu();

		auto m_Event = UnityEngine::Event::Current();
		if (m_Event->Type() == RustStructs::EventType::Repaint)
		{
			TextDrawBegin();

			if (ConnectionManager().IsConnected())
				InGame = true;
			else
				InGame = false;

			notifcations::object.run();

			static bool has_init = false;
			if (!has_init)
			{
				const auto string = std::wstring(XS(L"[Serotonin] Successfully Loaded!"));
				notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

				has_init = true;
			}

			if (InGame)
			{

				Color Color = m_settings::Manipulation_Indicator ? Color::Green() : Color::White();
				UnityEngine::GL::Circle(screen_center, m_settings::AimbotFOV, Color, 100);

				Visuals().CachePlayers();
				Visuals().DrawPlayers();
			}

			TextDrawEnd();
		}

	}
	
	if (UnityEngine::Input::GetKey(RustStructs::End))
	{
		MenuIconBundles->Unload(true);
		MenuIconBundles = nullptr;

		/* Chams */
		{
			if (GalaxyBundle)
			{
				GalaxyBundle->Unload(true);
				GalaxyBundle = nullptr;
				GalaxyShader = nullptr;
				GalaxyMaterial = nullptr;
			}

			if (FireBundleA)
			{
				FireBundleA->Unload(true);
				FireBundleA = nullptr;
				FireShaderA = nullptr;
				FireMaterialA = nullptr;
			}

			if (FireBundleB)
			{
				FireBundleB->Unload(true);
				FireBundleB = nullptr;
				FireShaderB = nullptr;
				FireMaterialB = nullptr;
			}

			if (GeometricBundle)
			{
				GeometricBundle->Unload(true);
				GeometricBundle = nullptr;
				GeometricShader = nullptr;
				GeometricMaterial = nullptr;
			}


			if (LightningBundle)
			{
				LightningBundle->Unload(true);
				LightningBundle = nullptr;
				LightningShader = nullptr;
				LightningMaterial = nullptr;
			}

			if (font_bundle)
			{
				font_bundle->Unload(true);
				font_bundle = nullptr;

			}
		}

		Hooks::OnGUIhk.Unhook();
		Hooks::Update_hk.Unhook();
		Hooks::ClientInputhk.Unhook();
		ConnectionManager().Instance()->ResetPlayerCache();
		Hooks::ProjectileShootHookhk.Unhook();

		connector::cheat_message msg;
		msg.msg = connector::messages::LEAVE_SHARED_ESP;
		msg.value = XS("ServerABCD"); //Name of channel
		auto data = connector::data(msg);
		net->send_data(data);
		delete net;
	}
	
	return;
}