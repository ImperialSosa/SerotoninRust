#include "Menu.hpp"
#include "../../Includes/settings.hpp"
inline bool aim_type_opened;

void MenuDraw::RenderMenu()
{
	auto m_Event = UnityEngine::Event::Current();
	tab_size = Vector2(100, 35);

	auto mouse = UnityEngine::Input::GetMousePosition();

	auto width = UnityEngine::Screen::get_width();
	auto height = UnityEngine::Screen::get_height();

	Vector2 pos, menu_pos = window_position, menu_size = { 500, 380 }, button_size = { 200, 0 }, mouse_pos = { mouse.x, height - mouse.y };

	if (UnityEngine::Input::GetKey(RustStructs::Mouse0)) {
		auto z = UnityEngine::rect_t{ window_position.x, window_position.y, menu_size.x, 30 };

		if (z.contains(mouse_pos))
		{
			window_position = (window_position + (mouse_pos - window_position) - Vector2(250, 15));
		}
		lmp = mouse_pos;
	}

	menu_event = m_Event->Type();

	main_menu_open = Menu().window(m_Event, XS(L"Rust Cheat"), { 50, 50 }, { 517, 343 }, false);

	if (main_menu_open) {
		Menu().Tab(XS(L"Aimbot"), 0, Vector2(112, 35));
		Menu().Tab(XS(L"Esp"), 1, Vector2(112, 35));
		Menu().Tab(XS(L"Misc"), 2, Vector2(112, 35));
		Menu().Tab(XS(L"Weapon"), 3, Vector2(112, 35));
		Menu().Tab(XS(L"Settings"), 4, Vector2(112, 35));
		switch (activetab)
		{
		case 0:
		{
			Menu().SubTab(XS(L"Aimbot"), 0, Vector2(156, 35)); //468
			Menu().SubTab(XS(L"Exploits"), 1, Vector2(156, 35));
			Menu().SubTab(XS(L"Visuals"), 2, Vector2(156, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS(L"Aimbot"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Silent Aimbot"), m_settings::SilentAim);
					Menu().CheckBox(XS(L"Melee Aimbot"), m_settings::MeleeAimbot);
					Menu().CheckBox(XS(L"Heli Aimbot"), m_settings::HeliAimbot);
					Menu().CheckBox(XS(L"Silent Melee"), m_settings::SilentMelee);
					if (m_settings::HeliAimbot)
					{
						Menu().CheckBox(XS(L"Heli Override"), m_settings::HeliHitboxOverride);
					}
					Menu().Slider(XS(L"Accuracy"), m_settings::AimbotAccuracy, 0, 100);
					Menu().Slider(XS(L"Fov Slider"), m_settings::AimbotFOV, 0, 1000);
					Menu().Dropdown(XS("Aimbone"), { XS("Head"), XS("Neck"), XS("Chest"), XS("Random"), XS("Closest To Crosshair") }, m_settings::SelectedAimbone, aim_type_opened);


					//Menu().Slider(XS(L"Bulletspeed"), m_settings::BulletsSpeeds, 0, 3);
					//if (m_settings::Manipulation)
					//{
					//	Menu().Spacer(50);
					//	Menu().Hotkey(XS(L"Manipulation Key"), m_settings::ManipulationKey);
					//	//Menu().CheckBox(XS(L"incude bullet tp"), m_settings::IncludeFatBullet);
					//}

					//Menu().Slider(XS(L"test slider"), textnigga, 5, 1337);
					//Menu().Spacer(50);
					///Menu().Hotkey(XS(L"Manipulation Key"), ManipulationKey);

					////Menu().ListBox("test listbox", parsed_scripts, selected_script);
					//Menu().Dropdown(XS("aim type"), { XS("aimlock"), XS("silent") }, aim_type, aim_type_opened);
					//Menu().Dropdown(XS("test"), { XS("test3"), XS("test4") }, aim_ty2pe, aim_type_opene2);

					////Menu().Spacer(15);
					//Menu().MultiDropdown(XS("options"), { XS("box"),XS("name"), XS("health"), XS("ammo"), XS("weapon") }, player_esp_options, player_esp_options_opened);
					//Menu().Spacer(50);
					//Menu().Hotkey(XS(L"test Key"), testkey);
				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					//Unity_String aTest2[] = { Unity_String(XS(L"Head")), Unity_String(XS(L"Neck")),Unity_String(XS(L"Chest")),Unity_String(XS(L"Random")),Unity_String(XS(L"Closest to Crosshair")) };

					//Menu().Button(XS("dees nuts"), &test);
					//Menu().Spacer(15);
					//Menu().Hotkey(XS(L"InstantKill Key"), testkey);

					Menu().CheckBox(XS(L"Target NPC"), m_settings::AimbotNPC);
					Menu().CheckBox(XS(L"Target Wounded"), m_settings::TargetWounded);
					Menu().CheckBox(XS(L"Target FriendList"), m_settings::TargetFriendList);

					//Menu().Dropdown(XS(L"Target Bone"), m_settings::SelectedAimbone, aTest2, 5)


				}
				break;
			case 1:
				Menu().BeginChild(XS(L"Exploits"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBoxKeyBind(XS(L"Manipulation"), m_settings::Manipulation, m_settings::ManipKey);
					Menu().CheckBoxKeyBind(XS(L"AutoShoot"), m_settings::Autoshoot, m_settings::AutoshootKey);

					//Menu().CheckBox(XS(L"Autoshoot"), m_settings::Autoshoot);
					if (m_settings::Autoshoot)
					{
						Menu().CheckBox(XS(L"AlwaysAutoshoot"), m_settings::AlwaysAutoshoot);
						//Menu().CheckBox(XS(L"OnHalfDesync"), m_settings::OnHalfDesync);
					}
					Menu().CheckBox(XS(L"BulletTp"), m_settings::BulletTP);
					Menu().CheckBox(XS(L"AutoStop"), m_settings::StopPlayer);
					//if (m_settings::BulletTP)
					//{
					//	if (m_settings::BTPType == 1)
					//	{
					//		Menu().CheckBox(XS(L"AdvancedAngleScans"), m_settings::BulletTPAnglesAll);
					//	}
					//}
					Menu().CheckBox(XS(L"PierceMaterials"), m_settings::PierceMaterials);
					Menu().CheckBox(XS(L"Bullet Queue"), m_settings::InstantKill);
					if (m_settings::InstantKill)
					{
						Menu().CheckBox(XS(L"WaitForBulletTP"), m_settings::WaitForBulletTP);
					}

					Menu().CheckBox(XS(L"Instant Hit"), m_settings::InstantBullet);
					Menu().CheckBox(XS(L"WaitForInstantHit"), m_settings::WaitForInstantHit);

					//	Menu().CheckBox(XS(L"Floor Hugger"), m_settings::FloorHugger);

						//Menu().Dropdown(XS("BulletTPType"), { XS("Default"), XS("Advanced") }, m_settings::BTPType, BTPTypefffff);


				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Auto Reload"), m_settings::AutoReload);

					//Menu().CheckBox(XS(L"Hitbox Override"), m_settings::HitboxOverride);
					//if (m_settings::HitboxOverride)
					//{
					//	Menu().Dropdown(XS("Hitbox"), { XS("Head"), XS("Chest"), XS("Random") }, m_settings::SelectedHitbox, aim_type_opene2);
					//}

					//if (m_settings::BulletTP)
					//	Menu().Dropdown(XS("BTP Mode"), { XS("Low"), XS("Medium"), XS("High"), XS("Intense (FPS)") }, m_settings::BulletTPIntensity, bullet_tpe_open);

				}
				break;

			case 2:
				Menu().BeginChild(XS(L"Visuals"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Crosshair"), m_settings::Crosshair);
					Menu().CheckBox(XS(L"FOV Circle"), m_settings::DrawFov);
					Menu().CheckBox(XS(L"Target Snapline"), m_settings::Aimline);
					Menu().CheckBox(XS(L"Target Marker"), m_settings::AimMarker);
					Menu().CheckBox(XS(L"Target Indicator"), m_settings::Target_Indicator);
					Menu().CheckBox(XS(L"Bullet Tracers"), m_settings::BulletTracers);
					//Simulate Projectile
					Menu().CheckBox(XS(L"Manipulation Indicator"), m_settings::ManipFlags);
					Menu().CheckBox(XS(L"BulletTP Indicator"), m_settings::BulletTPFlags);
					Menu().CheckBox(XS(L"BulletTP Arrows"), m_settings::Thickbullet_Arrows);
					Menu().CheckBox(XS(L"BulletTP Angle"), m_settings::ShowBulletTPAngle);

				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					//Menu().Button(XS("dees nuts"), &test);
				}
				break;
			}

		}
			break;
		case 1:
			//VisualTab().DrawVisualTab();
			break;
		case 2:
			//SettingsTab().DrawSettingsTab();
			break;
		case 3:
			//WeaponTab().DrawWeaponTab();
			break;
		case 4:
			//ColorTab().DrawColorTab();
			break;
		}
	}

	Menu().end_window();
}