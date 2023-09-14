#pragma once

#include "../SDK/RustStructs.h"


namespace m_settings {
	inline bool SilentAim = false;
	inline bool PlayerChams = false;
	inline bool NoMovementRestrictions = false;
	inline float AimbotFOV = 200.f;
	inline float TestSlider = 24.f;
	inline bool NormalThickBullet = false;
	inline bool DrawInventory = false;
	inline bool DrawClothing = false;
	inline float NormalThickBulletThickness = 4.4f;
	inline bool AimbotNPC = false;
	inline bool HeliAimbot = false;
	inline bool InstantEoka = false;
	inline bool TargetWounded = false;
	inline bool ShowUsers = false;
	inline int SelectedAimbone = 0;
	inline bool MeleeAimbot = false;
	inline bool FloorHugger = false;
	inline bool HackableCrateTimer = false;
	inline bool AlwaysManipulate = false;
	inline bool PatrolHelicopter = false;
	inline bool DrawDistance = false;
	inline bool InteractiveDebug = false;
	inline bool HackableCrateFlags = false;
	inline bool InstantBullet = false;
	inline bool FixDebugCamera = false;
	inline int SelectedChams = 0;
	inline bool InstantKill = false;
	inline bool WaitForBulletTP = false;
	inline bool Target_Indicator = false;
	inline bool NormalFastBullet = false;
	inline bool NoWeaponBob = false;
	inline bool WeaponSpammer;
	inline float WeaponSpamDelay = 10.f;
	inline RustStructs::KeyCode InteractiveKey = RustStructs::KeyCode::F;

	inline RustStructs::KeyCode WeaponSpamKey = RustStructs::KeyCode::F;
	inline bool PierceMaterials = false;
	inline bool Crosshair = true;
	inline bool BaseCheck = false;
	inline bool BulletTracers = false;
	inline int SelectedHitbox = 0;
	inline int BulletTPIntensity = 2;
	inline bool AutoReload = false;
	inline bool HeliHitboxOverride = false;
	inline bool Aimline = false;
	inline bool HitboxOverride = false;
	inline float reload_time = 0.f;
	inline float BulletTPRadius = 2.4f;
	inline bool OOFIndicators = false;
	inline bool AimMarker = false;
	inline bool DrawFov = false;
	inline bool TargetFriendList = false;
	inline bool InstantLoot = false;
	inline float Fov_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float Crosshair_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float AimbotAccuracy = 100.f;
	inline bool ChangeRecoil = false;
	inline bool Thickbullet_Arrows = false;
	inline bool BulletTP = false;
	inline bool Manipulation = true;
	inline bool StopPlayer = false;
	inline bool ManipFlags = false;
	inline bool BulletTPFlags = false;
	inline bool BlockServerCommands = true;
	inline bool Autoshoot = false;
	inline bool AlwaysAutoshoot = false;
	inline bool NoSpread = false;
	inline bool NoSway = false;
	inline bool OnHalfDesync = false;
	inline bool FastBullets = false;
	inline float BulletsSpeeds = 100;
	inline bool SilentMelee = false;
	inline RustStructs::KeyCode ManipKey = RustStructs::KeyCode::F;
	inline RustStructs::KeyCode AddFriend = RustStructs::KeyCode::Keypad0;
	inline RustStructs::KeyCode RemoveFriend = RustStructs::KeyCode::Keypad1;
	inline RustStructs::KeyCode RemoveAllFriends = RustStructs::KeyCode::Keypad2;
	inline bool just_shot = false;
	inline bool did_reload = false;
	inline bool reload_reset = false;
	inline bool reload_reset_2 = false;
	inline float time_since_last_shot = 0.0f;
	inline float fixed_time_last_shot = 0.0f;
	inline bool removefriend1 = false;
	inline bool removefriend2 = false;
	inline bool removefriend3 = false;
	inline bool ForceAutomatic = false;

	inline bool LoadGalaxy = false;
	inline bool LoadLightning = false;
	inline bool LoadGeometric = false;

	inline RustStructs::KeyCode AutoshootKey = RustStructs::KeyCode::F;
	inline bool IncludeFatBullet = false;

	inline int recoilPercent = 100;
	inline int RecoilPercentY = 100;

	inline bool AdminFlags = false;
	inline bool AdminCheat = false;
	inline RustStructs::KeyCode AdminCheatKey = RustStructs::KeyCode::C;
	inline bool SmallerLocalRadius = false;
	inline bool SpiderMan = false;
	inline bool InfiniteJump = false;
	inline bool NoAttackRestrictions = false;
	inline bool AlwaysSprint = false;
	inline bool OmniSprint = false;
	inline bool InstantHeal = false;
	inline bool IgnoreTrees = false;
	inline bool IgnorePlayers = false;
	inline bool InstantRevive = false;
	inline bool PlayerFov = false;
	inline float PlayerFovAmount = 90.f;
	inline bool Zoom = false;
	inline RustStructs::KeyCode ZoomKey = RustStructs::KeyCode::G;
	inline float ZoomAmount = 50.f;

	inline bool AutoFarmTree = false;
	inline bool AutoFarmOre = false;

	inline RustStructs::KeyCode InstantReviveKey = RustStructs::KeyCode::F;
	inline bool KeepTargetAlive = false;
	inline RustStructs::KeyCode KeepAliveKey = RustStructs::KeyCode::F;
	inline bool Spinbot = false;
	inline bool LootBodyThruWall = false;
	inline RustStructs::KeyCode LootBodyThruWallKey = RustStructs::KeyCode::X;
	inline bool LootCorpseThruWall = false;
	inline RustStructs::KeyCode LootCorpseThruWallKey = RustStructs::KeyCode::Z;

