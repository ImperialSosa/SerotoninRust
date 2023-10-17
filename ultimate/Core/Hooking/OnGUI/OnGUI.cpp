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
	if (UnityEngine::gui_style && gui_skin && UnityEngine::menu_gui_style)
		return;

	if (gui_skin == nullptr || UnityEngine::gui_style == nullptr || UnityEngine::menu_gui_style == nullptr)
	{
		gui_skin = UnityEngine::GUI::GetSkin();
		UnityEngine::gui_style = gui_skin->m_label();
		UnityEngine::menu_gui_style = gui_skin->m_label();
		static bool FontLoaded = false;
		if (!FontLoaded)
		{
			auto g_font = font_bundle->LoadAsset<uintptr_t>(XS("ubuntu-medium.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));

			gui_skin->m_Font() = ToAddress(g_font);

			UnityEngine::gui_style->SetFontSize(10);

			FontLoaded = true;
		}

		UnityEngine::GUIStyle::SetAlignment(UnityEngine::gui_style, 0);
		UnityEngine::GUIStyle::SetAlignment(UnityEngine::menu_gui_style, 0);
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
	msg.value = "TrollServer1"; //Name of channel
	auto data = connector::data(msg);

	if (current_time - send_time > 0.02f)
	{
		net->run();

		if (net->ready_.load())
		{

			if (!LoadOnce)
			{
				net->send_data(data);

				LOG(XS("[DEBUG] Connected to TrollServer1"));
				LoadOnce = true;
			}

			if (LoadOnce)
			{
				static bool ReceivedFile1 = false;
				static bool ReceivedFile2 = false;
				static bool ReceivedFile3 = false;
				static bool ReceivedFile4 = false;
				static bool ReceivedFile5 = false;
				static bool ReceivedFile6 = false;
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
					msg.value = "SeroIcon"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent = true;
				}

				static bool DataSent2 = false;
				if (ReceivedFile3 && !DataSent2)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "IconsBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent2 = true;
				}

				static bool DataSent3 = false;
				if (ReceivedFile4 && !DataSent3)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FireBundleA"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent3 = true;
				}

				static bool DataSent4 = false;
				if (ReceivedFile5 && !DataSent4)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FireBundleB"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent4 = true;
				}

				static bool DataSent5 = false;
				if (ReceivedFile6 && !DataSent5)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "ColorBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent5 = true;
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
							SerotoninIconBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
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
							MenuIconBundles = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
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
							FireBundleA = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile5 = true;
							ReceivedFile4 = false;
						}

						if (ReceivedFile5 && DataSent4)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							FireBundleB = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile6 = true;
							ReceivedFile5 = false;
						}

						if (ReceivedFile6 && DataSent5)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							ColorBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile6 = false;
						}
					}
				}
				net->shared_files_mutex_.unlock();

				//if (current_time2 - send_time2 > 0.8f)
				//{
				//	auto camera = UnityEngine::Camera::get_main();
				//	if (IsAddressValid(camera)) {
				//		auto Target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
				//		Vector3 TargetPos = Target.m_position;
				//		connector::writer write;
				//		write.write(TargetPos.x);
				//		write.write(TargetPos.y);
				//		write.write(TargetPos.z);

				//		//send data to server
				//		connector::shared_esp_data shared_data;
				//		shared_data.channel = HASHH("ServerABCD");//hash of the channel where we want to send data
				//		shared_data.data.resize(write.size() + 1, 0);
				//		memcpy(shared_data.data.data(), write.data(), write.size());

				//		data = connector::data(shared_data);
				//		net->send_data(data);

				//	}
				//	send_time2 = current_time2;
				//}
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
	UnityEngine::GL::RenderMenuText();
	UnityEngine::GL::RenderIcons();
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

						const auto string = std::wstring(XS(L"[Serotonin] Loaded Lightning!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

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

						const auto string = std::wstring(XS(L"[Serotonin] Loaded Geometric!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

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

						const auto string = std::wstring(XS(L"[Serotonin] Loaded Galaxy!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
		}
	}
	if (m_settings::LoadRBP) {
		if (!RPBGalaxyBundle)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/rbpgalaxy.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						RPBGalaxyBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);
						LOG(XS("[DEBUG] RPBGalaxyBundle Loaded"));

						const auto string = std::wstring(XS(L"[Serotonin] Loaded RPBGalaxy!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
		}
	}
	if (m_settings::LoadWireFrame) {
		if (!WireFrameBundle)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/wireframe.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						WireFrameBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);
						LOG(XS("[DEBUG] WireFrame Bundle Loaded"));

						const auto string = std::wstring(XS(L"[Serotonin] Loaded WireFrame!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
		}
	}
	if (m_settings::LoadHerbertAsset) {
		if (!HerbetAsset)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://xcheats.dev/BundleStreaming/herbert.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						HerbetAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);
						LOG(XS("[DEBUG] HerbetAsset Bundle Loaded"));

						const auto string = std::wstring(XS(L"[Serotonin] Loaded Herbert!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}
				send_time = current_time;
			}
		}

		if (HerbetAsset)
		{
			if (!HerbertPrefab)
			{
				HerbertPrefab = HerbetAsset->LoadAsset<UnityEngine::GameObject>(XS("herbert the pervert v2.fbx"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
			}
		}
	}
	if (m_settings::LoadAmongusAsset) {
		if (!AmongUsAsset)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://xcheats.dev/BundleStreaming/amongus.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						AmongUsAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);

						LOG(XS("[DEBUG] AmongUsAsset Bundle Loaded"));

						const auto string = std::wstring(XS(L"[Serotonin] Loaded Amongus!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}

				send_time = current_time;
			}
		}

		if (AmongUsAsset)
		{
			if (!AmongusPrefab)
			{
				AmongusPrefab = AmongUsAsset->LoadAsset<UnityEngine::GameObject>(XS("amongus.fbx"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
			}
		}
	}
	if (m_settings::LoadExplosionEffect) {
		if (!ExplosionAsset)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/explosion.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						ExplosionAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);

						LOG(XS("[DEBUG] ExplosionAsset Bundle Loaded"));
						const auto string = std::wstring(XS(L"[Serotonin] Loaded Explosion!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}

				send_time = current_time;
			}
		}

		if (ExplosionAsset)
		{
			if (!ExplosionPrefab)
			{
				ExplosionPrefab = ExplosionAsset->LoadAsset<UnityEngine::GameObject>(XS("bigexplosioneffect.prefab"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
			}
		}
	}
	if (m_settings::LoadGhostEffect) {
		if (!GhostAsset)
		{
			static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
			float current_time = UnityEngine::Time::get_realtimeSinceStartup();

			if (current_time - send_time > 5)
			{
				static uintptr_t WebClientClass = 0; if (!WebClientClass) WebClientClass = (uintptr_t)CIl2Cpp::FindClass(XS("System.Net"), XS("WebClient"));

				if (SystemNet::WebClient* webclient = reinterpret_cast<SystemNet::WebClient*>(CIl2Cpp::il2cpp_object_new((void*)WebClientClass)))
				{

					webclient->_cctor();

					auto request_msg = std::wstring(XS(L"https://fruityskills.com/BundleStreaming/ghost.php"));
					auto request_msg_str = std::string(request_msg.begin(), request_msg.end());

					auto resp = webclient->DownloadString(request_msg_str.c_str());
					std::string decoded = base64_decode(resp->string_safe().c_str());


					static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
					float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

					if (current_time2 - send_time2 > 5)
					{
						auto ConvertedArr = FPSystem::Convert().FromBase64String(resp->string_safe().c_str());
						GhostAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(ConvertedArr, 0, 0);

						LOG(XS("[DEBUG] GhostAsset Bundle Loaded"));

						const auto string = std::wstring(XS(L"[Serotonin] Loaded Ghost!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

						send_time2 = current_time2;
					}
				}

				send_time = current_time;
			}
		}

		if (GhostAsset)
		{
			if (!GhostPrefab)
			{
				GhostPrefab = GhostAsset->LoadAsset<UnityEngine::GameObject>(XS("cfxr2 souls escape.prefab"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
			}
		}
	}
}


#include "../../Features/Features/Features.hpp"
#include "../../Configs/Configs.hpp"

float RecordedPointsX[100] = {};
float RecordedPointsY[100] = {};
float RecordedPointsZ[100] = {};

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}

void drawRaidESP()
{
	LogSystem::RenderExplosions();
}

void drawMisc()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	int yPos = 15;

	int yoffset = 48;

	float center_x = (float)(UnityEngine::screen_size.x) / 2, center_y = (float)(UnityEngine::screen_size.y) / 2;

	if (m_settings::Crosshair)
	{
		auto Crosshair_Color = Color{ m_settings::Crosshair_Color[0], m_settings::Crosshair_Color[1], m_settings::Crosshair_Color[2], 255 };

		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x + 8, screen_center.y), Color::Red());
		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x - 7, screen_center.y), Color::Red());
		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x, screen_center.y + 8), Color::Red());
		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x, screen_center.y - 7), Color::Red());
	}

	if (m_settings::Swastika)
	{
		auto sped = m_settings::SwastikaSpeed / 10;
		float speed = sped;
		float razmer = 10;
		bool cadicall = false;

		float xs = screen_center.x, ys = screen_center.y;
		static float rotation_degree = 0.f;
		if (rotation_degree > 89.f)
			rotation_degree = 0.f;
		rotation_degree += speed;
		int length = (int)(screen_center.x / razmer / m_settings::SwastikaSize);
		float gamma = Math::atanf(length / length);
		int i = 0;
		while (i < 4)
		{
			std::vector <int> p
			{
				int(length * Math::sinf(GRD_TO_BOG(rotation_degree + (i * 90)))),
					int(length * Math::cosf(GRD_TO_BOG(rotation_degree + (i * 90)))),
					int((length / Math::cosf(gamma)) * Math::sinf(GRD_TO_BOG(rotation_degree + (i * 90) + RAD2DEG(gamma)))),
					int((length / Math::cosf(gamma)) * Math::cosf(GRD_TO_BOG(rotation_degree + (i * 90) + RAD2DEG(gamma))))
			};

			UnityEngine::GL::Line(Vector2(xs, ys), Vector2(xs + p[0], ys - p[1]), Color::Red());
			UnityEngine::GL::Line(Vector2(xs + p[0], ys - p[1]), Vector2(xs + p[2], ys - p[3]), Color::Red());

			i++;
		}
	}

	if (m_settings::Aimline)
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(m_target.m_player))
			{
				auto targetPos = m_target.m_position;
				if (!targetPos.IsZero())
				{
					auto bulletTPPos = Features().BulletTPAngle;

					if (bulletTPPos.IsZero())
					{
						bulletTPPos = targetPos;
					}

					Vector2 w2sPos;
					if (UnityEngine::WorldToScreen(bulletTPPos, w2sPos))
					{
						UnityEngine::GL::Line(Vector2(UnityEngine::Screen::get_width() / 2.f, UnityEngine::Screen::get_height() / 2.f), w2sPos, Color::Red());
					}
				}
			}
		}
	}

	if (m_settings::ShowCachedLOS) {
		if (Features().ConstantLOSCheck == true)
			UnityEngine::GL().TextCenter(Vector2(center_x, center_y - 400), XS("Cached Visible"), Color::Red(), Color::Black(), m_settings::fontsize);

	}

	if (m_settings::AimMarker)
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(m_target.m_player))
			{
				auto targetPos = m_target.m_position;

				if (!targetPos.IsZero())
				{
					Vector2 w2sPos;

					if (UnityEngine::WorldToScreen(targetPos, w2sPos))
					{
						UnityEngine::GL().TextCenter(w2sPos, XS("X"), Color::White(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
					}
				}
			}
		}
	}

	if (m_settings::SavePos)
	{
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		if (IsAddressValid(LocalPlayer)) {
			auto CurrentPos = LocalPlayer->get_bone_transform(47)->get_position();
			static Vector2 SavedPos;

			if (UnityEngine::Input::GetKey(m_settings::SavePosKey))
			{
				SavedWorldPos = CurrentPos;
			}

			if (UnityEngine::WorldToScreen(SavedWorldPos, SavedPos))
			{
				auto distance = CurrentPos.Distance(SavedWorldPos);

				std::string player_name = "SavedPos";
				char str[256];
				sprintf(str, XS("[%dm]"), (int)distance);
				player_name = player_name + " " + str;

				UnityEngine::GL().TextCenter(SavedPos, player_name.c_str(), Color::Cyan(), Color::Black(), m_settings::fontsize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
			}
		}
	}

	if (m_settings::DrawFov)
	{
		Color Color = m_settings::Manipulation_Indicator ? Color::Green() : Color::White();
		UnityEngine::GL::Circle(screen_center, m_settings::AimbotFOV, Color, 100);
	}

	if (m_settings::BulletTPFlags && m_settings::Thickbullet_Indicator && m_settings::BulletTP)
	{
		UnityEngine::GL().TextCenter(Vector2(center_x, center_y - yPos), XS("Bullet TP"), Color::Red(), Color::Black(), m_settings::fontsize);
		yPos += 10;
	}

	if (m_settings::InstantBullet)
	{
		auto desynctime = UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;


		if (desyncpercentage >= 0.85f)
		{
			UnityEngine::GL().TextCenter(Vector2(center_x, center_y - yPos), XS("Instant Hit"), Color::Red(), Color::Black(), m_settings::fontsize);
			yPos += 10;
		}
	}

	if (m_settings::AutoReload)
	{

		if (auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity())
		{
			if (LocalPlayer->lifestate() != RustStructs::Dead)
			{
				if (auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>())
				{
					if (BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
					{
						if (auto HeldItem = Features().LocalPlayer->ActiveItem())
						{
							if (!BaseProjectile->HasReloadCooldown())
							{
								if (m_settings::did_reload == false && m_settings::time_since_last_shot <= (m_settings::reload_time - (m_settings::reload_time / 10)) && m_settings::time_since_last_shot > 0)
								{
									float time_full = (m_settings::reload_time - (m_settings::reload_time / 10));
									float time_left = m_settings::time_since_last_shot;
									auto percentage = (((time_left / time_full) * 100.0f) + 1.f) / 100;
									float bars = 0;
									float red, green, blue;
									float Num = percentage;

									if (Num < 0.5) {
										red = Num * 2.f * 255.f;
										green = 255.f;
										blue = 0.f;
									}
									else {
										red = 255.f;
										green = (2.f - 2.f * Num) * 255.f;
										blue = 0.f;
									}


									if (Num > 0.01) {
										float xzzzz = bars++;

										if (auto mag = BaseProjectile->primaryMagazine())
										{
											if (auto def = mag->ammoType())
											{
												if (auto test = def->FindIconSprite(HeldItem->info()->itemid()))
												{
													if (auto texture = test->get_texture())
													{
														//auto rect = test->get_rect();
														//UnityEngine::GUI::SetColor(Color::White());
														//UnityEngine::GUI::DrawTexture(UnityEngine::rect_t(screen_center.x - 25, screen_center.y + 68, rect.wid / 4.5f, rect.hei / 4.5f), texture);
													}
												}
											}
										}
										auto xpostop = screen_center.x - 50;
										auto xpostop2 = screen_center.x - 49;
										auto ypostop = screen_center.y + yoffset;
										UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 1 }, { xpostop + 100, ypostop + 2 }, Color(0, 0, 0, 255.f).GetUnityColor());
										UnityEngine::GL::RectangleFilled({ xpostop, ypostop + 1 }, { xpostop + 100, ypostop + 4 }, Color(0, 0, 0, 255.f).GetUnityColor());
										UnityEngine::GL::RectangleFilled({ xpostop2, ypostop }, { xpostop2 + (100 * (time_left / time_full)), ypostop + 3 }, Color((int)(red), (int)(green), (int)(blue), 255.f).GetUnityColor());
										yoffset += 10;
									}
								}
							}
							else
							{
								m_settings::time_since_last_shot = 0.f;
								m_settings::just_shot = false;
								m_settings::did_reload = true;
							}

						}
					}
					else
					{
						m_settings::time_since_last_shot = 0.f;
						m_settings::just_shot = false;
						m_settings::did_reload = true;
					}
				}
			}
		}
	}

	if (m_settings::Manipulation && m_settings::BulletTP && m_settings::BulletTPFlags && m_settings::ManipFlags && m_settings::Manipulation_Indicator)
	{
		UnityEngine::GL().TextCenter(Vector2(center_x, center_y - yPos), XS("Manipulated"), Color::Red(), Color::Black(), m_settings::fontsize);
		yPos += 10;
	}
	else if (m_settings::ManipFlags && m_settings::Manipulation_Indicator && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		UnityEngine::GL().TextCenter(Vector2(center_x, center_y - yPos), XS("Manipulated"), Color::Red(), Color::Black(), m_settings::fontsize);
		yPos += 10;
	}

	if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		auto desynctime = UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;

		float red, green, blue;
		float Num = desyncpercentage;
		float bars = 0;

		if (desyncpercentage < 0.1)
			Num = 0;

		if (Num != 0) {
			if (Num < 0.5) {
				red = Num * 2.f * 255.f;
				green = 255.f;
				blue = 0.f;
			}
			else {
				red = 255.f;
				green = (2.f - 2.f * Num) * 255.f;
				blue = 0.f;
			}

			if (Num > 1.f)
				Num = 1.f;


			float xzzzz = bars++;


			auto xpostop = screen_center.x - 50;
			auto xpostop2 = screen_center.x - 49;
			auto ypostop = screen_center.y + yoffset;
			UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 1 }, { xpostop + 100, ypostop + 2 }, Color(0, 0, 0, 255.f).GetUnityColor());
			UnityEngine::GL::RectangleFilled({ xpostop, ypostop + 1 }, { xpostop + 100, ypostop + 4 }, Color(0, 0, 0, 255.f).GetUnityColor());
			UnityEngine::GL::RectangleFilled({ xpostop2, ypostop }, { xpostop2 + (100 * desynctime), ypostop + 3 }, Color((int)(red), (int)(green), (int)(blue), 255.f).GetUnityColor());
			yoffset += 10;
		}
	}

	if (m_settings::Flyhack_Indicator)
	{
		float YPos = (UnityEngine::screen_size.y / 8);
		int YOffset = 40;

		float bar_width = 200.f;
		float x = screen_center.x;
		float y = screen_center.y;
		float w = 300.f;
		float h = 10.f;

		auto FlyhackColorY = Color(0.f, 255.f, 0.f, 255.f);
		auto FlyhackColorX = Color(0.f, 255.f, 0.f, 255.f);

		const auto horizontal_percentage = minm(m_settings::HorisontalFlyhack / m_settings::MaxHorisontalFlyhack, 1.f);
		const auto vertical_percentage = minm(m_settings::VerticalFlyhack / m_settings::MaxVerticalFlyhack, 1.f);

		if (vertical_percentage > 0.5 && vertical_percentage < 0.8)
			FlyhackColorY = Color(255.f, 137.f, 0.f, 255.f);
		else if (vertical_percentage > 0.8)
			FlyhackColorY = Color(255.f, 0.f, 0.f, 255.f);
		else
			FlyhackColorY = Color(0.f, 255.f, 0.f, 255.f);

		if (horizontal_percentage > 0.5 && horizontal_percentage < 0.8)
			FlyhackColorX = Color(255.f, 137.f, 0.f, 255.f);
		else if (horizontal_percentage > 0.8)
			FlyhackColorX = Color(255.f, 0.f, 0.f, 255.f);
		else
			FlyhackColorX = Color(0.f, 255.f, 0.f, 255.f);

		auto xpostop = x - w / 2;
		auto ypostop = YPos - YOffset;
		UnityEngine::GL::RectangleFilled({ xpostop, ypostop }, { xpostop + w, ypostop + h }, Color(34.f, 34.f, 34.f, 255.f).GetUnityColor());
		UnityEngine::GL::RectangleFilled({ xpostop, ypostop }, { xpostop + w * horizontal_percentage, ypostop + h }, FlyhackColorX.GetUnityColor());

		UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 10 }, { xpostop + w, ypostop + h - 10 }, Color(34.f, 34.f, 34.f, 255.f).GetUnityColor());
		UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 10 }, { xpostop + w * vertical_percentage, ypostop + h - 10 }, FlyhackColorY.GetUnityColor());

		UnityEngine::GL::Rectangle({ xpostop, ypostop }, { xpostop + w, ypostop + h }, Color(0.f, 0.f, 0.f, 120.f).GetUnityColor());
		UnityEngine::GL::Rectangle({ xpostop, ypostop - 10 }, { xpostop + w, ypostop + h - 10 }, Color(0.f, 0.f, 0.f, 120.f).GetUnityColor());
	}
}

