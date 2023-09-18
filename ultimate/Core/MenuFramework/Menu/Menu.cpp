#include "Menu.hpp"
#include "../../Includes/settings.hpp"
inline bool aim_type_opened;
inline bool chams_type_opened;
inline bool bullet_tpe_open;
inline bool config_type_open;
inline bool hitmat_open;

inline bool aim_type_opene2;
#include "../../Configs/Configs.hpp"
#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"


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
			Menu().SubTab(XS(L"Aimbot"), 0, Vector2(156, 35)); //468
			Menu().SubTab(XS(L"Exploits"), 1, Vector2(156, 35));
			Menu().SubTab(XS(L"Visuals"), 2, Vector2(156, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS(L"Aimbot"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Memory Aimbot"), m_settings::MemoryAimbot);
					Menu().CheckBox(XS(L"Silent Aimbot"), m_settings::SilentAim);
					//Menu().CheckBox(XS(L"Melee Aimbot"), m_settings::MeleeAimbot);
					Menu().CheckBox(XS(L"Heli Aimbot"), m_settings::HeliAimbot);
					//Menu().CheckBox(XS(L"Silent Melee"), m_settings::SilentMelee);
					if (m_settings::HeliAimbot)
					{
						Menu().CheckBox(XS(L"Heli Override"), m_settings::HeliHitboxOverride);
					}
					Menu().Slider(XS(L"Accuracy"), m_settings::AimbotAccuracy, 0, 100);
					Menu().Slider(XS(L"Fov Slider"), m_settings::AimbotFOV, 0, 1000);
					Menu().Dropdown(XS("Aimbone"), { XS("Head"), XS("Neck"), XS("Chest"), XS("Random"), XS("Closest To Crosshair") }, m_settings::SelectedAimbone, aim_type_opened);
					
					Menu().Spacer(50);

					Menu().Dropdown(XS("HitMaterial"), { XS("Flesh"), XS("Glass"), XS("Metal"), XS("Water")}, m_settings::HitMaterial, hitmat_open);

				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{


					Menu().CheckBox(XS(L"Target NPC"), m_settings::AimbotNPC);
					Menu().CheckBox(XS(L"Target Wounded"), m_settings::TargetWounded);
					//Menu().CheckBox(XS(L"Target FriendList"), m_settings::TargetFriendList);

				}
				break;
			case 1:
				Menu().BeginChild(XS(L"Exploits"), { 60,45 }, { 220,290 });
				{				
					Menu().CheckBoxKeyBind(XS(L"AutoShoot"), m_settings::Autoshoot, m_settings::AutoshootKey);

					if (m_settings::Autoshoot)
					{
						Menu().CheckBox(XS(L"AlwaysAutoshoot"), m_settings::AlwaysAutoshoot);
					}
					Menu().CheckBoxKeyBind(XS(L"Manipulation"), m_settings::Manipulation, m_settings::ManipKey);
					if (m_settings::Manipulation)
					{
						Menu().Slider(XS(L"ManipAngles"), m_settings::ManipPoints, 5, 100);
						//m_settings::ManipPoints
					}

					Menu().CheckBox(XS(L"BulletTp"), m_settings::BulletTP);
					//Menu().CheckBox(XS(L"AutoStop"), m_settings::StopPlayer);

					Menu().CheckBox(XS(L"PierceMaterials"), m_settings::PierceMaterials);
					Menu().CheckBox(XS(L"Bullet Queue"), m_settings::InstantKill);
					if (m_settings::InstantKill)
					{
						Menu().CheckBox(XS(L"WaitForBulletTP"), m_settings::WaitForBulletTP);
					}

					Menu().CheckBox(XS(L"Instant Hit"), m_settings::InstantBullet);
					Menu().CheckBox(XS(L"WaitForInstantHit"), m_settings::WaitForInstantHit);
				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Auto Reload"), m_settings::AutoReload);

					Menu().CheckBox(XS(L"Hitbox Override"), m_settings::HitboxOverride);
					if (m_settings::HitboxOverride)
					{
						Menu().Dropdown(XS("Hitbox"), { XS("Head"), XS("Chest"), XS("Random") }, m_settings::SelectedHitbox, aim_type_opene2);
					}

					if (m_settings::BulletTP)
						Menu().Dropdown(XS("BTP Mode"), { XS("Low"), XS("Medium"), XS("High"), XS("Intense (FPS)") }, m_settings::BulletTPIntensity, bullet_tpe_open);
				}
				break;

			case 2:
				Menu().BeginChild(XS(L"Visuals"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Crosshair"), m_settings::Crosshair);
					if (m_settings::Crosshair)
					{
						m_settings::Swastika = false;
					}

					Menu().CheckBox(XS(L"SwastikaCrosshair"), m_settings::Swastika);
					if (m_settings::Swastika)
					{
						m_settings::Crosshair = false;
						Menu().Slider(XS(L"SwastikaSize"), m_settings::SwastikaSize, 1, 20);
					}
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
			Menu().SubTab(XS(L"Player"), 0, Vector2(117, 35)); //468
			Menu().SubTab(XS(L"Resources"), 1, Vector2(117, 35));
			Menu().SubTab(XS(L"Lootables"), 2, Vector2(117, 35));
			Menu().SubTab(XS(L"Other"), 3, Vector2(117, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS(L"Visuals"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Username"), m_settings::nameEsp);
					//Menu().CheckBox(XS(L"Distance"), m_settings::DrawDistance);
					Menu().CheckBox(XS(L"Box"), m_settings::BoxEsp);
					if (m_settings::BoxEsp)
						m_settings::CornerBox = false;
					Menu().CheckBox(XS(L"CornerBox"), m_settings::CornerBox);
					if (m_settings::CornerBox)
						m_settings::BoxEsp = false;
					Menu().CheckBox(XS(L"Skeleton"), m_settings::Skeleton);
					Menu().CheckBox(XS(L"Healthbar"), m_settings::healthBar);
					Menu().CheckBox(XS(L"Helditem"), m_settings::helditem);
					Menu().CheckBox(XS(L"isOutside"), m_settings::BaseCheck);
					//Menu().CheckBox(XS(L"Inventory"), m_settings::DrawInventory);
				//	Menu().CheckBox(XS(L"Clothing"), m_settings::DrawClothing);
					Menu().CheckBox(XS(L"PlayerChams"), m_settings::PlayerChams);
					Menu().CheckBox(XS(L"Corpse"), m_settings::Corpse);
					Menu().CheckBox(XS(L"Backpack"), m_settings::BackPack);
					//Menu().CheckBox(XS(L"OOFOV"), m_settings::OOFIndicators);
					Menu().CheckBoxKeyBind(XS(L"Save Pos"), m_settings::SavePos, m_settings::SavePosKey);
					Menu().Dropdown(XS("Chams Type"), { XS("NightFire Blue"), XS("NightFire Red"), XS("Lightning"), XS("Geometric Disolve"), XS("Galaxy") }, m_settings::SelectedChams, chams_type_opened);

				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Vischeck"), m_settings::EspVisCheck);
					Menu().CheckBox(XS(L"Tags Vischeck"), m_settings::TagsVisCheck);
					Menu().CheckBox(XS(L"Show Target"), m_settings::DrawTarget);
					Menu().CheckBox(XS(L"Wounded"), m_settings::DrawWounded);
					Menu().CheckBox(XS(L"Safezone"), m_settings::DrawSafezone);
					Menu().CheckBox(XS(L"Npc's"), m_settings::DrawNPC);
					Menu().CheckBox(XS(L"Sleepers"), m_settings::DrawSleepers);
					//Menu().CheckBox(XS(L"Disconnected"), m_settings::DrawAis);
					//Menu().CheckBox(XS(L"ShowCheatsUsers"), m_settings::ShowUsers);

					Menu().Slider(XS(L"PlayerDistance"), m_settings::PlayerESPDistance, 0, 500);
					Menu().Slider(XS(L"NPC Distance"), m_settings::NPCDistance, 0, 500);
					Menu().Slider(XS(L"Drops Distance"), m_settings::MaxPlayerDropsDistance, 0, 500);

					Menu().CheckBox(XS(L"LoadLightning"), m_settings::LoadLightning);
					Menu().CheckBox(XS(L"LoadGeometric"), m_settings::LoadGeometric);
					Menu().CheckBox(XS(L"LoadGalaxy"), m_settings::LoadGalaxy);
				}
				break;
			case 1:
				Menu().BeginChild(XS(L"World"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"StoneOre"), m_settings::StoneOre);
					Menu().CheckBox(XS(L"MetalOre"), m_settings::MetalOre);
					Menu().CheckBox(XS(L"SulfurOre"), m_settings::SulfurOre);
					//	Menu().CheckBox(XS(L"Ore Icon"), m_settings::OreIcons);

					Menu().CheckBox(XS(L"Hemp"), m_settings::Hemp);
					Menu().CheckBox(XS(L"Diesel"), m_settings::DieselBarrel);
					//	Menu().CheckBox(XS(L"Collectables Icon"), m_settings::CollectablesIcon);

					Menu().CheckBox(XS(L"Corn"), m_settings::Corn);
					Menu().CheckBox(XS(L"Pumpkin"), m_settings::Pumpkin);
					Menu().CheckBox(XS(L"Potato"), m_settings::Potato);
					Menu().CheckBox(XS(L"Mushroom"), m_settings::Mushroom);
				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().Slider(XS(L"Ore Distance"), m_settings::MaxOreDistance, 0, 500);
					Menu().Slider(XS(L"Collectables Distance"), m_settings::MaxCollectableDistance, 0, 500);
					Menu().Slider(XS(L"Food Distance"), m_settings::MaxFoodDistance, 0, 500);
				}
				break;

			case 2:
				Menu().BeginChild(XS(L"World"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Stash"), m_settings::Stash);
					Menu().CheckBox(XS(L"HackableCrate"), m_settings::HackableCrate);
					if (m_settings::HackableCrate)
					{
						Menu().CheckBox(XS(L"HackableCrateFlags"), m_settings::HackableCrateFlags);
						Menu().CheckBox(XS(L"HackableCrateTimer"), m_settings::HackableCrateTimer);
					}
					Menu().CheckBox(XS(L"Bradley Crate"), m_settings::BradleyCrate);
					Menu().CheckBox(XS(L"Heli Crate"), m_settings::HeliCrate);
				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().Slider(XS(L"Crates Distance"), m_settings::MaxCrateDistance, 0, 500);
				}
				break;

			case 3:
				Menu().BeginChild(XS(L"World"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"DroppedItems"), m_settings::DroppedItems);
					Menu().CheckBox(XS(L"Turret"), m_settings::AutoTurret);
					if (m_settings::AutoTurret)
					{
						Menu().CheckBox(XS(L"Authorized Players"), m_settings::TurretAuthorizedPlayers);
						Menu().CheckBox(XS(L"EquippedFlag"), m_settings::TurretEquippedFlags);
						Menu().CheckBox(XS(L"TurretOnFlags"), m_settings::TurretOnFlags);
						Menu().CheckBox(XS(L"Turret Health"), m_settings::TurretHealth);
						Menu().CheckBox(XS(L"TurningFlag"), m_settings::TurretTurningFlag);
						Menu().CheckBox(XS(L"TurretRange"), m_settings::TurretRange);
					}
					Menu().CheckBox(XS(L"Patrol Helicopter"), m_settings::PatrolHelicopter);
				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().Slider(XS(L"Dropped Distance"), m_settings::MaxDroppedDistance, 0, 500);
					Menu().Slider(XS(L"Traps Distance"), m_settings::MaxTrapsDistance, 0, 500);
					Menu().Slider(XS(L"APC Distance"), m_settings::MaxAPCDistance, 0, 3000);
				}
				break;
			}
			break;
		case 2:
		{
			Menu().SubTab(XS(L"LocalPlayer"), 0, Vector2(156, 35)); //468
			Menu().SubTab(XS(L"Other"), 1, Vector2(156, 35));
			Menu().SubTab(XS(L"Friends"), 2, Vector2(156, 35));
			//Menu().SubTab(XS(L"World"), 3, Vector2(117, 35));

			switch (activesubtab)
			{
			case 0:
				Menu().BeginChild(XS(L"LocalPlayer"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Flyhack Indicator"), m_settings::Flyhack_Indicator);
					Menu().CheckBox(XS(L"Anti FlyhackKick"), m_settings::AntiFlyKick);
					Menu().CheckBox(XS(L"Spiderman"), m_settings::SpiderMan);
					Menu().CheckBox(XS(L"SmallerLocalRadius"), m_settings::SmallerLocalRadius);
					Menu().CheckBox(XS(L"Admin Flags"), m_settings::AdminFlags);
					Menu().CheckBox(XS(L"Infinite Jump"), m_settings::InfiniteJump);
					Menu().CheckBox(XS(L"Omnisprint"), m_settings::OmniSprint);
					Menu().CheckBox(XS(L"NoMovementReduction"), m_settings::NoMovementRestrictions);
					Menu().CheckBox(XS(L"Ignore Trees"), m_settings::IgnoreTrees);
					Menu().CheckBox(XS(L"Ignore Players"), m_settings::IgnorePlayers);
					Menu().CheckBox(XS(L"NameSpoofer"), m_settings::NameSpoofer);

				}

				Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBox(XS(L"Instant Loot"), m_settings::InstantLoot);
					Menu().CheckBox(XS(L"Instant Heal"), m_settings::InstantHeal);
					Menu().CheckBoxKeyBind(XS(L"NoClip"), m_settings::AdminCheat, m_settings::AdminCheatKey);
					Menu().CheckBoxKeyBind(XS(L"InstantRevive"), m_settings::InstantRevive, m_settings::InstantReviveKey);
					Menu().CheckBoxKeyBind(XS(L"Keep TargetAlive"), m_settings::KeepTargetAlive, m_settings::KeepAliveKey);
					Menu().CheckBoxKeyBind(XS(L"Loot Body"), m_settings::LootBodyThruWall, m_settings::LootBodyThruWallKey);
					Menu().CheckBoxKeyBind(XS(L"Loot Corpse"), m_settings::LootCorpseThruWall, m_settings::LootCorpseThruWallKey);
					Menu().CheckBox(XS(L"Spinbot"), m_settings::Spinbot);
					Menu().CheckBox(XS(L"FixDebugCamera"), m_settings::FixDebugCamera);
					Menu().CheckBoxKeyBind(XS(L"Interactive Debug"), m_settings::InteractiveDebug, m_settings::InteractiveKey);

				}
				break;
			case 1:
				Menu().BeginChild(XS(L"Misc"), { 60,45 }, { 220,290 });
				{
					Menu().CheckBoxKeyBind(XS(L"Zoom"), m_settings::Zoom, m_settings::ZoomKey);
					if (m_settings::Zoom) {
						Menu().Slider(XS(L"Zoom Amount"), m_settings::ZoomAmount, 0, 50);
					}
					
					Menu().CheckBox(XS(L"PlayerFov"), m_settings::PlayerFov);
					if (m_settings::PlayerFov) {
						Menu().Slider(XS(L"PlayerFov Amount"), m_settings::PlayerFovAmount, 0, 140);
					}
					
					Menu().CheckBox(XS(L"AutoFarmTree"), m_settings::AutoFarmTree);
					Menu().CheckBox(XS(L"AutoFarmOre"), m_settings::AutoFarmOre);

				}

				Menu().BeginChild(XS(L"World"), { 285,45 }, { 220,290 });
				{
					//Menu().CheckBox(XS(L"Brightnight"), m_settings::Brightnight);
					//Menu().CheckBox(XS(L"Stars"), m_settings::Stars);
					//Menu().CheckBox(XS(L"BrightCave"), m_settings::BrightCave);
					Menu().CheckBox(XS(L"TimeChanger"), m_settings::TimeChanger);
					if (m_settings::TimeChanger) {
						Menu().Slider(XS(L"GameTime: "), m_settings::GameTime, 0, 24);
					}
					//Menu().CheckBox(XS(L"RemoveUnderwaterEffects"), m_settings::RemoveUnderwaterEffects);
				}
				break;

			case 2:
				/*Menu().BeginChild(XS(L"Friend List"), { 60,45 }, { 220,290 });
				{
					for (const auto& wideKey : wideKeys) {
						Menu().Text(wideKey.c_str());
					}
				}

				Menu().BeginChild(XS(L"Settings"), { 285,45 }, { 220,290 });
				{
					Menu().CheckBoxKeyBind(XS(L"Add Friends"), m_settings::removefriend1, m_settings::AddFriend);
					Menu().CheckBoxKeyBind(XS(L"Remove Friend"), m_settings::removefriend2, m_settings::RemoveFriend);
					Menu().CheckBoxKeyBind(XS(L"Remove All"), m_settings::removefriend3, m_settings::RemoveAllFriends);
				}*/
				break;

				/*case 3:
					Menu().BeginChild(XS(L"Page1"), { 60,45 }, { 220,290 });
					{

					}

					Menu().BeginChild(XS(L"Page2"), { 285,45 }, { 220,290 });
					{
					}
					break;*/
			}
		}
			break;
		case 3:
			Menu().BeginChild(XS(L"Weapon"), { 60,45 }, { 220,290 });
			{
				Menu().CheckBox(XS(L"No Attack Restrictions"), m_settings::NoAttackRestrictions);
				Menu().CheckBox(XS(L"Recoil Modifier"), m_settings::ChangeRecoil);
				if (m_settings::ChangeRecoil) {
					Menu().Slider(XS(L"Recoil Percent X"), m_settings::recoilPercent, 0, 100);
					Menu().Slider(XS(L"Recoil Percent Y"), m_settings::RecoilPercentY, 0, 100);
				}
				Menu().CheckBox(XS(L"Thickness Modifier"), m_settings::NormalThickBullet);
				if (m_settings::NormalThickBullet) {
					Menu().Slider(XS(L"Bullet Thickness"), m_settings::NormalThickBulletThickness, 0, 4.5);
				}
				Menu().CheckBox(XS(L"Fast Bullet"), m_settings::NormalFastBullet);
				Menu().CheckBox(XS(L"Force Automatic"), m_settings::ForceAutomatic);
				Menu().CheckBox(XS(L"NoSpread"), m_settings::NoSpread);
				Menu().CheckBox(XS(L"NoWeaponBob"), m_settings::NoWeaponBob);
				Menu().CheckBox(XS(L"NoSway"), m_settings::NoSway);
				//Menu().CheckBox(XS(L"InstantEoka"), m_settings::InstantEoka);
				Menu().CheckBox(XS(L"RemoveAttackAnimations"), m_settings::RemoveAttackAnimations);
			}

			Menu().BeginChild(XS(L"Other"), { 285,45 }, { 220,290 });
			{
				Menu().CheckBoxKeyBind(XS(L"WeaponSpammer"), m_settings::WeaponSpammer, m_settings::WeaponSpamKey);
				if (m_settings::WeaponSpammer) {
					Menu().Slider(XS(L"WeaponSpammerDelay"), m_settings::WeaponSpamDelay, 0, 20);
				}

			
			}
			break;
		case 4:
			Menu().BeginChild(XS(L"Colors"), { 60,45 }, { 220,290 });
			{
				Menu().Button(XS("Reset PlayerModels"), reset_player_model);

				//Menu().CheckBox(XS(L"No Attack Restrictions"), m_settings::NoAttackRestrictions);
				//Menu().CheckBox(XS(L"Recoil Modifier"), m_settings::ChangeRecoil);
				//if (m_settings::ChangeRecoil) {
				//	Menu().Slider(XS(L"Recoil Percent X"), m_settings::recoilPercent, 0, 100);
				//	Menu().Slider(XS(L"Recoil Percent Y"), m_settings::RecoilPercentY, 0, 100);
				//}
				//Menu().CheckBox(XS(L"Thickness Modifier"), m_settings::NormalThickBullet);
				//if (m_settings::NormalThickBullet) {
				//	Menu().Slider(XS(L"Bullet Thickness"), m_settings::NormalThickBulletThickness, 0, 4.5);
				//}
				//Menu().CheckBox(XS(L"Fast Bullet"), m_settings::NormalFastBullet);
				//Menu().CheckBox(XS(L"Force Automatic"), m_settings::ForceAutomatic);
				//Menu().CheckBox(XS(L"NoSpread"), m_settings::NoSpread);
				//Menu().CheckBox(XS(L"NoWeaponBob"), m_settings::NoWeaponBob);
				//Menu().CheckBox(XS(L"NoSway"), m_settings::NoSway);
				//Menu().CheckBox(XS(L"InstantEoka"), m_settings::InstantEoka);
			}

			Menu().BeginChild(XS(L"Configs"), { 285,45 }, { 220,290 });
			{
				Menu().Button(XS("Save Config"), Configs::SaveConfig);
				Menu().Button(XS("Load Config"), Configs::LoadConfig);
				Menu().Spacer(30);
				
				Menu().Dropdown(XS("Config Type"), { XS("Legit"), XS("Rage"), XS("Config1"), XS("Config2"), XS("Config3") }, m_settings::SelectedConfig, config_type_open);
			}
			break;
		}
	}

	Menu().end_window();
}