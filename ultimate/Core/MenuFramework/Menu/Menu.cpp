#include "Menu.hpp"
#include "../../Includes/settings.hpp"
inline bool aim_type_opened;
inline bool chams_type_opened;
inline bool bullet_tpe_open;
inline bool config_type_open;
inline bool hitmat_open;
inline bool wchams_type_opens;
inline bool killeffect_type_open;
inline bool manip_type_openm;
inline bool aim_type_opene2;
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
						Menu().CheckBoxKeyBind(XS("Legit Aimbot"), m_settings::RotationAimbot, m_settings::RotationKey);
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
						//Menu().CheckBox(XS(L"Silent Melee"), m_settings::SilentMelee);
						////if (m_settings::HeliAimbot)
						//{
						//	Menu().CheckBox(XS(L"Heli Override"), m_settings::HeliHitboxOverride);
						//}
						Menu().Slider(XS("Accuracy"), m_settings::AimbotAccuracy, 0, 100);
						Menu().Slider(XS("Fov Slider"), m_settings::AimbotFOV, 0, 1000);
						Menu().Dropdown(XS("Aimbone"), { XS("Head"), XS("Neck"), XS("Chest"), XS("Random"), XS("Closest To Crosshair") }, m_settings::SelectedAimbone, aim_type_opened);
						
						//Menu().Spacer(50);

						Menu().Dropdown(XS("HitMaterial"), { XS("Flesh"), XS("Glass"), XS("Metal"), XS("Water")}, m_settings::HitMaterial, hitmat_open);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{

						Menu().CheckBox(XS("Target NPC"), m_settings::AimbotNPC);
						Menu().CheckBox(XS("Target Wounded"), m_settings::TargetWounded);
						//Menu().CheckBox(XS(L"Target FriendList"), m_settings::TargetFriendList);

						Menu().Slider(XS("Spread Percent"), m_settings::SilentSpread, 0, 100);
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
						Menu().CheckBox(XS("AutoStop"), m_settings::StopPlayer);

						Menu().CheckBox(XS("PierceMaterials"), m_settings::PierceMaterials);
						Menu().CheckBox(XS("Bullet Queue"), m_settings::InstantKill);
						if (m_settings::InstantKill)
						{
							Menu().CheckBox(XS("WaitForBulletTP"), m_settings::WaitForBulletTP);
						}

						Menu().CheckBox(XS("Instant Hit"), m_settings::InstantBullet);
						Menu().CheckBox(XS("WaitForInstantHit"), m_settings::WaitForInstantHit);

						Menu().CheckBox(XS("Silent Melee"), m_settings::SilentMelee);

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
							Menu().Dropdown(XS("Manip Mode"), { XS("Static Points"), XS("Dynamic Points"), XS("Enhanced Points") }, m_settings::ManipMode, manip_type_openm);

						if (m_settings::BulletTP)
							Menu().Dropdown(XS("BTP Mode"), { XS("Lowest"), XS("Low"), XS("Medium"), XS("High"), XS("Intense (FPS)"), XS("Enhanced")}, m_settings::BulletTPIntensity, bullet_tpe_open);

						if (m_settings::Manipulation)
						{
							Menu().Slider(XS("ManipAngles"), m_settings::ManipPoints, 5, 100);
							//m_settings::ManipPoints
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
						//Simulate Projectile
						Menu().CheckBox(XS("Manipulation Indicator"), m_settings::ManipFlags);
						Menu().CheckBox(XS("BulletTP Indicator"), m_settings::BulletTPFlags);
						Menu().CheckBox(XS("BulletTP Arrows"), m_settings::Thickbullet_Arrows);
						Menu().CheckBox(XS("BulletTP Angle"), m_settings::ShowBulletTPAngle);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						//				//Menu().Button(XS("dees nuts"), &test);
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
						Menu().CheckBox(XS("Box"), m_settings::BoxEsp);
						if (m_settings::BoxEsp)
							m_settings::CornerBox = false;
						Menu().CheckBox(XS("CornerBox"), m_settings::CornerBox);
						if (m_settings::CornerBox)
							m_settings::BoxEsp = false;
						Menu().CheckBox(XS("Skeleton"), m_settings::Skeleton);
						Menu().CheckBox(XS("Healthbar"), m_settings::healthBar);
						Menu().CheckBox(XS("Helditem"), m_settings::helditem);
						Menu().CheckBox(XS("HeldItem (icons)"), m_settings::HeldItemIcon);
						//Menu().CheckBox(XS("AmmoType"), m_settings::ammoESP);
						Menu().CheckBox(XS("isOutside"), m_settings::BaseCheck);
						Menu().CheckBox(XS("Inventory"), m_settings::DrawInventory);
						if (m_settings::DrawInventory)
							m_settings::DrawInventoryIcons = false;
						Menu().CheckBox(XS("Inventory (icons)"), m_settings::DrawInventoryIcons);
						if (m_settings::DrawInventoryIcons)
							m_settings::DrawInventory = false;
						Menu().CheckBox(XS("Clothing"), m_settings::DrawClothing);
						if (m_settings::DrawClothing)
							m_settings::DrawClothingIcons = false;
						Menu().CheckBox(XS("Clothing (icons)"), m_settings::DrawClothingIcons);
						if (m_settings::DrawClothingIcons)
							m_settings::DrawClothing = false;
						Menu().CheckBox(XS("PlayerChams"), m_settings::PlayerChams);
						Menu().CheckBox(XS("Corpse"), m_settings::Corpse);
						Menu().CheckBox(XS("Backpack"), m_settings::BackPack);
						//Menu().CheckBox(XS(L"OOFOV"), m_settings::OOFIndicators);
						Menu().CheckBoxKeyBind(XS("Save Pos"), m_settings::SavePos, m_settings::SavePosKey);
						Menu().Dropdown(XS("Chams Type"), { XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame"), XS("Color") }, m_settings::SelectedChams, chams_type_opened);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().CheckBox(XS("Vischeck"), m_settings::EspVisCheck);
						Menu().CheckBox(XS("Tags Vischeck"), m_settings::TagsVisCheck);
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

						Menu().CheckBox(XS("LoadLightning"), m_settings::LoadLightning);
						Menu().CheckBox(XS("LoadGeometric"), m_settings::LoadGeometric);
						Menu().CheckBox(XS("LoadGalaxy"), m_settings::LoadGalaxy);
						Menu().CheckBox(XS("LoadWireFrame"), m_settings::LoadWireFrame);
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
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().Slider(XS("Crates Distance"), m_settings::MaxCrateDistance, 0, 500);
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
					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
						Menu().Slider(XS("Dropped Distance"), m_settings::MaxDroppedDistance, 0, 500);
						Menu().Slider(XS("Traps Distance"), m_settings::MaxTrapsDistance, 0, 500);
						Menu().Slider(XS("APC Distance"), m_settings::MaxAPCDistance, 0, 3000);

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
						Menu().CheckBox(XS("NoCollision (Trees)"), m_settings::IgnoreTrees);
						Menu().CheckBox(XS("NoCollision (Players)"), m_settings::IgnorePlayers);
						Menu().CheckBox(XS("NameSpoofer"), m_settings::NameSpoofer);
						Menu().CheckBox(XS("DisableHitSounds"), m_settings::DisableHitSounds);
						Menu().CheckBox(XS("CustomHitSounds"), m_settings::CustomHitSounds);

					}

					Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
					{
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
					Menu().CheckBox(XS("NoSpread"), m_settings::NoSpread);
					Menu().CheckBox(XS("NoWeaponBob"), m_settings::NoWeaponBob);
					Menu().CheckBox(XS("NoSway"), m_settings::NoSway);
					Menu().CheckBox(XS("InstantEoka"), m_settings::InstantEoka);
					Menu().CheckBox(XS("RemoveAttackAnimations"), m_settings::RemoveAttackAnimations);
					Menu().CheckBox(XS("Long Melee"), m_settings::LongMelee);

				}

				Menu().BeginChild(XS("Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBoxKeyBind(XS("WeaponSpammer"), m_settings::WeaponSpammer, m_settings::WeaponSpamKey);
					if (m_settings::WeaponSpammer) {
						Menu().Slider(XS("WeaponSpammerDelay"), m_settings::WeaponSpamDelay, 0, 20);
					}

					Menu().CheckBox(XS("KillEffects"), m_settings::KillEffects);
					Menu().Dropdown(XS("Effect Type"), { XS("Explosion"), XS("Ghosts") }, m_settings::SelectedKillEffect, killeffect_type_open);

					

					Menu().CheckBox(XS("WeaponChams"), m_settings::WeaponChams);
					Menu().Dropdown(XS("Chams Type"), { XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy"), XS("WireFrame") }, m_settings::WeaponSelectedChams, wchams_type_opens);

					Menu().CheckBox(XS("LoadLightning"), m_settings::LoadLightning);
					Menu().CheckBox(XS("LoadGeometric"), m_settings::LoadGeometric);
					Menu().CheckBox(XS("LoadGalaxy"), m_settings::LoadGalaxy);
					Menu().CheckBox(XS("LoadWireFrame"), m_settings::LoadWireFrame);

					Menu().CheckBox(XS("LoadExplosionEffect"), m_settings::LoadExplosionEffect);
					Menu().CheckBox(XS("LoadGhostEffect"), m_settings::LoadGhostEffect);


				}
				break;
			}
			case 4:
			{
				Menu().BeginChild(XS("Colors"), { 60,45 }, { 220,290 });
				{
					Menu().Button(XS("Reset PlayerModels"), reset_player_model);
					Menu().Button(XS("Clear RaidCache"), Buttons::ClearRaidCache);
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
		}
	}

	Menu().end_window();
}