const wchar_t* ConvertToWideString(const char* str) //imports
{
	// Get the length of the wide string
	size_t length = LI_FN(mbstowcs)(nullptr, str, 0);

	// Allocate memory for the wide string
	wchar_t* wideStr = new wchar_t[length + 1];

	// Convert the string to wide string
	LI_FN(mbstowcs)(wideStr, str, length + 1);

	return wideStr;
}

auto prefab_spawner() -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	if (!IsAddressValid(Features().LocalPlayer->eyes()))
		return;

	if (m_settings::HerbertPrefabSpawn && UnityEngine::Input::GetKeyDown(m_settings::HerbertKey))
	{
		if (IsAddressValid(HerbertPrefab))
		{
			auto lookingatPoint = Features().LocalPlayer->lookingAtPoint();
			UnityEngine::Object().Instantiate(HerbertPrefab, lookingatPoint, Features().LocalPlayer->eyes()->get_rotation());
		}
	}

	if (m_settings::AmongusPrefabSpawn && UnityEngine::Input::GetKeyDown(m_settings::AmongusKey))
	{
		if (IsAddressValid(AmongusPrefab))
		{
			auto lookingatPoint = Features().LocalPlayer->lookingAtPoint();
			UnityEngine::Object().Instantiate(AmongusPrefab, lookingatPoint, Features().LocalPlayer->eyes()->get_rotation());

		}
	}
}

