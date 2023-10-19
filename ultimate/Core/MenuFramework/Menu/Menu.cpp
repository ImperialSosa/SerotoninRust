#include "Menu.hpp"
#include "../../Includes/settings.hpp"
inline bool aim_type_opened;
inline bool chams_type_opened;
inline bool bullet_tpe_open;
inline bool config_type_open;
inline bool hitmat_open;
inline bool upgrade_open;
inline bool gesutre_open;
inline bool font_open;

inline bool esp_type_open;
inline bool wchams_type_opens;
inline bool heldi_type_open;
inline bool hotbar_type_opne;
inline bool clothing_type_open;
inline bool vischeck_type_openm;
inline bool healthbar_tpype_oepn;
inline bool killeffect_type_open;
inline bool inside_Tyope_opem;
inline bool manip_type_openm;
inline bool aim_type_opene2;

inline bool multi_type_test_open;
inline bool multi_chams_load;
inline bool multi_effect_load;
inline bool multi_food_option;
inline bool multi_ore_options;
inline bool multi_collectable_options;
inline bool multi_crate_options;
inline bool multi_turret_options;
inline bool multi_traps_options;
inline bool multi_vehicle_options;
inline bool multi_raid_options;
inline bool multi_cupboard_options;
inline bool multi_deployable_options;

#include "../../Configs/Configs.hpp"
#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

#include "../../Features/Visuals/Visuals.hpp"
auto reset_player_model()
{
	if (InGame)
	{
		AssemblyCSharp::PlayerModel().RebuildAll();
	}
}
void MenuDraw::RenderOptions()
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

	main_menu_open = Menu().window(m_Event, XS(L"Rust Cheat"), { 50, 50 }, { 520, 350 }, false, true);

	Vector2 IconSize = { 256, 256 };

	if (main_menu_open) {

		Menu().BeginChild(XS("Serotonin"), { 60,45 }, { 451,296 }, true);
		{
			
			Menu().DrawLogo(Vector2(156, 30), Vector2(IconSize), Color::White(), true);

			Menu().Spacer(210);

			Menu().Text(XS("Please Select a version you would like to load"), true); //	     

			Menu().SpacerX(70);
			Menu().Button(XS("Legit"), Buttons::LoadLegitCheat, true); //450 / 2 - (spacer: 5)
			Menu().Button(XS("Rage"), Buttons::LoadRageCheat);

			
		}		
	}

	Menu().end_window();
}