	inline bool Stash = false;
	inline bool Hemp = false;
	inline bool CollectablesIcon = false;
	inline bool WaitForInstantHit = false;
	inline bool ShowBulletTPAngle = false;
	inline bool DroppedItems = false;
	inline float DroppedItemColor[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float HempColor[4] = { 108.f, 238.f, 0.f, 255.f };
	inline float DieselColor[4] = { 72.f, 72.f, 72.f, 255.f };
	inline float StoneColor[4] = { 238.f, 238.f, 238.f, 255.f };
	inline float MetalColor[4] = { 100.f, 49.f, 49.f, 255.f };
	inline float SulfurColor[4] = { 238.f, 238.f, 0.f, 255.f };
	inline float MaxDroppedDistance = 50.f;
	inline float MaxTrapsDistance = 50.f;
	inline float MaxCrateDistance = 50.f;
	inline float MaxFoodDistance = 50.f;
	inline float MaxAPCDistance = 1500.f;
	inline float MaxPlayerDropsDistance = 50.f;
	inline bool StoneOre = false;
	inline bool MetalOre = false;
	inline bool SulfurOre = false;
	inline bool OreIcons = false;
	inline float MaxOreDistance = 100.f;
	inline float MaxCollectableDistance = 50.f;
	inline float IconsScale = 24.f;

	inline bool Mushroom = false;
	inline bool Pumpkin = false;
	inline bool Corn = false;
	inline bool Potato = false;
	inline bool FoodIcons = false;

	inline bool Bear = false;
	inline bool Wolf = false;
	inline bool Stag = false;
	inline bool Boar = false;

	inline bool DieselBarrel = false;
	inline float WorldFontSize = 10.f;

	inline float MushRoomColor[4] = { 66.f, 126.f, 51.f, 255.f };
	inline float PumpkinColor[4] = { 66.f, 126.f, 51.f, 255.f };
	inline float CornColor[4] = { 66.f, 126.f, 51.f, 255.f };
	inline float PotatoColor[4] = { 66.f, 126.f, 51.f, 255.f };

	inline bool Corpse = false;
	inline bool BackPack = false;

	inline float CorpseColor[4] = { 201.f, 235.f, 168.f, 255.f };
	inline float BackPackColor[4] = { 238.f, 238.f, 238.f, 255.f };

	inline bool AutoTurret = false;
	inline bool HackableCrate = false;
	inline bool BradleyCrate = false;
	inline bool HeliCrate = false;
	inline bool TurretRange = false;
	inline bool TurretAuthorizedPlayers = false;
	inline bool TurretTurningFlag = false;
	inline bool TurretEquippedFlags = false;
	inline bool TurretHealth = false;
	inline float TurretColor[4] = { 238.f, 0.f, 0.f, 255.f };
	inline float CrateColor[4] = { 0.f, 255.f, 255.f, 255.f };
	inline float HeliColor[4] = { 255.f, 0.f, 0.f, 255.f };
	//esp
	inline bool SavePos = false;
	inline RustStructs::KeyCode SavePosKey = RustStructs::KeyCode::F;

	inline bool nameEsp = false;
	inline bool BoxEsp = false;
	inline bool Swastika = false;
	inline float SwastikaSpeed = 1.f;
	inline float SwastikaSize = 15.f;
	inline bool CornerBox = false;
	inline bool healthBar = false;
	inline bool Skeleton = false;
	inline bool helditem = false;
	inline bool EspVisCheck = false;
	inline float DrawBox_Color[4] = { 205.f, 5.0f, 2.0f, 255.f };
	inline float VisCheck_Color[4] = { 63.f, 210.0f, 0.0f, 255.f };
	inline float DrawNameTag_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float DrawHeldItem_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float Friend_Color[4] = { 0.f, 255.f, 255.f, 255.f };
	inline float Wounded_Color[4] = { 255.f, 149.f, 0.f, 255.f };
	inline float Scientist_color[4] = { 29.f, 31.f, 161.f, 255.f };
	inline float Dead_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float Safezone_Color[4] = { 204.f, 88.0f, 202.f, 255.f };
	inline float Target_Color[4] = { 91, 23, 227, 255.f };
	inline float fontsize = 10.f;
	inline bool TagsVisCheck = false;

	inline bool DrawNPC = false;
	inline float NPCDistance = 30.f;
	inline bool DrawDead = false;
	inline bool DrawAis = true;
	inline bool DrawSleepers = false;
	inline float Sleeper_Color[4] = { 0.0f, 255.f, 255.f, 255.f };
	inline bool DrawWounded = false;
	inline bool DrawTarget = false;
	inline bool DrawSafezone = false;
	inline float PlayerESPDistance = 300.f;

	inline bool Flyhack_Indicator = true;
	inline bool AntiFlyKick = false;
	inline float MaxVerticalFlyhack;
	inline float VerticalFlyhack;
	inline float MaxHorisontalFlyhack;
	inline float HorisontalFlyhack;

	inline bool Brightnight = false;
	inline bool Stars = false;
	inline bool BrightCave = false;
	inline bool TimeChanger = false;
	inline float GameTime = 12.f;
	inline bool RemoveUnderwaterEffects = false;

	inline float last_tick_time = 0.f;
	inline float max_spoofed_eye_distance = 0.f;
	inline bool can_manipulate = false;
	inline bool StartShooting = false;
	inline bool Manipulation_Indicator = false;
	inline bool Thickbullet_Indicator = false;
	inline bool Thickbullet_AutoShoot = false;

};

//inline RustStructs::KeyCode ManipulationKey = RustStructs::KeyCode::F;