inline Vector2 hotbar_pos;
inline Vector2 window_size2;
inline bool sex2 = false;
inline void DrawPlayerHotbar(UnityEngine::Event* event, const Vector2& pos, const Vector2& window_size) {
	if (m_settings::SelectedHotbar == 1 || m_settings::SelectedHotbar == 2)
	{
		if (!sex2) {
			hotbar_pos = pos;
			sex2 = true;
		}

		window_size2 = window_size;

		auto mouse = UnityEngine::Input::GetMousePosition();
		auto width = UnityEngine::Screen::get_width();
		auto height = UnityEngine::Screen::get_height();
		auto menu_event = event->Type();
		auto key_code = UnityEngine::Event::get_keyCode(event);

		mouse_pos.x = UnityEngine::Input::GetMousePosition().x;
		mouse_pos.y = UnityEngine::Screen::get_height() - UnityEngine::Input::GetMousePosition().y;
		auto mouse_state = UnityEngine::Input::GetMouseButton(0);

		if (main_menu_open)
		{
			if (Menu().is_mouse_in_box({ hotbar_pos.x, hotbar_pos.y }, { hotbar_pos.x + window_size2.x, hotbar_pos.y + window_size2.y }) && mouse_state && !hover_element) {
				hotbar_pos.x += mouse_pos.x - old_mouse_pos.x;
				hotbar_pos.y += mouse_pos.y - old_mouse_pos.y;
			}
			else {
				hover_element = false;
			}

		}

		auto camera = UnityEngine::Camera::get_main();
		float info_y = 0;
		float info_y_icons = 0;
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(AimbotTarget.m_player))
			{
				auto inventory = AimbotTarget.m_player->inventory();
				if (IsAddressValid(inventory))
				{
					if (m_settings::SelectedHotbar == 1) {
						auto containerBelt = inventory->containerBelt();
						if (IsAddressValid(containerBelt))
						{
							auto ItemList = containerBelt->itemList();
							if (IsAddressValid(ItemList))
							{
								if (menu_event == RustStructs::EventType::Repaint)
								{
									for (int i = 0; i < ItemList->_size; i++) {
										auto item = ItemList->_items->m_Items[i];
										if (!item)
											continue;

										if (i > ItemList->_size - 1)
										{
											info_y += 13;
											continue;
										}

										if (IsAddressValid(item)) {

											auto amount = item->amount();
											auto name = item->GetItemName();

											auto camera = UnityEngine::Camera::get_main();
											if (IsAddressValid(camera)) {
												auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
												if (IsAddressValid(m_target.m_player))
												{
													if (IsAddressValid(name))
													{
														std::string ItemName = "";
														char str[256];
														sprintf(str, XS("[%d] %s"), (int)amount, name->string_safe().c_str());
														ItemName = str;

														if (item->heldEntity() && m_target.m_player && m_target.m_player->ActiveItem()) {
															if (item->heldEntity()->prefabID() == m_target.m_player->ActiveItem()->heldEntity()->prefabID())
																UnityEngine::GL().TextCenter(Vector2(hotbar_pos.x, hotbar_pos.y + info_y), ItemName.c_str(), Color::Turquoise(), Color::Black(), m_settings::fontsize);
														}
														else
															UnityEngine::GL().TextCenter(Vector2(hotbar_pos.x, hotbar_pos.y + info_y), ItemName.c_str(), Color::White(), Color::Black(), m_settings::fontsize);
													}
												}
											}
										}

										info_y += 13;
									}
									info_y += 10;
									//info_y = 0;
								}
							}
						}
					}
					if (m_settings::SelectedHotbar == 2) {
						auto containerBelt = inventory->containerBelt();
						if (IsAddressValid(containerBelt))
						{
							auto ItemList = containerBelt->itemList();
							if (IsAddressValid(ItemList))
							{
								if (menu_event == RustStructs::EventType::Repaint)
								{
									std::string player_name = utf16_to_utf8(AimbotTarget.m_player->get_displayName()->c_str());					
									Vector2 Size = Vector2(60, 60);

									//BackGround
									{
										UnityEngine::GL::TextCenter(Vector2(hotbar_pos.x, hotbar_pos.y + 12.5), player_name.c_str(), Color::White(), Color::Black(), 10);
									}

									for (int i = 0; i < ItemList->_size; i++) {
										auto item = ItemList->_items->m_Items[i];
										if (!item)
											continue;

										if (i > ItemList->_size - 1)
										{
											info_y_icons += 65;
											continue;
										}

										if (IsAddressValid(item)) {

											auto amount = item->amount();
											auto name = item->GetItemName();

											auto sprite_the_drink = item->get_iconSprite();
											if (!sprite_the_drink)
												continue;

											auto texture = sprite_the_drink->get_texture();
											if (!texture)
												continue;

											auto camera = UnityEngine::Camera::get_main();
											if (IsAddressValid(camera)) {
												auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
												if (IsAddressValid(m_target.m_player))
												{
													//std::string ItemName = "";
													//char str[128];
													//sprintf(str, XS("[%d] %s"), (int)amount, name->string_safe().c_str());
													//ItemName = str;
													//
													if (item->heldEntity() && m_target.m_player && m_target.m_player->ActiveItem()) {
														if (item->heldEntity()->prefabID() == m_target.m_player->ActiveItem()->heldEntity()->prefabID())
															UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons, hotbar_pos.y + 20.f), Vector2(hotbar_pos.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons + Size.x, hotbar_pos.y + 20.f + Size.y), Color(0.f, 24.f, 143.f, 120.f).GetUnityColor());
													}
													else
														UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons, hotbar_pos.y + 20.f), Vector2(hotbar_pos.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons + Size.x, hotbar_pos.y + 20.f + Size.y), Color(34.f, 34.f, 34.f, 120.f).GetUnityColor());

													UnityEngine::GL().DrawIcon(Vector2(hotbar_pos.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons, hotbar_pos.y + 20.f), Size, texture, Color::White());
												}
											}
										}

										info_y_icons += 65;
									}
									info_y_icons = 0;
								}
							}
						}
					}
				}
			}
		}
		//Menu().end_window();
	}
}