void MenuDraw::RenderLegitMenu()
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
			Menu().SubTab(XS("Aimbot"), 0, Vector2(156, 35)); //468
			Menu().SubTab(XS("Exploits"), 1, Vector2(156, 35));
			Menu().SubTab(XS("Visuals"), 2, Vector2(156, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS("Aimbot"), { 60,45 }, { 220,290 });
				{

					Menu().CheckBoxKeyBind(XS("Silent Aimbot (Legit)"), m_settings::RotationAimbot, m_settings::RotationKey);
					if (m_settings::RotationAimbot)
					{
						m_settings::SilentAim = false;
						m_settings::VelocityAimbot = false;
						m_settings::Manipulation = false;
						m_settings::BulletTP = false;
						m_settings::InstantBullet = false;
						m_settings::InstantKill = false;
					}

					Menu().Slider(XS("Accuracy"), m_settings::AimbotAccuracy, 0, 100);
					Menu().Slider(XS("Fov Slider"), m_settings::AimbotFOV, 0, 1000);

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{

					Menu().CheckBox(XS("Target NPC"), m_settings::AimbotNPC);
					Menu().CheckBox(XS("Target Wounded"), m_settings::TargetWounded);
					//Menu().CheckBox(XS(L"Target FriendList"), m_settings::TargetFriendList);

					Menu().Dropdown(XS("Aimbone"), { XS("Head"), XS("Neck"), XS("Chest"), XS("Random"), XS("Closest To Crosshair") }, m_settings::SelectedAimbone, aim_type_opened);

				}
				break;
			case 1:
				Menu().BeginChild(XS("Exploits"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("Recoil Modifier"), m_settings::ChangeRecoil);
					if (m_settings::ChangeRecoil) {
						Menu().Slider(XS("Recoil Percent"), m_settings::recoilPercent, 0, 100);
						//	Menu().Slider(XS("Recoil Percent Y"), m_settings::RecoilPercentY, 0, 100);
					}
					Menu().Slider(XS("Spread Percent"), m_settings::SilentSpread, 0, 100);
					Menu().CheckBox(XS("Thickness Modifier"), m_settings::NormalThickBullet);
					if (m_settings::NormalThickBullet) {
						Menu().Slider(XS("Bullet Thickness"), m_settings::NormalThickBulletThickness, 0, 4.5);
					}
				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{

				}
				break;

			case 2:
				Menu().BeginChild(XS("Visuals"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("Crosshair"), m_settings::Crosshair);
					if (m_settings::Crosshair)
					{
						m_settings::Swastika = false;
					}

					//Menu().CheckBox(XS("SwastikaCrosshair"), m_settings::Swastika);
					if (m_settings::Swastika)
					{
						m_settings::Crosshair = false;
						Menu().Slider(XS("SwastikaSize"), m_settings::SwastikaSize, 1, 20);
					}
					Menu().CheckBox(XS("FOV Circle"), m_settings::DrawFov);

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("Target Snapline"), m_settings::Aimline);
					Menu().CheckBox(XS("Target Marker"), m_settings::AimMarker);
					Menu().CheckBox(XS("Target Indicator"), m_settings::Target_Indicator);
					Menu().CheckBox(XS("Bullet Tracers"), m_settings::BulletTracers);
				}
				break;
			}

			break;
		}
		case 1:
		{
			Menu().SubTab(XS("Player"), 0, Vector2(117, 35)); //468
			Menu().SubTab(XS("Resources"), 1, Vector2(117, 35));
			Menu().SubTab(XS("Lootables"), 2, Vector2(117, 35));
			Menu().SubTab(XS("Other"), 3, Vector2(117, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS("Visuals"), { 60,45 }, { 220,290 });
				{

					Menu().CheckBox(XS("Username"), m_settings::nameEsp);
					Menu().CheckBox(XS("Skeleton"), m_settings::Skeleton);
					//Menu().CheckBox(XS("AmmoType"), m_settings::ammoESP);

					Menu().Dropdown(XS("BoxType"), { XS("None"), XS("Box"), XS("CornerBox") }, m_settings::SelectedBoxESP, esp_type_open);
					Menu().Dropdown(XS("HeldItem"), { XS("None"), XS("Text"), XS("Icons"), XS("Both") }, m_settings::HeldItemType, heldi_type_open);
					Menu().Dropdown(XS("HealthBar"), { XS("None"), XS("Bottom"), XS("Left") }, m_settings::SelectedHealthBar, healthbar_tpype_oepn);
					Menu().Dropdown(XS("Inventory"), { XS("None"), XS("Text"), XS("Icons") }, m_settings::SelectedHotbar, hotbar_type_opne);
					Menu().Dropdown(XS("Clothing"), { XS("None"), XS("Text"), XS("Icons") }, m_settings::SelectedClothing, clothing_type_open);
					Menu().Dropdown(XS("BaseCheck"), { XS("None"), XS("Outside"), XS("Inside"), XS("Both") }, m_settings::SelectedOutsideType, inside_Tyope_opem);
					Menu().Dropdown(XS("Vischeck"), { XS("None"), XS("Enabled"), XS("Tags Enabled"), XS("Both") }, m_settings::VisCheckType, vischeck_type_openm);
					Menu().MultiDropdown(XS("Load Chams"), { XS("Lightning"), XS("Geometric"), XS("Galaxy"), XS("WireFrame") }, m_settings::LoadChams, multi_type_test_open);
					Menu().Dropdown(XS("Chams"), { XS("None"), XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame"), XS("VisColor") }, m_settings::SelectedChams, chams_type_opened);

					if (m_settings::SelectedChams == 0)
						m_settings::PlayerChams = false;
					else
						m_settings::PlayerChams = true;

					if (m_settings::VisCheckType == 0) {
						m_settings::EspVisCheck = false;
						m_settings::TagsVisCheck = false;
					}
					else if (m_settings::VisCheckType == 1) {
						m_settings::EspVisCheck = true;
						m_settings::TagsVisCheck = false;
					}
					else if (m_settings::VisCheckType == 2) {
						m_settings::EspVisCheck = false;
						m_settings::TagsVisCheck = true;
					}
					else if (m_settings::VisCheckType == 3) {
						m_settings::EspVisCheck = true;
						m_settings::TagsVisCheck = true;
					}


					if (m_settings::LoadChams[0]) {
						static bool HasLoaded = false;
						if (!HasLoaded)
							m_settings::LoadLightning = true;
					}
					if (m_settings::LoadChams[1]) {
						static bool HasLoaded = false;
						if (!HasLoaded)
							m_settings::LoadGeometric = true;
					}
					if (m_settings::LoadChams[2]) {
						static bool HasLoaded = false;
						if (!HasLoaded)
							m_settings::LoadGalaxy = true;
					}
					if (m_settings::LoadChams[3]) {
						static bool HasLoaded = false;
						if (!HasLoaded)
							m_settings::LoadWireFrame = true;
					}

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("Corpse"), m_settings::Corpse);
					Menu().CheckBox(XS("Backpack"), m_settings::BackPack);
					Menu().CheckBox(XS("ShowAlerts"), m_settings::ShowAlerts);
					Menu().CheckBox(XS("Radar"), m_settings::Radar);
					Menu().CheckBoxKeyBind(XS("Save Pos"), m_settings::SavePos, m_settings::SavePosKey);
					Menu().CheckBox(XS("Show Target"), m_settings::DrawTarget);
					Menu().CheckBox(XS("Wounded"), m_settings::DrawWounded);
					Menu().CheckBox(XS("Safezone"), m_settings::DrawSafezone);
					Menu().CheckBox(XS("Npc's"), m_settings::DrawNPC);
					Menu().CheckBox(XS("Sleepers"), m_settings::DrawSleepers);
					//Menu().CheckBox(XS("Disconnected"), m_settings::DrawAis);
					//Menu().CheckBox(XS("ShowCheatsUsers"), m_settings::ShowUsers);

					Menu().Slider(XS("PlayerDistance"), m_settings::PlayerESPDistance, 0, 500);
					Menu().Slider(XS("NPC Distance"), m_settings::NPCDistance, 0, 500);
					Menu().Slider(XS("Drops Distance"), m_settings::MaxPlayerDropsDistance, 0, 500);
					Menu().Slider(XS("RadarSize"), m_settings::RadarSize, 0, 300);
				}
				break;
			case 1:
				Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
				{
					Menu().MultiDropdown(XS("Ores"), { XS("Stone"), XS("Metal"), XS("Sulfur") }, m_settings::OreOptions, multi_ore_options);
					{
						if (m_settings::OreOptions[0])
							m_settings::StoneOre = true;
						else
							m_settings::StoneOre = false;
						if (m_settings::OreOptions[1])
							m_settings::MetalOre = true;
						else
							m_settings::MetalOre = false;
						if (m_settings::OreOptions[2])
							m_settings::SulfurOre = true;
						else
							m_settings::SulfurOre = false;
					}

					Menu().MultiDropdown(XS("Collectables"), { XS("Hemp"), XS("Diesel"), XS("Stone") , XS("Metal") , XS("Sulfur") }, m_settings::CollectableOpions, multi_collectable_options);
					{
						if (m_settings::CollectableOpions[0])
							m_settings::Hemp = true;
						else
							m_settings::Hemp = false;
						if (m_settings::CollectableOpions[1])
							m_settings::DieselBarrel = true;
						else
							m_settings::DieselBarrel = false;

						if (m_settings::CollectableOpions[2])
							m_settings::StoneCollectable = true;
						else
							m_settings::StoneCollectable = false;

						if (m_settings::CollectableOpions[3])
							m_settings::MetalCollectable = true;
						else
							m_settings::MetalCollectable = false;

						if (m_settings::CollectableOpions[4])
							m_settings::SulfurCollectable = true;
						else
							m_settings::SulfurCollectable = false;

					}

					Menu().MultiDropdown(XS("Food"), { XS("Corn"), XS("Pumpkin"), XS("Potato"), XS("Mushroom") }, m_settings::FoodOptions, multi_food_option);
					{
						if (m_settings::FoodOptions[0])
							m_settings::Corn = true;
						else
							m_settings::Corn = false;
						if (m_settings::FoodOptions[1])
							m_settings::Pumpkin = true;
						else
							m_settings::Pumpkin = false;
						if (m_settings::FoodOptions[2])
							m_settings::Potato = true;
						else
							m_settings::Potato = false;
						if (m_settings::FoodOptions[3])
							m_settings::Mushroom = true;
						else
							m_settings::Mushroom = false;
					}
				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().Slider(XS("Ore Distance"), m_settings::MaxOreDistance, 0, 500);
					Menu().Slider(XS("Collectables Distance"), m_settings::MaxCollectableDistance, 0, 500);
					Menu().Slider(XS("Food Distance"), m_settings::MaxFoodDistance, 0, 500);
				}
				break;

			case 2:
				Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
				{
					Menu().MultiDropdown(XS("Deployables"), { XS("Stash"), XS("Cupboard"), XS("T1 Workbench"), XS("T2 Workbench") , XS("T3 Workbench") }, m_settings::DeployableOptions, multi_deployable_options);
					{
						if (m_settings::DeployableOptions[0])
							m_settings::Stash = true;
						else
							m_settings::Stash = false;

						if (m_settings::DeployableOptions[1])
							m_settings::cupboard = true;
						else
							m_settings::cupboard = false;

						if (m_settings::DeployableOptions[2])
							m_settings::T1Workbench = true;
						else
							m_settings::T1Workbench = false;

						if (m_settings::DeployableOptions[3])
							m_settings::T2Workbench = true;
						else
							m_settings::T2Workbench = false;

						if (m_settings::DeployableOptions[4])
							m_settings::T3Workbench = true;
						else
							m_settings::T3Workbench = false;

					}
					if (m_settings::cupboard) {
						Menu().MultiDropdown(XS("Cupboard"), { XS("TC Health"), XS("Authed Players"), XS("Upkeep") }, m_settings::CupboardOptions, multi_cupboard_options);
						{
							if (m_settings::CupboardOptions[0])
								m_settings::TC_Health = true;
							else
								m_settings::TC_Health = false;

							if (m_settings::CupboardOptions[1])
								m_settings::AuthorizedPlayers = true;
							else
								m_settings::AuthorizedPlayers = false;

							if (m_settings::CupboardOptions[2])
								m_settings::TC_Upkeep = true;
							else
								m_settings::TC_Upkeep = false;

						}
					}
					Menu().MultiDropdown(XS("Crates"), { XS("Airdrop"), XS("Bradley"), XS("Heli"), XS("Hackable"), XS("Basic"), XS("Normal"), XS("Military"), XS("Elite"), XS("Loot Barrels") }, m_settings::CrateOptions, multi_crate_options);
					{
						if (m_settings::CrateOptions[0])
							m_settings::SupplyDrop = true;
						else
							m_settings::SupplyDrop = false;
						if (m_settings::CrateOptions[1])
							m_settings::BradleyCrate = true;
						else
							m_settings::BradleyCrate = false;
						if (m_settings::CrateOptions[2])
							m_settings::HeliCrate = true;
						else
							m_settings::HeliCrate = false;
						if (m_settings::CrateOptions[3])
							m_settings::HackableCrate = true;
						else
							m_settings::HackableCrate = false;
						if (m_settings::CrateOptions[4])
							m_settings::BasicCrate = true;
						else
							m_settings::BasicCrate = false;
						if (m_settings::CrateOptions[5])
							m_settings::NormalCrate = true;
						else
							m_settings::NormalCrate = false;
						if (m_settings::CrateOptions[6])
							m_settings::MilitaryCrate = true;
						else
							m_settings::MilitaryCrate = false;
						if (m_settings::CrateOptions[7])
							m_settings::EliteCrate = true;
						else
							m_settings::EliteCrate = false;
						if (m_settings::CrateOptions[8])
							m_settings::LootBarrel = true;
						else
							m_settings::LootBarrel = false;

						if (m_settings::HackableCrate)
						{
							m_settings::HackableCrateFlags = true;
							m_settings::HackableCrateTimer = true;
						}
					}

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().Slider(XS("Crates Distance"), m_settings::MaxCrateDistance, 0, 500);
					Menu().Slider(XS("Airdrop Distance"), m_settings::MaxSupplyDropDistance, 0, 500);
				}
				break;

			case 3:
				Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("DroppedItems"), m_settings::DroppedItems);
					Menu().MultiDropdown(XS("Traps"), { XS("Turret"), XS("ShotgunTrap"), XS("FlameTurret"), XS("BearTrap"), XS("SpikesTrap"), XS("LandMine"), XS("SamSite") }, m_settings::TrapsOptions, multi_traps_options);
					{
						if (m_settings::TrapsOptions[0])
							m_settings::AutoTurret = true;
						else
							m_settings::AutoTurret = false;

						if (m_settings::TrapsOptions[1])
							m_settings::ShotgunTrap = true;
						else
							m_settings::ShotgunTrap = false;

						if (m_settings::TrapsOptions[2])
							m_settings::FlameTurret = true;
						else
							m_settings::FlameTurret = false;

						if (m_settings::TrapsOptions[3])
							m_settings::BearTrap = true;
						else
							m_settings::BearTrap = false;

						if (m_settings::TrapsOptions[4])
							m_settings::SpikesTrap = true;
						else
							m_settings::SpikesTrap = false;

						if (m_settings::TrapsOptions[5])
							m_settings::LandMine = true;
						else
							m_settings::LandMine = false;

						if (m_settings::TrapsOptions[6])
							m_settings::SamSite = true;
						else
							m_settings::SamSite = false;
					}
					if (m_settings::AutoTurret)
					{
						Menu().MultiDropdown(XS("Turret Settings"), { XS("Authed Players"), XS("EquippedFlag"), XS("ShowOnline"), XS("Health"), XS("TurningFlags"), XS("Range"), }, m_settings::TurretOptions, multi_turret_options);

						{
							if (m_settings::TurretOptions[0])
								m_settings::TurretAuthorizedPlayers = true;
							else
								m_settings::TurretAuthorizedPlayers = false;

							if (m_settings::TurretOptions[1])
								m_settings::TurretEquippedFlags = true;
							else
								m_settings::TurretEquippedFlags = false;

							if (m_settings::TurretOptions[2])
								m_settings::TurretOnFlags = true;
							else
								m_settings::TurretOnFlags = false;

							if (m_settings::TurretOptions[3])
								m_settings::TurretHealth = true;
							else
								m_settings::TurretHealth = false;

							if (m_settings::TurretOptions[4])
								m_settings::TurretTurningFlag = true;
							else
								m_settings::TurretTurningFlag = false;

							if (m_settings::TurretOptions[5])
								m_settings::TurretRange = true;
							else
								m_settings::TurretRange = false;

						}
					}

					Menu().MultiDropdown(XS("Vehicles"), { XS("PatrolHeli"), XS("Bradley"), XS("MiniCopter"), XS("ScrapHeli"), XS("AttackHeli"), XS("TugBoat"), XS("RHIB"), XS("RowBoat") }, m_settings::VehicleOptions, multi_vehicle_options);
					{
						if (m_settings::VehicleOptions[0])
							m_settings::PatrolHelicopter = true;
						else
							m_settings::PatrolHelicopter = false;

						if (m_settings::VehicleOptions[1])
							m_settings::BradleyAPC = true;
						else
							m_settings::BradleyAPC = false;

						if (m_settings::VehicleOptions[2])
							m_settings::Minicopter = true;
						else
							m_settings::Minicopter = false;

						if (m_settings::VehicleOptions[3])
							m_settings::ScrapHeli = true;
						else
							m_settings::ScrapHeli = false;

						if (m_settings::VehicleOptions[4])
							m_settings::AttackHeli = true;
						else
							m_settings::AttackHeli = false;

						if (m_settings::VehicleOptions[5])
							m_settings::TugBoat = true;
						else
							m_settings::TugBoat = false;

						if (m_settings::VehicleOptions[6])
							m_settings::Rhib = true;
						else
							m_settings::Rhib = false;

						if (m_settings::VehicleOptions[7])
							m_settings::Rowboat = true;
						else
							m_settings::Rowboat = false;
					}


					//Menu().MultiDropdown(XS("Raid ESP"), { XS("Enable"), XS("C4"), XS("Rockets"), XS("Satchels"), XS("ExploAmmo") }, m_settings::RaidOptions, multi_raid_options);
					{
						if (m_settings::RaidOptions[0])
							m_settings::RaidESP = true;
						else
							m_settings::RaidESP = false;

						if (m_settings::RaidOptions[1])
							m_settings::ShowC4 = true;
						else
							m_settings::ShowC4 = false;

						if (m_settings::RaidOptions[2])
							m_settings::ShowRocket = true;
						else
							m_settings::ShowRocket = false;

						if (m_settings::RaidOptions[3])
							m_settings::ShowSatchel = true;
						else
							m_settings::ShowSatchel = false;

						if (m_settings::RaidOptions[4])
							m_settings::ShowExplosiveAmmo = true;
						else
							m_settings::ShowExplosiveAmmo = false;
					}


				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().Slider(XS("Dropped Distance"), m_settings::MaxDroppedDistance, 0, 500);
					Menu().Slider(XS("Traps Distance"), m_settings::MaxTrapsDistance, 0, 500);
					Menu().Slider(XS("APC Distance"), m_settings::MaxAPCDistance, 0, 3000);
					Menu().Slider(XS("Vehicle Distance"), m_settings::MaxVehicleDistance, 0, 500);

					Menu().Slider(XS("Raid Distance"), m_settings::MaxExplosionDistance, 0, 5000);
					Menu().Slider(XS("AuthDistance"), m_settings::AuthorizedPlayersDistance, 0, 300);
					Menu().Slider(XS("Raid Timer"), m_settings::MaxRaidTimer, 0, 300);

				}
				break;
			}

			break;
		}
		case 2:
		{
			Menu().SubTab(XS("LocalPlayer"), 0, Vector2(156, 35)); //468
			Menu().SubTab(XS("Other"), 1, Vector2(156, 35));
			Menu().SubTab(XS("Prefab"), 2, Vector2(156, 35));
			//Menu().SubTab(XS(L"World"), 3, Vector2(117, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS("LocalPlayer"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("Flyhack Indicator"), m_settings::Flyhack_Indicator);
					Menu().CheckBox(XS("Anti FlyhackKick"), m_settings::AntiFlyKick);
					Menu().CheckBox(XS("Anti DeathBarrier"), m_settings::AntiDeathBarrier);
					Menu().CheckBox(XS("Spiderman"), m_settings::SpiderMan);
					Menu().CheckBox(XS("SmallerLocalRadius"), m_settings::SmallerLocalRadius);
					Menu().CheckBox(XS("Admin Flags"), m_settings::AdminFlags);
					Menu().CheckBox(XS("Infinite Jump"), m_settings::InfiniteJump);
					Menu().CheckBox(XS("Omnisprint"), m_settings::OmniSprint);
					Menu().CheckBox(XS("ToggleSprint"), m_settings::AlwaysSprint);
					Menu().CheckBox(XS("NoMovementReduction"), m_settings::NoMovementRestrictions);

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("NameSpoofer"), m_settings::NameSpoofer);
					//Menu().CheckBox(XS("BlockServerCommands"), m_settings::BlockServerCommands);
					Menu().CheckBox(XS("Instant Loot"), m_settings::InstantLoot);
					Menu().CheckBox(XS("Instant Heal"), m_settings::InstantHeal);
					Menu().CheckBox(XS("Adjust NoClipSpeed"), m_settings::AdjustNoClipSpeed);
					Menu().CheckBoxKeyBind(XS("NoClip"), m_settings::AdminCheat, m_settings::AdminCheatKey);

					Menu().CheckBox(XS("FixDebugCamera"), m_settings::FixDebugCamera);

				}
				break;
			case 1:
				Menu().BeginChild(XS("Misc"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBoxKeyBind(XS("Zoom"), m_settings::Zoom, m_settings::ZoomKey);
					if (m_settings::Zoom) {
						Menu().Slider(XS("Zoom Amount"), m_settings::ZoomAmount, 0, 50);
					}

					Menu().CheckBox(XS("PlayerFov"), m_settings::PlayerFov);
					if (m_settings::PlayerFov) {
						Menu().Slider(XS("PlayerFov Amount"), m_settings::PlayerFovAmount, 0, 140);
					}

					Menu().CheckBox(XS("AutoFarmTree"), m_settings::AutoFarmTree);
					Menu().CheckBox(XS("AutoFarmOre"), m_settings::AutoFarmOre);

				}

				Menu().BeginChild(XS("World"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("BrightNight"), m_settings::Brightnight);
					Menu().CheckBox(XS("BrightAmbient"), m_settings::BrightAmbient);
					Menu().CheckBox(XS("Stars"), m_settings::Stars);
					Menu().CheckBox(XS("SkyColor (Day)"), m_settings::SkyColorDay);
					Menu().CheckBox(XS("SkyColor (Night)"), m_settings::SkyColorNight);
					Menu().CheckBox(XS("SharpClouds"), m_settings::SharpClouds);
					Menu().CheckBox(XS("BrightCave"), m_settings::BrightCave);
					//Menu().CheckBox(XS("CustomSky"), m_settings::CustomSky);					

					Menu().CheckBox(XS("TimeChanger"), m_settings::TimeChanger);
					if (m_settings::TimeChanger) {
						Menu().Slider(XS("GameTime: "), m_settings::GameTime, 0, 24);
					}
					//Menu().CheckBox(XS("RemoveUnderwaterEffects"), m_settings::RemoveUnderwaterEffects);
				}
				break;

			case 2:
				Menu().BeginChild(XS("Prefab Spawner"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("LoadAmongus"), m_settings::LoadAmongusAsset);
					if (m_settings::LoadAmongusAsset) {
						Menu().CheckBoxKeyBind(XS("AmongusPrefab"), m_settings::AmongusPrefabSpawn, m_settings::AmongusKey);
					}
					Menu().CheckBox(XS("LoadHerbert"), m_settings::LoadHerbertAsset);
					if (m_settings::LoadHerbertAsset) {
						Menu().CheckBoxKeyBind(XS("HerbertPrefab"), m_settings::HerbertPrefabSpawn, m_settings::HerbertKey);
					}
				}

				Menu().BeginChild(XS("Settings"), { 285,45 }, { 220,290 });
				{

				}
				/*	Menu().BeginChild(XS("Friend List"), { 60,45 }, { 220,290 });
					{
						for (const auto& wideKey : wideKeys) {
							Menu().Text(wideKey.c_str());
						}
					}

					Menu().BeginChild(XS("Settings"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBoxKeyBind(XS("Add Friends"), m_settings::removefriend1, m_settings::AddFriend);
						Menu().CheckBoxKeyBind(XS("Remove Friend"), m_settings::removefriend2, m_settings::RemoveFriend);
						Menu().CheckBoxKeyBind(XS("Remove All"), m_settings::removefriend3, m_settings::RemoveAllFriends);
					}*/
				break;
			}

			break;
		}
		case 3:
		{
			Menu().SubTab(XS("Weapon"), 0, Vector2(156, 35)); //468
			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS("Weapon"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("No Attack Restrictions"), m_settings::NoAttackRestrictions);
					Menu().CheckBox(XS("Fast Bullet"), m_settings::NormalFastBullet);
					Menu().CheckBox(XS("Force Automatic"), m_settings::ForceAutomatic);
					Menu().CheckBox(XS("NoSway"), m_settings::NoSway);
					Menu().CheckBox(XS("InstantEoka"), m_settings::InstantEoka);

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("DisableHitSounds"), m_settings::DisableHitSounds);
					Menu().CheckBox(XS("CustomHitSounds"), m_settings::CustomHitSounds);

					Menu().CheckBox(XS("KillEffects"), m_settings::KillEffects);
					if (m_settings::KillEffects) {
						Menu().Dropdown(XS("Effect Type"), { XS("Explosion"), XS("Ghosts") }, m_settings::SelectedKillEffect, killeffect_type_open);
						Menu().MultiDropdown(XS("Load Effects"), { XS("Explosion"), XS("Ghosts") }, m_settings::LoadHitEffects, multi_effect_load);

						if (m_settings::LoadHitEffects[0]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadExplosionEffect = true;
						}
						if (m_settings::LoadHitEffects[1]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadGhostEffect = true;
						}
					}

					Menu().CheckBox(XS("WeaponChams"), m_settings::WeaponChams);
					if (m_settings::WeaponChams) {
						Menu().CheckBox(XS("IgnoreArms"), m_settings::IgnoreArms);

						Menu().Dropdown(XS("Chams Type"), { XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame") }, m_settings::WeaponSelectedChams, wchams_type_opens);
						Menu().MultiDropdown(XS("Load Chams"), { XS("Lightning"), XS("Geometric"), XS("Galaxy"), XS("WireFrame") }, m_settings::LoadChams, multi_chams_load);

						if (m_settings::LoadChams[0]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadLightning = true;
						}
						if (m_settings::LoadChams[1]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadGeometric = true;
						}
						if (m_settings::LoadChams[2]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadGalaxy = true;
						}
						if (m_settings::LoadChams[3]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadWireFrame = true;
						}
					}

				}
				break;
			}
			break;
		}
		case 4:
		{
			Menu().SubTab(XS("Settings"), 0, Vector2(156, 35)); //468

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS("Colors"), { 60,45 }, { 220,290 });
				{
					Menu().Button(XS("Reset PlayerModels"), reset_player_model);
					Menu().Button(XS("Reset LOS Points"), Buttons::ClearLOSPoints);
					Menu().Button(XS("Clear RaidCache"), Buttons::ClearRaidCache);
					Menu().Button(XS("Load RageCheat"), Buttons::LoadRageCheat);

					Menu().Spacer(30);

					Menu().Button(XS("Save Config"), Configs::SaveConfig);
					Menu().Button(XS("Load Config"), Configs::LoadConfig);
					Menu().Spacer(15);

					Menu().Dropdown(XS("Config Type"), { XS("Legit"), XS("Rage"), XS("Config1"), XS("Config2"), XS("Config3") }, m_settings::SelectedConfig, config_type_open);
				}

				Menu().BeginChild(XS("Configs"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS("OutlinedText"), m_settings::OutlinedText);
					if (m_settings::OutlinedText)
						m_settings::ShadedText = false;
					Menu().CheckBox(XS("ShadowedText"), m_settings::ShadedText);
					if (m_settings::ShadedText)
						m_settings::OutlinedText = false;
					Menu().CheckBox(XS("WorldOutlinedText"), m_settings::WorldOutlinedText);
					if (m_settings::WorldOutlinedText)
						m_settings::WorldShadedText = false;
					Menu().CheckBox(XS("WorldShadedText"), m_settings::WorldShadedText);
					if (m_settings::WorldShadedText)
						m_settings::WorldOutlinedText = false;
					Menu().Slider(XS("EspFontSize"), m_settings::ESPFontsize, 0, 15);
					Menu().Slider(XS("WorldFontSize"), m_settings::WorldFontSize, 0, 15);

					Menu().CheckBox(XS("FontChanger"), m_settings::FontChanger);
					if (m_settings::FontChanger) {
						Menu().Dropdown(XS("Font"), { XS("Default"), XS("Pixel"), XS("Verdana"), }, m_settings::fonttype, font_open);
					}
				}
				break;
			}
			break;
		}
		}
	}


	Menu().end_window();
}
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
				Menu().SubTab(XS("Aimbot"), 0, Vector2(156, 35)); //468
				Menu().SubTab(XS("Exploits"), 1, Vector2(156, 35));
				Menu().SubTab(XS("Visuals"), 2, Vector2(156, 35));

				switch (activesubtab)
				{
				case 0:
					Menu().BeginChild(XS("Aimbot"), { 60,45 }, { 220,290 });
					{
						//Menu().CheckBoxKeyBind(XS("Memory Aimbot"), m_settings::MemoryAimbot, m_settings::MemoryAimbotKey);
						//Menu().CheckBox(XS("AutoMed"), m_settings::AutoMed);

						//Menu().CheckBox(XS("WalkToMarker"), m_settings::WalkToMarker);
						//Menu().CheckBox(XS("ShowPrediction"), m_settings::ShowPrediction);
						Menu().CheckBoxKeyBind(XS("Silent Aimbot"), m_settings::SilentAim, m_settings::AimbotKey);
						//Menu().CheckBox(XS("Velocity Aimbot"), m_settings::VelocityAimbot);
						if (m_settings::SilentAim)
						{
							m_settings::RotationAimbot = false;
						}
						if (m_settings::VelocityAimbot)
						{
							m_settings::RotationAimbot = false;
						}

						Menu().CheckBox(XS("Melee Aimbot"), m_settings::MeleeAimbot);

						//Menu().CheckBox(XS(L"Heli Aimbot"), m_settings::HeliAimbot);
						Menu().CheckBox(XS("Silent Melee"), m_settings::SilentMelee);
						////if (m_settings::HeliAimbot)
						//{
						//	Menu().CheckBox(XS(L"Heli Override"), m_settings::HeliHitboxOverride);
						//}
						Menu().Slider(XS("Accuracy"), m_settings::AimbotAccuracy, 0, 100);
						Menu().Slider(XS("Fov Slider"), m_settings::AimbotFOV, 0, 1000);
						Menu().Slider(XS("Smoothing"), m_settings::AimbotSmoothness, 0, 10);
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{

						Menu().CheckBox(XS("Target NPC"), m_settings::AimbotNPC);
						Menu().CheckBox(XS("Target Wounded"), m_settings::TargetWounded);
						//Menu().CheckBox(XS(L"Target FriendList"), m_settings::TargetFriendList);

						Menu().Dropdown(XS("Aimbone"), { XS("Head"), XS("Neck"), XS("Chest"), XS("Random"), XS("Closest To Crosshair") }, m_settings::SelectedAimbone, aim_type_opened);

						//Menu().Spacer(50);

				
					}
					break;
				case 1:
					Menu().BeginChild(XS("Exploits"), { 60,45 }, { 220,290 });
					{
						static bool SetDefaults = false;
						if (!SetDefaults)
						{
							m_settings::CacheBulletTP = true;
							m_settings::AdvancedChecks = true;
							SetDefaults = true;
						}

						Menu().CheckBoxKeyBind(XS("AutoShoot"), m_settings::Autoshoot, m_settings::AutoshootKey);
						//if (m_settings::Autoshoot)
						//{
						//	Menu().CheckBox(XS("AlwaysAutoshoot"), m_settings::AlwaysAutoshoot);
						//}
						Menu().CheckBoxKeyBind(XS("Manipulation"), m_settings::Manipulation, m_settings::ManipKey);

						Menu().CheckBox(XS("BulletTp"), m_settings::BulletTP);
						if (m_settings::BulletTP) {
							Menu().CheckBox(XS("Cache BulletTP (Saves FPS)"), m_settings::CacheBulletTP);
							if (m_settings::CacheBulletTP)
							{
								Menu().CheckBox(XS("AdvancedCaching (Saves FPS)"), m_settings::AdvancedChecks);
							}
						}
						if (m_settings::BulletTP && m_settings::Manipulation) {
							Menu().CheckBox(XS("BehindWall (FPS)"), m_settings::BehindWall);
						}
						else {
							m_settings::BehindWall = false;
						}

						Menu().CheckBox(XS("AutoStop"), m_settings::StopPlayer);
						Menu().CheckBox(XS("PierceMaterials"), m_settings::PierceMaterials);
						Menu().CheckBox(XS("Bullet Queue"), m_settings::InstantKill);
						/*	if (m_settings::InstantKill)
						{
							Menu().CheckBox(XS("WaitForBulletTP"), m_settings::WaitForBulletTP);
						}*/
						Menu().CheckBox(XS("Instant Hit"), m_settings::InstantBullet);
						Menu().CheckBox(XS("WaitForInstantHit/Kill"), m_settings::WaitForInstantHit);
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("AutoReload"), m_settings::AutoReload);
						if (m_settings::AutoReload)
							Menu().CheckBox(XS("AutoReload Icon"), m_settings::AutoReloadIcon);

						Menu().CheckBox(XS("Hitbox Override"), m_settings::HitboxOverride);
						if (m_settings::HitboxOverride)
						{
							Menu().Dropdown(XS("Hitbox"), { XS("Head"), XS("Chest"), XS("Random") }, m_settings::SelectedHitbox, aim_type_opene2);
						}

						if (m_settings::Manipulation)
							Menu().Dropdown(XS("Manip-Mode"), { XS("Static Points"), XS("Dynamic Points"), XS("Enhanced Points") }, m_settings::ManipMode, manip_type_openm);

						if (m_settings::BulletTP)
							Menu().Dropdown(XS("BTP-Mode"), { XS("Static Angles"), XS("Dynamic Angles"), XS("Enhanced Angles")/*, XS("Cached Angles")*/}, m_settings::BulletTPIntensity, bullet_tpe_open);

						if (m_settings::BulletTPIntensity == 3) {
							m_settings::CacheBulletTP = true;
							m_settings::AdvancedChecks = true;
						}

						if (m_settings::Manipulation)
						{
							Menu().Slider(XS("ManipAngles"), m_settings::ManipPoints, 0, 100);
							if (m_settings::ManipPoints < 5)
								m_settings::ManipPoints = 5;
							//m_settings::ManipPoints
						}

						if (m_settings::CacheBulletTP) {
							Menu().Slider(XS("LOS Checks Amount"), m_settings::LOSCheckAmount, 0, 2000);
							if (m_settings::LOSCheckAmount < 500)
								m_settings::LOSCheckAmount = 500;
						}
					}
					break;

				case 2:
					Menu().BeginChild(XS("Visuals"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Crosshair"), m_settings::Crosshair);
						if (m_settings::Crosshair)
						{
							m_settings::Swastika = false;
						}

						//Menu().CheckBox(XS("SwastikaCrosshair"), m_settings::Swastika);
						//if (m_settings::Swastika)
						//{
						//	m_settings::Crosshair = false;
						//	Menu().Slider(XS("SwastikaSize"), m_settings::SwastikaSize, 1, 20);
						//}
						Menu().CheckBox(XS("FOV Circle"), m_settings::DrawFov);
						Menu().CheckBox(XS("Target Snapline"), m_settings::Aimline);
						Menu().CheckBox(XS("Target Marker"), m_settings::AimMarker);
						Menu().CheckBox(XS("Target Indicator"), m_settings::Target_Indicator);
						Menu().CheckBox(XS("Bullet Tracers"), m_settings::BulletTracers);
						Menu().Dropdown(XS("HitMaterial"), { XS("Flesh"), XS("Glass"), XS("Metal"), XS("Water") }, m_settings::HitMaterial, hitmat_open);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						//Simulate Projectile
						Menu().CheckBox(XS("Manipulation Indicator"), m_settings::ManipFlags);
						Menu().CheckBox(XS("Manip Angle"), m_settings::DrawManipPoints);
						Menu().CheckBox(XS("BulletTP Indicator"), m_settings::BulletTPFlags);
						Menu().CheckBox(XS("BulletTP Arrows"), m_settings::Thickbullet_Arrows);
						Menu().CheckBox(XS("BulletTP Angle"), m_settings::ShowBulletTPAngle);
						Menu().CheckBox(XS("Cached Indicator"), m_settings::ShowCachedLOS);
						Menu().CheckBox(XS("Cached Point"), m_settings::ShowCachedPoint);

						Menu().CheckBox(XS("SnickerBullet"), m_settings::SnickerBullet);
					}
					break;
				}

				break;
			}
			case 1:
			{
				Menu().SubTab(XS("Player"), 0, Vector2(117, 35)); //468
				Menu().SubTab(XS("Resources"), 1, Vector2(117, 35));
				Menu().SubTab(XS("Lootables"), 2, Vector2(117, 35));
				Menu().SubTab(XS("Other"), 3, Vector2(117, 35));

				switch (activesubtab)
				{
				case 0:
					Menu().BeginChild(XS("Visuals"), { 60,45 }, { 220,290 });
					{

						Menu().CheckBox(XS("Username"), m_settings::nameEsp);
						Menu().CheckBox(XS("Skeleton"), m_settings::Skeleton);
						//Menu().CheckBox(XS("AmmoType"), m_settings::ammoESP);

						Menu().Dropdown(XS("BoxType"), { XS("None"), XS("Box"), XS("CornerBox") }, m_settings::SelectedBoxESP, esp_type_open);
						Menu().Dropdown(XS("HeldItem"), { XS("None"), XS("Text"), XS("Icons"), XS("Both") }, m_settings::HeldItemType, heldi_type_open);
						Menu().Dropdown(XS("HealthBar"), { XS("None"), XS("Bottom"), XS("Left") }, m_settings::SelectedHealthBar, healthbar_tpype_oepn);
						Menu().Dropdown(XS("Inventory"), { XS("None"), XS("Text"), XS("Icons") }, m_settings::SelectedHotbar, hotbar_type_opne);
						Menu().Dropdown(XS("Clothing"), { XS("None"), XS("Text"), XS("Icons") }, m_settings::SelectedClothing, clothing_type_open);
						Menu().Dropdown(XS("BaseCheck"), { XS("None"), XS("Outside"), XS("Inside"), XS("Both") }, m_settings::SelectedOutsideType, inside_Tyope_opem);
						Menu().Dropdown(XS("Vischeck"), { XS("None"), XS("Enabled"), XS("Tags Enabled"), XS("Both") }, m_settings::VisCheckType, vischeck_type_openm);
						Menu().MultiDropdown(XS("Load Chams"), { XS("Lightning"), XS("Geometric"), XS("Galaxy"), XS("WireFrame"), XS("RPBGalaxy") }, m_settings::LoadChams, multi_type_test_open);
						Menu().Dropdown(XS("Chams"), { XS("None"), XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame"), XS("VisColor"), XS("RPBGalaxy"), /*XS("TestChams")*/}, m_settings::SelectedChams, chams_type_opened);

						if (m_settings::SelectedChams == 0)
							m_settings::PlayerChams = false;
						else
							m_settings::PlayerChams = true;

						if (m_settings::VisCheckType == 0) {
							m_settings::EspVisCheck = false;
							m_settings::TagsVisCheck = false;
						}
						else if (m_settings::VisCheckType == 1) {
							m_settings::EspVisCheck = true;
							m_settings::TagsVisCheck = false;
						}
						else if (m_settings::VisCheckType == 2) {
							m_settings::EspVisCheck = false;
							m_settings::TagsVisCheck = true;
						}
						else if (m_settings::VisCheckType == 3) {
							m_settings::EspVisCheck = true;
							m_settings::TagsVisCheck = true;
						}

						
						if (m_settings::LoadChams[0]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadLightning = true;
						}
						if (m_settings::LoadChams[1]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadGeometric = true;
						}
						if (m_settings::LoadChams[2]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadGalaxy = true;
						}
						if (m_settings::LoadChams[3]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadWireFrame = true;
						}
						if (m_settings::LoadChams[4]) {
							static bool HasLoaded = false;
							if (!HasLoaded)
								m_settings::LoadRBP = true;
						}
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Corpse"), m_settings::Corpse);
						Menu().CheckBox(XS("Backpack"), m_settings::BackPack);
						Menu().CheckBox(XS("ShowAlerts"), m_settings::ShowAlerts);
						Menu().CheckBox(XS("Radar"), m_settings::Radar);
						Menu().CheckBoxKeyBind(XS("Save Pos"), m_settings::SavePos, m_settings::SavePosKey);
						Menu().CheckBox(XS("Show Target"), m_settings::DrawTarget);
						Menu().CheckBox(XS("Wounded"), m_settings::DrawWounded);
						Menu().CheckBox(XS("Safezone"), m_settings::DrawSafezone);
						Menu().CheckBox(XS("Npc's"), m_settings::DrawNPC);
						Menu().CheckBox(XS("Sleepers"), m_settings::DrawSleepers);
						//Menu().CheckBox(XS("Disconnected"), m_settings::DrawAis);
						//Menu().CheckBox(XS("ShowCheatsUsers"), m_settings::ShowUsers);

						Menu().Slider(XS("PlayerDistance"), m_settings::PlayerESPDistance, 0, 500);
						Menu().Slider(XS("NPC Distance"), m_settings::NPCDistance, 0, 500);
						Menu().Slider(XS("Drops Distance"), m_settings::MaxPlayerDropsDistance, 0, 500);
						Menu().Slider(XS("RadarSize"), m_settings::RadarSize, 0, 300);
					}
					break;
				case 1:
					Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
					{
						Menu().MultiDropdown(XS("Ores"), { XS("Stone"), XS("Metal"), XS("Sulfur") }, m_settings::OreOptions, multi_ore_options);
						{
							if (m_settings::OreOptions[0])
								m_settings::StoneOre = true;
							else
								m_settings::StoneOre = false;
							if (m_settings::OreOptions[1])
								m_settings::MetalOre = true;
							else
								m_settings::MetalOre = false;
							if (m_settings::OreOptions[2])
								m_settings::SulfurOre = true;
							else
								m_settings::SulfurOre = false;
						}

						Menu().MultiDropdown(XS("Collectables"), { XS("Hemp"), XS("Diesel"), XS("Stone") , XS("Metal") , XS("Sulfur") }, m_settings::CollectableOpions, multi_collectable_options);
						{
							if (m_settings::CollectableOpions[0])
								m_settings::Hemp = true;
							else
								m_settings::Hemp = false;
							if (m_settings::CollectableOpions[1])
								m_settings::DieselBarrel = true;
							else
								m_settings::DieselBarrel = false;

							if (m_settings::CollectableOpions[2])
								m_settings::StoneCollectable = true;
							else
								m_settings::StoneCollectable = false;

							if (m_settings::CollectableOpions[3])
								m_settings::MetalCollectable = true;
							else
								m_settings::MetalCollectable = false;

							if (m_settings::CollectableOpions[4])
								m_settings::SulfurCollectable = true;
							else
								m_settings::SulfurCollectable = false;

						}

						Menu().MultiDropdown(XS("Food"), { XS("Corn"), XS("Pumpkin"), XS("Potato"), XS("Mushroom") }, m_settings::FoodOptions, multi_food_option);
						{
							if (m_settings::FoodOptions[0])
								m_settings::Corn = true;
							else
								m_settings::Corn = false;
							if (m_settings::FoodOptions[1])
								m_settings::Pumpkin = true;
							else
								m_settings::Pumpkin = false;
							if (m_settings::FoodOptions[2])
								m_settings::Potato = true;
							else
								m_settings::Potato = false;
							if (m_settings::FoodOptions[3])
								m_settings::Mushroom = true;
							else
								m_settings::Mushroom = false;
						}
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().Slider(XS("Ore Distance"), m_settings::MaxOreDistance, 0, 500);
						Menu().Slider(XS("Collectables Distance"), m_settings::MaxCollectableDistance, 0, 500);
						Menu().Slider(XS("Food Distance"), m_settings::MaxFoodDistance, 0, 500);
					}
					break;

				case 2:
					Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
					{
						Menu().MultiDropdown(XS("Deployables"), { XS("Stash"), XS("Cupboard"), XS("T1 Workbench"), XS("T2 Workbench") , XS("T3 Workbench") }, m_settings::DeployableOptions, multi_deployable_options);
						{
							if (m_settings::DeployableOptions[0])
								m_settings::Stash = true;
							else
								m_settings::Stash = false;

							if (m_settings::DeployableOptions[1])
								m_settings::cupboard = true;
							else
								m_settings::cupboard = false;

							if (m_settings::DeployableOptions[2])
								m_settings::T1Workbench = true;
							else
								m_settings::T1Workbench = false;

							if (m_settings::DeployableOptions[3])
								m_settings::T2Workbench = true;
							else
								m_settings::T2Workbench = false;

							if (m_settings::DeployableOptions[4])
								m_settings::T3Workbench = true;
							else
								m_settings::T3Workbench = false;

						}
						if (m_settings::cupboard) {
							Menu().MultiDropdown(XS("Cupboard"), { XS("TC Health"), XS("Authed Players"), XS("Upkeep")}, m_settings::CupboardOptions, multi_cupboard_options);
							{
								if (m_settings::CupboardOptions[0])
									m_settings::TC_Health = true;
								else
									m_settings::TC_Health = false;

								if (m_settings::CupboardOptions[1])
									m_settings::AuthorizedPlayers = true;
								else
									m_settings::AuthorizedPlayers = false;

								if (m_settings::CupboardOptions[2])
									m_settings::TC_Upkeep = true;
								else
									m_settings::TC_Upkeep = false;

							}
						}
						Menu().MultiDropdown(XS("Crates"), { XS("Airdrop"), XS("Bradley"), XS("Heli"), XS("Hackable"), XS("Basic"), XS("Normal"), XS("Military"), XS("Elite"), XS("Loot Barrels") }, m_settings::CrateOptions, multi_crate_options);
						{
							if (m_settings::CrateOptions[0])
								m_settings::SupplyDrop = true;
							else
								m_settings::SupplyDrop = false;
							if (m_settings::CrateOptions[1])
								m_settings::BradleyCrate = true;
							else
								m_settings::BradleyCrate = false;
							if (m_settings::CrateOptions[2])
								m_settings::HeliCrate = true;
							else
								m_settings::HeliCrate = false;
							if (m_settings::CrateOptions[3])
								m_settings::HackableCrate = true;
							else
								m_settings::HackableCrate = false;
							if (m_settings::CrateOptions[4])
								m_settings::BasicCrate = true;
							else
								m_settings::BasicCrate = false;
							if (m_settings::CrateOptions[5])
								m_settings::NormalCrate = true;
							else
								m_settings::NormalCrate = false;
							if (m_settings::CrateOptions[6])
								m_settings::MilitaryCrate = true;
							else
								m_settings::MilitaryCrate = false;
							if (m_settings::CrateOptions[7])
								m_settings::EliteCrate = true;
							else
								m_settings::EliteCrate = false;
							if (m_settings::CrateOptions[8])
								m_settings::LootBarrel = true;
							else
								m_settings::LootBarrel = false;

							if (m_settings::HackableCrate)
							{
								m_settings::HackableCrateFlags = true;
								m_settings::HackableCrateTimer = true;
							}
						}

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().Slider(XS("Crates Distance"), m_settings::MaxCrateDistance, 0, 500);
						Menu().Slider(XS("Airdrop Distance"), m_settings::MaxSupplyDropDistance, 0, 500);
					}
					break;

				case 3:
					Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("DroppedItems"), m_settings::DroppedItems);
						if (m_settings::DroppedItems)
							Menu().CheckBox(XS("DroppedItemsChams"), m_settings::DroppedItemsChams);
						Menu().MultiDropdown(XS("Traps"), { XS("Turret"), XS("ShotgunTrap"), XS("FlameTurret"), XS("BearTrap"), XS("SpikesTrap"), XS("LandMine"), XS("SamSite")}, m_settings::TrapsOptions, multi_traps_options);
						{
							if (m_settings::TrapsOptions[0])
								m_settings::AutoTurret = true;
							else
								m_settings::AutoTurret = false;

							if (m_settings::TrapsOptions[1])
								m_settings::ShotgunTrap = true;
							else
								m_settings::ShotgunTrap = false;

							if (m_settings::TrapsOptions[2])
								m_settings::FlameTurret = true;
							else
								m_settings::FlameTurret = false;

							if (m_settings::TrapsOptions[3])
								m_settings::BearTrap = true;
							else
								m_settings::BearTrap = false;

							if (m_settings::TrapsOptions[4])
								m_settings::SpikesTrap = true;
							else
								m_settings::SpikesTrap = false;

							if (m_settings::TrapsOptions[5])
								m_settings::LandMine = true;
							else
								m_settings::LandMine = false;

							if (m_settings::TrapsOptions[6])
								m_settings::SamSite = true;
							else
								m_settings::SamSite = false;
						}
						if (m_settings::AutoTurret)
						{
							Menu().MultiDropdown(XS("Turret Settings"), { XS("Authed Players"), XS("EquippedFlag"), XS("ShowOnline"), XS("Health"), XS("TurningFlags"), XS("Range"), }, m_settings::TurretOptions, multi_turret_options);

							{
								if (m_settings::TurretOptions[0])
									m_settings::TurretAuthorizedPlayers = true;
								else
									m_settings::TurretAuthorizedPlayers = false;

								if (m_settings::TurretOptions[1])
									m_settings::TurretEquippedFlags = true;
								else
									m_settings::TurretEquippedFlags = false;

								if (m_settings::TurretOptions[2])
									m_settings::TurretOnFlags = true;
								else
									m_settings::TurretOnFlags = false;

								if (m_settings::TurretOptions[3])
									m_settings::TurretHealth = true;
								else
									m_settings::TurretHealth = false;

								if (m_settings::TurretOptions[4])
									m_settings::TurretTurningFlag = true;
								else
									m_settings::TurretTurningFlag = false;

								if (m_settings::TurretOptions[5])
									m_settings::TurretRange = true;
								else
									m_settings::TurretRange = false;

							}
						}

						Menu().MultiDropdown(XS("Vehicles"), { XS("PatrolHeli"), XS("Bradley"), XS("MiniCopter"), XS("ScrapHeli"), XS("AttackHeli"), XS("TugBoat"), XS("RHIB"), XS("RowBoat") }, m_settings::VehicleOptions, multi_vehicle_options);
						{
							if (m_settings::VehicleOptions[0])
								m_settings::PatrolHelicopter = true;
							else
								m_settings::PatrolHelicopter = false;

							if (m_settings::VehicleOptions[1])
								m_settings::BradleyAPC = true;
							else
								m_settings::BradleyAPC = false;

							if (m_settings::VehicleOptions[2])
								m_settings::Minicopter = true;
							else
								m_settings::Minicopter = false;

							if (m_settings::VehicleOptions[3])
								m_settings::ScrapHeli = true;
							else
								m_settings::ScrapHeli = false;

							if (m_settings::VehicleOptions[4])
								m_settings::AttackHeli = true;
							else
								m_settings::AttackHeli = false;

							if (m_settings::VehicleOptions[5])
								m_settings::TugBoat = true;
							else
								m_settings::TugBoat = false;

							if (m_settings::VehicleOptions[6])
								m_settings::Rhib = true;
							else
								m_settings::Rhib = false;

							if (m_settings::VehicleOptions[7])
								m_settings::Rowboat = true;
							else
								m_settings::Rowboat = false;
						}


						//Menu().MultiDropdown(XS("Raid ESP"), { XS("Enable"), XS("C4"), XS("Rockets"), XS("Satchels"), XS("ExploAmmo") }, m_settings::RaidOptions, multi_raid_options);
						{
							if (m_settings::RaidOptions[0])
								m_settings::RaidESP = true;
							else
								m_settings::RaidESP = false;

							if (m_settings::RaidOptions[1])
								m_settings::ShowC4 = true;
							else
								m_settings::ShowC4 = false;

							if (m_settings::RaidOptions[2])
								m_settings::ShowRocket = true;
							else
								m_settings::ShowRocket = false;

							if (m_settings::RaidOptions[3])
								m_settings::ShowSatchel = true;
							else
								m_settings::ShowSatchel = false;

							if (m_settings::RaidOptions[4])
								m_settings::ShowExplosiveAmmo = true;
							else
								m_settings::ShowExplosiveAmmo = false;
						}
					

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().Slider(XS("Dropped Distance"), m_settings::MaxDroppedDistance, 0, 500);
						Menu().Slider(XS("Traps Distance"), m_settings::MaxTrapsDistance, 0, 500);
						Menu().Slider(XS("APC Distance"), m_settings::MaxAPCDistance, 0, 3000);
						Menu().Slider(XS("Vehicle Distance"), m_settings::MaxVehicleDistance, 0, 500);

						Menu().Slider(XS("Raid Distance"), m_settings::MaxExplosionDistance, 0, 5000);
						Menu().Slider(XS("AuthDistance"), m_settings::AuthorizedPlayersDistance, 0, 300);
						Menu().Slider(XS("Raid Timer"), m_settings::MaxRaidTimer, 0, 300);

					}
					break;
				}

				break;
			}
			case 2:
			{
				Menu().SubTab(XS("LocalPlayer"), 0, Vector2(156, 35)); //468
				Menu().SubTab(XS("Other"), 1, Vector2(156, 35));
				Menu().SubTab(XS("Weather"), 2, Vector2(156, 35));
				//Menu().SubTab(XS(L"World"), 3, Vector2(117, 35));

				switch (activesubtab)
				{
				case 0:
					Menu().BeginChild(XS("LocalPlayer"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Flyhack Indicator"), m_settings::Flyhack_Indicator);
						Menu().CheckBox(XS("Anti FlyhackKick"), m_settings::AntiFlyKick);
						Menu().CheckBox(XS("Anti DeathBarrier"), m_settings::AntiDeathBarrier);
						Menu().CheckBox(XS("Spiderman"), m_settings::SpiderMan);
						Menu().CheckBox(XS("SmallerLocalRadius"), m_settings::SmallerLocalRadius);
						Menu().CheckBox(XS("Admin Flags"), m_settings::AdminFlags);
						Menu().CheckBox(XS("Infinite Jump"), m_settings::InfiniteJump);
						Menu().CheckBox(XS("Omnisprint"), m_settings::OmniSprint);
						Menu().CheckBox(XS("ToggleSprint"), m_settings::AlwaysSprint);
						Menu().CheckBox(XS("NoMovementReduction"), m_settings::NoMovementRestrictions);
						Menu().CheckBox(XS("NoCollision (Trees)"), m_settings::IgnoreTrees);
						Menu().CheckBox(XS("NoCollision (Players)"), m_settings::IgnorePlayers);
						//Menu().CheckBox(XS("FloorHugger"), m_settings::FloorHugger);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("NameSpoofer"), m_settings::NameSpoofer);
						Menu().CheckBox(XS("FixDebugCamera"), m_settings::FixDebugCamera);
						Menu().CheckBox(XS("Instant Loot"), m_settings::InstantLoot);
						Menu().CheckBox(XS("Instant Heal"), m_settings::InstantHeal);
						Menu().CheckBox(XS("Adjust NoClipSpeed"), m_settings::AdjustNoClipSpeed);
						Menu().CheckBoxKeyBind(XS("NoClip"), m_settings::AdminCheat, m_settings::AdminCheatKey);
						//Menu().CheckBoxKeyBind(XS("Teleport"), m_settings::Teleport, m_settings::TeleportKey);
						Menu().CheckBoxKeyBind(XS("InstantRevive"), m_settings::InstantRevive, m_settings::InstantReviveKey);
						if (m_settings::InstantRevive)
							m_settings::TargetWounded = true;
						Menu().CheckBoxKeyBind(XS("Keep TargetAlive"), m_settings::KeepTargetAlive, m_settings::KeepAliveKey);
						Menu().CheckBoxKeyBind(XS("Loot Body"), m_settings::LootBodyThruWall, m_settings::LootBodyThruWallKey);
						Menu().CheckBoxKeyBind(XS("Loot Corpse"), m_settings::LootCorpseThruWall, m_settings::LootCorpseThruWallKey);
						Menu().CheckBoxKeyBind(XS("Interactive Debug"), m_settings::InteractiveDebug, m_settings::InteractiveKey);
						Menu().CheckBoxKeyBind(XS("SilentWalk"), m_settings::SilentWalk, m_settings::SilentWalkKey);
						Menu().CheckBoxKeyBind(XS("TeleportMaxHeight"), m_settings::TeleportMax, m_settings::TeleportMaxKey);
					}
					break;
				case 1:
					Menu().BeginChild(XS("Misc"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBoxKeyBind(XS("Zoom"), m_settings::Zoom, m_settings::ZoomKey);
						if (m_settings::Zoom) {
							Menu().Slider(XS("Zoom Amount"), m_settings::ZoomAmount, 0, 50);
						}
						
						Menu().CheckBox(XS("PlayerFov"), m_settings::PlayerFov);
						if (m_settings::PlayerFov) {
							Menu().Slider(XS("PlayerFov Amount"), m_settings::PlayerFovAmount, 0, 140);
						}
						
						Menu().CheckBox(XS("AutoFarmTree"), m_settings::AutoFarmTree);
						Menu().CheckBox(XS("AutoFarmOre"), m_settings::AutoFarmOre);
						Menu().CheckBox(XS("AutoUpgrade"), m_settings::AutoUpgrade);
						if (m_settings::AutoUpgrade)
						{
							Menu().Dropdown(XS("BuildingGrade"), { XS("Wood"), XS("Stone"), XS("Metal"), XS("HQM") }, m_settings::BuildingGrade, upgrade_open);
						}
						Menu().CheckBox(XS("DoorSpammer"), m_settings::DoorSpammer);

						Menu().CheckBox(XS("GestureSpam"), m_settings::GestureSpam);
						if (m_settings::GestureSpam) {
							Menu().Dropdown(XS("GestureSpam"), { XS("None"), XS("Clap"), XS("Friendly"), XS("ThumbsDown"),XS("ThumbsUp"), XS("Ok"), XS("Point"), XS("Shrug"), XS("Victory"), XS("Wave") }, m_settings::gesture, gesutre_open);
						}
						//Menu().CheckBox(XS("AutoMini"), m_settings::AutoMini);
						//Menu().CheckBox(XS("HoverMini"), m_settings::HoverMini);
						//Menu().Slider(XS("HoverHeight"), m_settings::HoverHeight, 0, 500);

					}

					Menu().BeginChild(XS("Prefab Spawner"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("LoadAmongus"), m_settings::LoadAmongusAsset);
						if (m_settings::LoadAmongusAsset) {
							Menu().CheckBoxKeyBind(XS("AmongusPrefab"), m_settings::AmongusPrefabSpawn, m_settings::AmongusKey);
						}
						Menu().CheckBox(XS("LoadHerbert"), m_settings::LoadHerbertAsset);
						if (m_settings::LoadHerbertAsset) {
							Menu().CheckBoxKeyBind(XS("HerbertPrefab"), m_settings::HerbertPrefabSpawn, m_settings::HerbertKey);
						}
					}
					break;

				case 2:
					Menu().BeginChild(XS("Prefab Spawner"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("BrightNight"), m_settings::Brightnight);
						Menu().CheckBox(XS("BrightAmbient"), m_settings::BrightAmbient);
						Menu().CheckBox(XS("Stars"), m_settings::Stars);
						Menu().CheckBox(XS("SkyColor (Day)"), m_settings::SkyColorDay);
						Menu().CheckBox(XS("SkyColor (Night)"), m_settings::SkyColorNight);
						Menu().CheckBox(XS("SharpClouds"), m_settings::SharpClouds);
						Menu().CheckBox(XS("BrightCave"), m_settings::BrightCave);
						//Menu().CheckBox(XS("CustomSky"), m_settings::CustomSky);					

						Menu().CheckBox(XS("TimeChanger"), m_settings::TimeChanger);
						if (m_settings::TimeChanger) {
							Menu().Slider(XS("GameTime: "), m_settings::GameTime, 0, 24);
						}


						//Menu().CheckBox(XS("RemoveUnderwaterEffects"), m_settings::RemoveUnderwaterEffects);
					}

					Menu().BeginChild(XS("Settings"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Enable Weather"), m_settings::Weather);
						Menu().CheckBox(XS("Atmosphere"), m_settings::AtmosphereContrast);
						Menu().CheckBox(XS("Rainbows"), m_settings::Rainbows);
						Menu().CheckBox(XS("Waves"), m_settings::Waves);
						Menu().CheckBox(XS("NoClouds"), m_settings::NoClouds);
						//Menu().CheckBox(XS("NoAtmosphere"), m_settings::NoAtmosphere);
						Menu().CheckBox(XS("NoSun"), m_settings::NoSun);
						Menu().CheckBox(XS("NoFog"), m_settings::NoFog);
						Menu().CheckBox(XS("NoRain"), m_settings::NoRain);
						Menu().CheckBox(XS("NoThunder"), m_settings::NoThunder);
						Menu().CheckBox(XS("NoWind"), m_settings::NoWind);
						Menu().CheckBox(XS("RainbowSky"), m_settings::RainbowSky);
						if (m_settings::RainbowSky) {
							Menu().Slider(XS("SkyValue: "), m_settings::RainbowAmount, 0, 100);
						}
					}
					/*	Menu().BeginChild(XS("Friend List"), { 60,45 }, { 220,290 });
						{
							for (const auto& wideKey : wideKeys) {
								Menu().Text(wideKey.c_str());
							}
						}

						Menu().BeginChild(XS("Settings"), { 285,45 }, { 220,290 });
						{
							Menu().CheckBoxKeyBind(XS("Add Friends"), m_settings::removefriend1, m_settings::AddFriend);
							Menu().CheckBoxKeyBind(XS("Remove Friend"), m_settings::removefriend2, m_settings::RemoveFriend);
							Menu().CheckBoxKeyBind(XS("Remove All"), m_settings::removefriend3, m_settings::RemoveAllFriends);
						}*/
					break;
				}

				break;
			}
			case 3:
			{
				Menu().SubTab(XS("Weapon"), 0, Vector2(156, 35)); //468
				switch (activesubtab)
				{
				case 0:
					Menu().BeginChild(XS("Weapon"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("No Attack Restrictions"), m_settings::NoAttackRestrictions);
						Menu().CheckBox(XS("Recoil Modifier"), m_settings::ChangeRecoil);
						if (m_settings::ChangeRecoil) {
							Menu().Slider(XS("Recoil Percent"), m_settings::recoilPercent, 0, 100);
							//	Menu().Slider(XS("Recoil Percent Y"), m_settings::RecoilPercentY, 0, 100);
						}

						Menu().CheckBox(XS("Thickness Modifier"), m_settings::NormalThickBullet);
						if (m_settings::NormalThickBullet) {
							Menu().Slider(XS("Bullet Thickness"), m_settings::NormalThickBulletThickness, 0, 4.5);
						}
						Menu().CheckBox(XS("Fast Bullet"), m_settings::NormalFastBullet);
						Menu().CheckBox(XS("Force Automatic"), m_settings::ForceAutomatic);
						
						Menu().CheckBox(XS("NoWeaponBob"), m_settings::NoWeaponBob);
						Menu().CheckBox(XS("NoSway"), m_settings::NoSway);
						Menu().CheckBox(XS("InstantEoka"), m_settings::InstantEoka);
						Menu().CheckBox(XS("RemoveAttackAnimations"), m_settings::RemoveAttackAnimations);

						Menu().CheckBox(XS("DisableHitSounds"), m_settings::DisableHitSounds);
						Menu().CheckBox(XS("CustomHitSounds"), m_settings::CustomHitSounds);

						Menu().CheckBox(XS("Long Melee"), m_settings::LongMelee);
						Menu().Slider(XS("Spread Percent"), m_settings::SilentSpread, 0, 100);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Spinbot"), m_settings::Spinbot);
						Menu().CheckBoxKeyBind(XS("WeaponSpammer"), m_settings::WeaponSpammer, m_settings::WeaponSpamKey);
						if (m_settings::WeaponSpammer) {
							Menu().Slider(XS("WeaponSpammerDelay"), m_settings::WeaponSpamDelay, 0, 20);
						}

						Menu().CheckBox(XS("KillEffects"), m_settings::KillEffects);
						if (m_settings::KillEffects) {
							Menu().Dropdown(XS("Effect Type"), { XS("Explosion"), XS("Ghosts") }, m_settings::SelectedKillEffect, killeffect_type_open);
							Menu().MultiDropdown(XS("Load Effects"), { XS("Explosion"), XS("Ghosts") }, m_settings::LoadHitEffects, multi_effect_load);

							if (m_settings::LoadHitEffects[0]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadExplosionEffect = true;
							}
							if (m_settings::LoadHitEffects[1]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadGhostEffect = true;
							}
						}


						Menu().CheckBox(XS("WeaponChams"), m_settings::WeaponChams);
						if (m_settings::WeaponChams) {
							Menu().CheckBox(XS("IgnoreArms"), m_settings::IgnoreArms);

							Menu().Dropdown(XS("Chams Type"), { XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame"), XS("RPBGalaxy"), /*XS("TestChams")*/}, m_settings::WeaponSelectedChams, wchams_type_opens);
							Menu().MultiDropdown(XS("Load Chams"), { XS("Lightning"), XS("Geometric"), XS("Galaxy"), XS("WireFrame"), XS("RPBGalaxy")}, m_settings::LoadChams, multi_chams_load);

							if (m_settings::LoadChams[0]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadLightning = true;
							}
							if (m_settings::LoadChams[1]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadGeometric = true;
							}
							if (m_settings::LoadChams[2]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadGalaxy = true;
							}
							if (m_settings::LoadChams[3]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadWireFrame = true;
							}
							if (m_settings::LoadChams[4]) {
								static bool HasLoaded = false;
								if (!HasLoaded)
									m_settings::LoadRBP = true;
							}

							//Menu().CheckBox(XS("Grenade Prediction"), m_settings::GrenadePrediction);
						}
						//Menu().CheckBox(XS("Rocket Prediction"), m_settings::RocketPrediction);

					}
					break;
				}
				break;
			}
			case 4:
			{
				Menu().SubTab(XS("Settings"), 0, Vector2(156, 35)); //468

				switch (activesubtab)
				{
				case 0:
					Menu().BeginChild(XS("Colors"), { 60,45 }, { 220,290 });
					{
						Menu().Button(XS("Reset PlayerModels"), reset_player_model);
						Menu().Button(XS("Reset LOS Points"), Buttons::ClearLOSPoints);
						Menu().Button(XS("Clear RaidCache"), Buttons::ClearRaidCache);
						Menu().Button(XS("Load LegitCheat"), Buttons::LoadLegitCheat);

						Menu().Spacer(30);
						Menu().Button(XS("Save Config"), Configs::SaveConfig);
						Menu().Button(XS("Load Config"), Configs::LoadConfig);
						Menu().Spacer(15);

						Menu().Dropdown(XS("Config Type"), { XS("Legit"), XS("Rage"), XS("Config1"), XS("Config2"), XS("Config3") }, m_settings::SelectedConfig, config_type_open);
					}

					Menu().BeginChild(XS("Configs"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("OutlinedText"), m_settings::OutlinedText);
						if (m_settings::OutlinedText)
							m_settings::ShadedText = false;
						Menu().CheckBox(XS("ShadowedText"), m_settings::ShadedText);
						if (m_settings::ShadedText)
							m_settings::OutlinedText = false;
						Menu().CheckBox(XS("WorldOutlinedText"), m_settings::WorldOutlinedText);
						if (m_settings::WorldOutlinedText)
							m_settings::WorldShadedText = false;
						Menu().CheckBox(XS("WorldShadedText"), m_settings::WorldShadedText);
						if (m_settings::WorldShadedText)
							m_settings::WorldOutlinedText = false;
						Menu().Slider(XS("EspFontSize"), m_settings::ESPFontsize, 0, 15);
						Menu().Slider(XS("WorldFontSize"), m_settings::WorldFontSize, 0, 15);
						Menu().CheckBox(XS("FontChanger"), m_settings::FontChanger);
						if (m_settings::FontChanger) {
							Menu().Dropdown(XS("Font"), { XS("Default"), XS("Pixel"), XS("Verdana"), }, m_settings::fonttype, font_open);
						}

					}
					break;
				}
				break;
			}
		}
	}

	Menu().end_window();
}