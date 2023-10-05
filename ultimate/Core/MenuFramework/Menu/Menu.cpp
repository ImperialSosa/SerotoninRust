#include "Menu.hpp"
#include "../../Includes/settings.hpp"
inline bool aim_type_opened;
inline bool chams_type_opened;
inline bool bullet_tpe_open;
inline bool config_type_open;
inline bool hitmat_open;
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
						//Menu().CheckBox(XS("Memory Aimbot"), m_settings::MemoryAimbot);
						Menu().CheckBox(XS("Silent Aimbot"), m_settings::SilentAim);
						Menu().CheckBox(XS("Velocity Aimbot"), m_settings::VelocityAimbot);
						//Menu().CheckBox(XS("Rotation Aimbot"), m_settings::RotationAimbot);
						if (m_settings::SilentAim)
						{
							m_settings::RotationAimbot = false;
						}

						if (m_settings::VelocityAimbot)
						{
							m_settings::RotationAimbot = false;
						}

						Menu().CheckBox(XS("Melee Aimbot"), m_settings::MeleeAimbot);
						Menu().CheckBoxKeyBind(XS("Rotation Aimbot"), m_settings::RotationAimbot, m_settings::RotationKey);
						if (m_settings::RotationAimbot)
						{
							m_settings::SilentAim = false;
							m_settings::VelocityAimbot = false;
							m_settings::Manipulation = false;
							m_settings::BulletTP = false;
							m_settings::InstantBullet = false;
							m_settings::InstantKill = false;

						}
						//Menu().CheckBox(XS(L"Heli Aimbot"), m_settings::HeliAimbot);
						Menu().CheckBox(XS("Silent Melee"), m_settings::SilentMelee);
						////if (m_settings::HeliAimbot)
						//{
						//	Menu().CheckBox(XS(L"Heli Override"), m_settings::HeliHitboxOverride);
						//}
						Menu().Slider(XS("Accuracy"), m_settings::AimbotAccuracy, 0, 100);
						Menu().Slider(XS("Fov Slider"), m_settings::AimbotFOV, 0, 1000);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{

						Menu().CheckBox(XS("Target NPC"), m_settings::AimbotNPC);
						Menu().CheckBox(XS("Target Wounded"), m_settings::TargetWounded);
						//Menu().CheckBox(XS(L"Target FriendList"), m_settings::TargetFriendList);

						Menu().Dropdown(XS("Aimbone"), { XS("Head"), XS("Neck"), XS("Chest"), XS("Random"), XS("Closest To Crosshair") }, m_settings::SelectedAimbone, aim_type_opened);

						//Menu().Spacer(50);

						Menu().Dropdown(XS("HitMaterial"), { XS("Flesh"), XS("Glass"), XS("Metal"), XS("Water") }, m_settings::HitMaterial, hitmat_open);
				
					}
					break;
				case 1:
					Menu().BeginChild(XS("Exploits"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBoxKeyBind(XS("AutoShoot"), m_settings::Autoshoot, m_settings::AutoshootKey);

						if (m_settings::Autoshoot)
						{
							Menu().CheckBox(XS("AlwaysAutoshoot"), m_settings::AlwaysAutoshoot);
						}
						Menu().CheckBoxKeyBind(XS("Manipulation"), m_settings::Manipulation, m_settings::ManipKey);

						Menu().CheckBox(XS("BulletTp"), m_settings::BulletTP);
						if (m_settings::BulletTP) {
							Menu().CheckBox(XS("Cache LOS (Saves FPS)"), m_settings::CacheBulletTP);
							if (m_settings::CacheBulletTP)
							{
								Menu().CheckBox(XS("AdvancedCaching (Saves FPS)"), m_settings::AdvancedChecks);
							}
						}
						Menu().CheckBox(XS("AutoStop"), m_settings::StopPlayer);

						Menu().CheckBox(XS("PierceMaterials"), m_settings::PierceMaterials);
						Menu().CheckBox(XS("Bullet Queue"), m_settings::InstantKill);
						if (m_settings::InstantKill)
						{
							Menu().CheckBox(XS("WaitForBulletTP"), m_settings::WaitForBulletTP);
						}

						Menu().CheckBox(XS("Instant Hit"), m_settings::InstantBullet);
						Menu().CheckBox(XS("WaitForInstantHit"), m_settings::WaitForInstantHit);
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Auto Reload"), m_settings::AutoReload);

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
						//	m_settings::AdvancedChecks = true;
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

						Menu().CheckBox(XS("SwastikaCrosshair"), m_settings::Swastika);
						if (m_settings::Swastika)
						{
							m_settings::Crosshair = false;
							Menu().Slider(XS("SwastikaSize"), m_settings::SwastikaSize, 1, 20);
						}
						Menu().CheckBox(XS("FOV Circle"), m_settings::DrawFov);
						Menu().CheckBox(XS("Target Snapline"), m_settings::Aimline);
						Menu().CheckBox(XS("Target Marker"), m_settings::AimMarker);
						Menu().CheckBox(XS("Target Indicator"), m_settings::Target_Indicator);
						Menu().CheckBox(XS("Bullet Tracers"), m_settings::BulletTracers);

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

						//Menu().CheckBox(XS("SnickerBullet"), m_settings::SnickerBullet);
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
						Menu().Dropdown(XS("Chams"), { XS("None"), XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame"), XS("Color")}, m_settings::SelectedChams, chams_type_opened);
						Menu().MultiDropdown(XS("Load Chams"), { XS("Lightning"), XS("Geometric"), XS("Galaxy"), XS("WireFrame") }, m_settings::LoadChams, multi_type_test_open);

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
						//Menu().CheckBox(XS(L"OOFOV"), m_settings::OOFIndicators);
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
					}
					break;
				case 1:
					Menu().BeginChild(XS("World"), { 60,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("StoneOre"), m_settings::StoneOre);
						Menu().CheckBox(XS("MetalOre"), m_settings::MetalOre);
						Menu().CheckBox(XS("SulfurOre"), m_settings::SulfurOre);
						//	Menu().CheckBox(XS("Ore Icon"), m_settings::OreIcons);

						Menu().CheckBox(XS("Hemp"), m_settings::Hemp);
						Menu().CheckBox(XS("Diesel"), m_settings::DieselBarrel);
						//	Menu().CheckBox(XS("Collectables Icon"), m_settings::CollectablesIcon);

						Menu().CheckBox(XS("Corn"), m_settings::Corn);
						Menu().CheckBox(XS("Pumpkin"), m_settings::Pumpkin);
						Menu().CheckBox(XS("Potato"), m_settings::Potato);
						Menu().CheckBox(XS("Mushroom"), m_settings::Mushroom);
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
						Menu().CheckBox(XS("Stash"), m_settings::Stash);
						Menu().CheckBox(XS("HackableCrate"), m_settings::HackableCrate);
						if (m_settings::HackableCrate)
						{
							Menu().CheckBox(XS("HackableCrateFlags"), m_settings::HackableCrateFlags);
							Menu().CheckBox(XS("HackableCrateTimer"), m_settings::HackableCrateTimer);
						}
						Menu().CheckBox(XS("Bradley Crate"), m_settings::BradleyCrate);
						Menu().CheckBox(XS("Heli Crate"), m_settings::HeliCrate);
						Menu().CheckBox(XS("Basic Crate"), m_settings::BasicCrate);
						Menu().CheckBox(XS("Normal Crate"), m_settings::NormalCrate);
						Menu().CheckBox(XS("Military Crate"), m_settings::MilitaryCrate);
						Menu().CheckBox(XS("Elite Crate"), m_settings::EliteCrate);
						Menu().CheckBox(XS("Airdrop"), m_settings::SupplyDrop);
<<<<<<< HEAD
						Menu().CheckBox(XS("Loot Barrels"), m_settings::LootBarrel);
=======
						//Menu().CheckBox(XS("Loot Barrels"), m_settings::LootBarrel);
>>>>>>> 106ea80c5224b90737646fe9eb32489d6a7596fe

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
						Menu().CheckBox(XS("Turret"), m_settings::AutoTurret);
						if (m_settings::AutoTurret)
						{
							Menu().CheckBox(XS("Authorized Players"), m_settings::TurretAuthorizedPlayers);
							Menu().CheckBox(XS("EquippedFlag"), m_settings::TurretEquippedFlags);
							Menu().CheckBox(XS("TurretOnFlags"), m_settings::TurretOnFlags);
							Menu().CheckBox(XS("Turret Health"), m_settings::TurretHealth);
							Menu().CheckBox(XS("TurningFlag"), m_settings::TurretTurningFlag);
							Menu().CheckBox(XS("TurretRange"), m_settings::TurretRange);
						}
						Menu().CheckBox(XS("Patrol Helicopter"), m_settings::PatrolHelicopter);
						Menu().CheckBox(XS("Bradley"), m_settings::BradleyAPC);
						Menu().CheckBox(XS("TugBoat"), m_settings::ThugBoat);
						Menu().CheckBox(XS("Raid ESP"), m_settings::RaidESP);
						if (m_settings::RaidESP)
						{
							Menu().CheckBox(XS("Show Rocket"), m_settings::ShowRocket);
							Menu().CheckBox(XS("Show C4"), m_settings::ShowC4);
							Menu().CheckBox(XS("Show Satchel"), m_settings::ShowSatchel);
							Menu().CheckBox(XS("Show ExploAmmo"), m_settings::ShowExplosiveAmmo);
						}

						Menu().CheckBox(XS("Cupboard"), m_settings::cupboard);
						if (m_settings::cupboard)
						{
							Menu().CheckBox(XS("TC Health"), m_settings::TC_Health);
							Menu().CheckBox(XS("AuthorizedPlayers"), m_settings::AuthorizedPlayers);
							

						}
						Menu().CheckBox(XS("TugBoat"), m_settings::ThugBoat);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().Slider(XS("Dropped Distance"), m_settings::MaxDroppedDistance, 0, 500);
						Menu().Slider(XS("Traps Distance"), m_settings::MaxTrapsDistance, 0, 500);
						Menu().Slider(XS("APC Distance"), m_settings::MaxAPCDistance, 0, 3000);

						Menu().Slider(XS("Raid Distance"), m_settings::MaxExplosionDistance, 0, 5000);
						Menu().Slider(XS("AuthDistance"), m_settings::AuthorizedPlayersDistance, 0, 300);
						Menu().Slider(XS("Raid Timer"), m_settings::MaxRaidTimer, 0, 300);
						Menu().CheckBox(XS("Bradley"), m_settings::BradleyAPC);

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
						Menu().CheckBox(XS("NoCollision (Trees)"), m_settings::IgnoreTrees);
						Menu().CheckBox(XS("NoCollision (Players)"), m_settings::IgnorePlayers);
						Menu().CheckBox(XS("FloorHugger"), m_settings::FloorHugger);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("NameSpoofer"), m_settings::NameSpoofer);
						Menu().CheckBox(XS("Instant Loot"), m_settings::InstantLoot);
						Menu().CheckBox(XS("Instant Heal"), m_settings::InstantHeal);
						Menu().CheckBox(XS("Adjust NoClipSpeed"), m_settings::AdjustNoClipSpeed);
						Menu().CheckBoxKeyBind(XS("NoClip"), m_settings::AdminCheat, m_settings::AdminCheatKey);
						Menu().CheckBoxKeyBind(XS("InstantRevive"), m_settings::InstantRevive, m_settings::InstantReviveKey);
						Menu().CheckBoxKeyBind(XS("Keep TargetAlive"), m_settings::KeepTargetAlive, m_settings::KeepAliveKey);
						Menu().CheckBoxKeyBind(XS("Loot Body"), m_settings::LootBodyThruWall, m_settings::LootBodyThruWallKey);
						Menu().CheckBoxKeyBind(XS("Loot Corpse"), m_settings::LootCorpseThruWall, m_settings::LootCorpseThruWallKey);
						Menu().CheckBox(XS("Spinbot"), m_settings::Spinbot);
						Menu().CheckBox(XS("FixDebugCamera"), m_settings::FixDebugCamera);
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
						Menu().CheckBox(XS("NoSpread"), m_settings::ChangeSpread);
						if (m_settings::ChangeSpread)
							Menu().Slider(XS("Spread Percent"), m_settings::SilentSpread, 0, 100);
						Menu().CheckBox(XS("NoWeaponBob"), m_settings::NoWeaponBob);
						Menu().CheckBox(XS("NoSway"), m_settings::NoSway);
						Menu().CheckBox(XS("InstantEoka"), m_settings::InstantEoka);
						Menu().CheckBox(XS("RemoveAttackAnimations"), m_settings::RemoveAttackAnimations);
<<<<<<< HEAD
						Menu().CheckBox(XS("Long Melee"), m_settings::LongMelee);

=======
						Menu().CheckBox(XS("DisableHitSounds"), m_settings::DisableHitSounds);
						Menu().CheckBox(XS("CustomHitSounds"), m_settings::CustomHitSounds);

						Menu().CheckBox(XS("Long Melee"), m_settings::LongMelee);
>>>>>>> 106ea80c5224b90737646fe9eb32489d6a7596fe
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
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
						Menu().Button(XS("Reset LOS Points"), Buttons::ClearRaidCache);
						Menu().Button(XS("Clear RaidCache"), Buttons::ClearLOSPoints);
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

						Menu().Button(XS("Save Config"), Configs::SaveConfig);
						Menu().Button(XS("Load Config"), Configs::LoadConfig);
						Menu().Spacer(30);

						Menu().Dropdown(XS("Config Type"), { XS("Legit"), XS("Rage"), XS("Config1"), XS("Config2"), XS("Config3") }, m_settings::SelectedConfig, config_type_open);
					}
					break;
				}
				break;
			}
		}
	}

	Menu().end_window();
}