inline Vector2 hotbar_pos_c;
inline Vector2 window_size2_c;
inline bool sex2_c = false;

inline void DrawPlayerClothing(UnityEngine::Event* event, const Vector2& pos, const Vector2& window_size) {
	if (m_settings::SelectedClothing == 1 || m_settings::SelectedClothing == 2)
	{
		if (!sex2_c) {
			hotbar_pos_c = pos;
			sex2_c = true;
		}

		window_size2_c = window_size;

		auto mouse = UnityEngine::Input::GetMousePosition();
		auto width = UnityEngine::Screen::get_width();
		auto height = UnityEngine::Screen::get_height();
		auto menu_event = event->Type();
		auto key_code = UnityEngine::Event::get_keyCode(event);

		mouse_pos.x = UnityEngine::Input::GetMousePosition().x;
		mouse_pos.y = UnityEngine::Screen::get_height() - UnityEngine::Input::GetMousePosition().y;
		auto mouse_state = UnityEngine::Input::GetMouseButton(0);

		if (main_menu_open)
		{
			if (Menu().is_mouse_in_box({ hotbar_pos_c.x, hotbar_pos_c.y }, { hotbar_pos_c.x + window_size2_c.x, hotbar_pos_c.y + window_size2_c.y }) && mouse_state && !hover_element) {
				hotbar_pos_c.x += mouse_pos.x - old_mouse_pos.x;
				hotbar_pos_c.y += mouse_pos.y - old_mouse_pos.y;
			}
			else {
				hover_element = false;
			}

		}

		auto camera = UnityEngine::Camera::get_main();
		float info_y = 0;
		float info_y_icons = 0;
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(AimbotTarget.m_player))
			{
				auto inventory = AimbotTarget.m_player->inventory();
				if (IsAddressValid(inventory))
				{
					if (m_settings::SelectedClothing == 1) {
						auto containerWear = inventory->containerWear();
						if (IsAddressValid(containerWear))
						{
							auto ItemList = containerWear->itemList();
							if (IsAddressValid(ItemList))
							{
								for (int i = 0; i < ItemList->_size; i++) {
									auto item = ItemList->_items->m_Items[i];
									if (!item)
										continue;

									if (i > ItemList->_size - 1)
									{
										info_y += 13;
										continue;
									}

									if (IsAddressValid(item)) {

										auto name = item->GetItemName();

										auto camera = UnityEngine::Camera::get_main();
										if (IsAddressValid(camera)) {
											auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);

											std::string ItemName = "";
											char str[256];
											sprintf(str, XS("%s"), name->string_safe().c_str());
											ItemName = str;

											if (IsAddressValid(m_target.m_player))
											{
												UnityEngine::GL().TextCenter(Vector2(hotbar_pos_c.x, hotbar_pos_c.y + info_y), ItemName.c_str(), Color::White(), Color::Black(), m_settings::fontsize);
											}
										}
									}

									info_y += 13;
								}
								info_y = 0;
							}
						}
					}
					if (m_settings::SelectedClothing == 2) {
						auto containerBelt = inventory->containerWear();
						if (IsAddressValid(containerBelt))
						{
							auto ItemList = containerBelt->itemList();
							if (IsAddressValid(ItemList))
							{
								if (menu_event == RustStructs::EventType::Repaint)
								{
									Vector2 Size = Vector2(60, 60);

									for (int i = 0; i < ItemList->_size; i++) {
										auto item = ItemList->_items->m_Items[i];
										if (!item)
											continue;

										if (i > ItemList->_size - 1)
										{
											info_y_icons += 65;
											continue;
										}

										if (IsAddressValid(item)) {

											auto amount = item->amount();
											auto name = item->GetItemName();

											auto sprite_the_drink = item->get_iconSprite();
											if (!sprite_the_drink)
												continue;

											auto texture = sprite_the_drink->get_texture();
											if (!texture)
												continue;

											auto camera = UnityEngine::Camera::get_main();
											if (IsAddressValid(camera)) {
												auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
												if (IsAddressValid(m_target.m_player))
												{
													//std::string ItemName = "";
													//char str[128];
													//sprintf(str, XS("[%d] %s"), (int)amount, name->string_safe().c_str());
													//ItemName = str;
													//
													if (item->heldEntity() && m_target.m_player && m_target.m_player->ActiveItem()) {
														if (item->heldEntity()->prefabID() == m_target.m_player->ActiveItem()->heldEntity()->prefabID())
															UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos_c.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons, hotbar_pos_c.y + 20.f), Vector2(hotbar_pos_c.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons + Size.x, hotbar_pos_c.y + 20.f + Size.y), Color(0.f, 24.f, 143.f, 120.f).GetUnityColor());
													}
													else
														UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos_c.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons, hotbar_pos_c.y + 20.f), Vector2(hotbar_pos_c.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons + Size.x, hotbar_pos_c.y + 20.f + Size.y), Color(34.f, 34.f, 34.f, 120.f).GetUnityColor());

													UnityEngine::GL().DrawIcon(Vector2(hotbar_pos_c.x - (((Size.x + 5) * ItemList->_size) / 2) + info_y_icons, hotbar_pos_c.y + 20.f), Size, texture, Color::White());
												}
											}
										}

										info_y_icons += 65;
									}
									info_y_icons = 0;
								}
							}
						}
					}
				}
			}
		}

		//Menu().end_window();
	}
}

static inline bool HasTriggered = false;
void Hooks::OnGUI(AssemblyCSharp::ExplosionsFPS* _This)
{
	screen_center = { UnityEngine::Screen::get_width() / 2.f, UnityEngine::Screen::get_height() / 2.f };
	UnityEngine::screen_size = { (float)UnityEngine::Screen::get_width(), (float)UnityEngine::Screen::get_height() };

	ConnectorClient();

	if (!Hooks::ProjectileUpdatehk.IsHooked())
	{
		Hooks::ProjectileUpdatehk.PointerSwapHook(XS("Projectile"), HASH("Update"), &Hooks::ProjectileUpdate, XS(""), 0);
	}

	if (!Hooks::ClientInputhk.IsHooked())
	{
		Hooks::ClientInputhk.VirtualFunctionHook(XS("BasePlayer"), HASH("ClientInput"), &Hooks::ClientInput, XS(""), 1);
	}

	if (!Hooks::SteamPlatformUpdatehk.IsHooked())
	{
		Hooks::SteamPlatformUpdatehk.VirtualFunctionHook(XS("SteamPlatform"), HASH("Update"), &Hooks::SteamPlatformUpdate, XS("Rust.Platform.Steam"), 0);
	}

	if (!Hooks::OnAttackedhk.IsHooked())
	{
		Hooks::OnAttackedhk.VirtualFunctionHook(XS("BasePlayer"), HASH("OnAttacked"), &Hooks::OnAttacked, XS(""), 1);
	}


	/*if (!Hooks::SkyUpdatehk.IsHooked())
	{
		Hooks::SkyUpdatehk.PointerSwapHook(XS("TOD_Camera"), HASH("Update"), &Hooks::SkyUpdate, XS(""), 0);
	}*/

	SetupBundles();

	if (MenuIconBundles)
	{
		SetupStyles();

		if (is_menu_open) {
			if (UnityEngine::Input::GetKey(RustStructs::Mouse0)) {
				auto z = UnityEngine::rect_t{ hotbar_pos.x - 20, hotbar_pos.y - 10, hotbar_pos.x + 20, hotbar_pos.y + 10 };

				if (z.contains(mouse_pos))
				{
					hotbar_pos = (hotbar_pos + (mouse_pos - hotbar_pos) - Vector2(0, 0));
				}
			}

			if (UnityEngine::Input::GetKey(RustStructs::Mouse0)) {
				auto z = UnityEngine::rect_t{ hotbar_pos_c.x - 20, hotbar_pos_c.y - 10, hotbar_pos_c.x + 20, hotbar_pos_c.y + 10 };

				if (z.contains(mouse_pos))
				{
					hotbar_pos_c = (hotbar_pos_c + (mouse_pos - hotbar_pos_c) - Vector2(0, 0));
				}
			}
		}

		auto m_Event = UnityEngine::Event::Current();
		if (IsAddressValid(m_Event))
		{
			TextDrawBegin();

			if (!m_settings::SelectedOption)
				MenuDraw().RenderOptions();
			else if (m_settings::LoadLegit)
				MenuDraw().RenderLegitMenu();
			else if (m_settings::LoadRage)
				MenuDraw().RenderMenu();

			if (m_Event->Type() == RustStructs::EventType::Repaint)
			{
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

				static std::string Message;
				static bool DisplayMessage = false;
				if (Message != GlobalMessage)
				{
					if (DisplayMessage)
						DisplayMessage = false;
					Message = GlobalMessage;
				}
				if (Message == GlobalMessage) {
				
					if (!DisplayMessage) {						
				
						auto Text = ConvertToWideString(GlobalMessage.c_str());
						notifcations::object.push(Text, UnityEngine::Time::get_time());
						DisplayMessage = true;
					}
				}

				if (InGame)
				{
					drawMisc();

					if (m_settings::RaidESP)
					{
						drawRaidESP();

					}

					float x = screen_center.x;
					float YPos = (UnityEngine::screen_size.y / 8);
					int YOffset = 40;

					if (m_settings::SelectedHotbar == 1 || m_settings::SelectedHotbar == 2) {
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerHotbar(m_Event, { x,  YPos - YOffset + 20 }, WindowSize);
						YOffset += 25.f;
					}

					if (m_settings::SelectedClothing == 1 || m_settings::SelectedClothing == 2) {
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerClothing(m_Event, { x,  YPos + YOffset }, WindowSize);
						YOffset += 25.f;
					}

					if (m_settings::HerbertPrefabSpawn || m_settings::AmongusPrefabSpawn)
						prefab_spawner();

					Visuals().CachePlayers();
					Visuals().DrawPlayers();

					Visuals().CacheEntities();
					Visuals().RenderEntities();
				}	
			}

			TextDrawEnd();
		}
	}


	if (UnityEngine::Input::GetKey(RustStructs::End))
	{
		connector::cheat_message msg;
		msg.msg = connector::messages::LEAVE_SHARED_ESP;
		msg.value = XS("TrollServer1"); //Name of channel
		auto data = connector::data(msg);
		net->send_data(data);
		delete net;

		MenuIconBundles->Unload(true);
		MenuIconBundles = nullptr;

		SerotoninIconBundle->Unload(true);
		SerotoninIconBundle = nullptr;

		/* Chams */
		{

			if (HerbetAsset)
			{
				HerbetAsset->Unload(true);
				HerbetAsset = nullptr;

				if (HerbertPrefab)
				{
					HerbertPrefab = nullptr;
				}
			}

			if (AmongUsAsset)
			{
				AmongUsAsset->Unload(true);
				AmongUsAsset = nullptr;

				if (AmongusPrefab)
				{
					AmongusPrefab = nullptr;
				}
			}

			if (ExplosionAsset)
			{
				ExplosionAsset->Unload(true);
				ExplosionAsset = nullptr;

				if (ExplosionPrefab)
				{
					ExplosionPrefab = nullptr;
				}
			}

			if (GhostAsset)
			{
				GhostAsset->Unload(true);
				GhostAsset = nullptr;

				if (GhostPrefab)
				{
					GhostPrefab = nullptr;
				}
			}

			if (TestAsset)
			{
				TestAsset->Unload(true);
				TestAsset = nullptr;

				if (TestPrefab)
				{
					TestPrefab = nullptr;
				}
			}



			if (GalaxyBundle)
			{
				GalaxyBundle->Unload(true);
				GalaxyBundle = nullptr;
				GalaxyShader = nullptr;
				GalaxyMaterial = nullptr;
			}

			if (WireFrameBundle)
			{
				WireFrameBundle->Unload(true);
				WireFrameBundle = nullptr;
				WireFrameShader = nullptr;
				WireFrameMaterial = nullptr;
			}

			if (FireBundleA)
			{
				FireBundleA->Unload(true);
				FireBundleA = nullptr;
				FireShaderA = nullptr;
				FireMaterialA = nullptr;
			}

			if (RPBGalaxyBundle)
			{
				RPBGalaxyBundle->Unload(true);
				RPBGalaxyBundle = nullptr;
				RPBGalaxyShader = nullptr;
				RPBGalaxyMaterial = nullptr;
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

			if (ColorBundle)
			{
				ColorBundle->Unload(true);
				ColorBundle = nullptr;
				ColorShader = nullptr;
				ColorMaterial = nullptr;
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


		Hooks::ClientInputhk.Unhook();
		ConnectionManager().Instance()->ResetPlayerCache();
		Hooks::ProjectileShootHookhk.Unhook();
		Hooks::DoAttackhk.Unhook();
		Hooks::ProjectileUpdatehk.Unhook();
		Hooks::PPA_WriteToStreamhk.Unhook();
		Hooks::PlayerWalkMovementhk.Unhook();
		Hooks::TryToMovehk.Unhook();
		Hooks::SkyUpdatehk.Unhook();
		Hooks::SteamPlatformUpdatehk.Unhook();
		Hooks::OnAttackedhk.Unhook();
		Hooks::OnGUIhk.Unhook();
		Hooks::Update_hk.Unhook();
		Hooks::BlockSprinthk.Unhook();
		Hooks::LateUpdatehk.Unhook();
		Hooks::OnNetworkMessagehk.Unhook();
		Hooks::OnInputhk.Unhook();
		Hooks::DoAttackBowhk.Unhook();
		Hooks::DoAttackMeleehk.Unhook();

		Hooks::FlintStrikeWeaponDoAttackhk.Unhook();
	}
	
	return;
}