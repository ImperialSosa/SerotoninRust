#include "Configs.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../SDK/System/System.hpp"
inline bool gggg = false;
#include "../Utils/json.hpp"
#include "../Features/Notifications/Notifications.hpp"
using json = nlohmann::json;

void Configs::LoadConfig()
{
    std::string file_name;
    if (m_settings::SelectedConfig == 0)
    {
        file_name = XS("Legit.json");
    }
    else if (m_settings::SelectedConfig == 1)
    {
        file_name = XS("Rage.json");
    }
    else if (m_settings::SelectedConfig == 2)
    {
        file_name = XS("Config1.json");
    }
    else if (m_settings::SelectedConfig == 3)
    {
        file_name = XS("Config2.json");
    }
    else if (m_settings::SelectedConfig == 4)
    {
        file_name = XS("Config3.json");
    }

    FILE* file = LI_FN(fopen)(file_name.c_str(), XS("r"));
    if (file == nullptr) {
        // Handle error: Unable to open the file
        return;
    }

    LI_FN(fseek)(file, 0, SEEK_END);
    long fileSize = LI_FN(ftell)(file);
    LI_FN(fseek)(file, 0, SEEK_SET);

    if (fileSize <= 0) {
        LI_FN(fclose)(file);
        return;
    }

    char* buffer = new char[fileSize + 1];
    LI_FN(fread)(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    LI_FN(fclose)(file);

    nlohmann::json config = nlohmann::json::parse(buffer);

    // Set your variables from the loaded JSON data
    m_settings::SilentAim = config.value(XS("SilentAim"), m_settings::SilentAim);
    m_settings::PlayerChams = config.value(XS("PlayerChams"), m_settings::PlayerChams);
    m_settings::NoMovementRestrictions = config.value(XS("NoMovementRestrictions"), m_settings::NoMovementRestrictions);
    m_settings::AimbotFOV = config.value(XS("AimbotFOV"), m_settings::AimbotFOV);
    m_settings::TestSlider = config.value(XS("TestSlider"), m_settings::TestSlider);
    m_settings::NormalThickBullet = config.value(XS("NormalThickBullet"), m_settings::NormalThickBullet);
    m_settings::DrawInventory = config.value(XS("DrawInventory"), m_settings::DrawInventory);
    m_settings::DrawClothing = config.value(XS("DrawClothing"), m_settings::DrawClothing);
    m_settings::DrawInventoryIcons = config.value(XS("DrawInventoryIcons"), m_settings::DrawInventoryIcons);
    m_settings::DrawClothingIcons = config.value(XS("DrawClothingIcons"), m_settings::DrawClothingIcons);
    m_settings::NormalThickBulletThickness = config.value(XS("NormalThickBulletThickness"), m_settings::NormalThickBulletThickness);
    m_settings::AimbotNPC = config.value(XS("AimbotNPC"), m_settings::AimbotNPC);
    m_settings::HeliAimbot = config.value(XS("HeliAimbot"), m_settings::HeliAimbot);
    m_settings::HitMaterial = config.value(XS("HitMaterial"), m_settings::HitMaterial);
    m_settings::InstantEoka = config.value(XS("InstantEoka"), m_settings::InstantEoka);
    m_settings::TargetWounded = config.value(XS("TargetWounded"), m_settings::TargetWounded);
    m_settings::ShowUsers = config.value(XS("ShowUsers"), m_settings::ShowUsers);
    m_settings::SelectedAimbone = config.value(XS("SelectedAimbone"), m_settings::SelectedAimbone);
    m_settings::MeleeAimbot = config.value(XS("MeleeAimbot"), m_settings::MeleeAimbot);
    m_settings::FloorHugger = config.value(XS("FloorHugger"), m_settings::FloorHugger);
    m_settings::HackableCrateTimer = config.value(XS("HackableCrateTimer"), m_settings::HackableCrateTimer);
    m_settings::AlwaysManipulate = config.value(XS("AlwaysManipulate"), m_settings::AlwaysManipulate);
    m_settings::PatrolHelicopter = config.value(XS("PatrolHelicopter"), m_settings::PatrolHelicopter);
    m_settings::DrawDistance = config.value(XS("DrawDistance"), m_settings::DrawDistance);
    m_settings::InteractiveDebug = config.value(XS("InteractiveDebug"), m_settings::InteractiveDebug);
    m_settings::HackableCrateFlags = config.value(XS("HackableCrateFlags"), m_settings::HackableCrateFlags);
    m_settings::InstantBullet = config.value(XS("InstantBullet"), m_settings::InstantBullet);
    m_settings::FixDebugCamera = config.value(XS("FixDebugCamera"), m_settings::FixDebugCamera);
    m_settings::SelectedChams = config.value(XS("SelectedChams"), m_settings::SelectedChams);
    m_settings::InstantKill = config.value(XS("InstantKill"), m_settings::InstantKill);
    m_settings::WaitForBulletTP = config.value(XS("WaitForBulletTP"), m_settings::WaitForBulletTP);
    m_settings::Target_Indicator = config.value(XS("Target_Indicator"), m_settings::Target_Indicator);
    m_settings::NormalFastBullet = config.value(XS("NormalFastBullet"), m_settings::NormalFastBullet);
    m_settings::NoWeaponBob = config.value(XS("NoWeaponBob"), m_settings::NoWeaponBob);
    m_settings::WeaponSpammer = config.value(XS("WeaponSpammer"), m_settings::WeaponSpammer);
    m_settings::WeaponSpamDelay = config.value(XS("WeaponSpamDelay"), m_settings::WeaponSpamDelay);
    m_settings::InteractiveKey = static_cast<RustStructs::KeyCode>(config.value(XS("InteractiveKey"), m_settings::InteractiveKey));
    m_settings::WeaponSpamKey = static_cast<RustStructs::KeyCode>(config.value(XS("WeaponSpamKey"), m_settings::WeaponSpamKey));
    m_settings::PierceMaterials = config.value(XS("PierceMaterials"), m_settings::PierceMaterials);
    m_settings::Crosshair = config.value(XS("Crosshair"), m_settings::Crosshair);
    m_settings::BaseCheck = config.value(XS("BaseCheck"), m_settings::BaseCheck);
    m_settings::BulletTracers = config.value(XS("BulletTracers"), m_settings::BulletTracers);
    m_settings::SelectedHitbox = config.value(XS("SelectedHitbox"), m_settings::SelectedHitbox);
    m_settings::BulletTPIntensity = config.value(XS("BulletTPIntensity"), m_settings::BulletTPIntensity);
    m_settings::AutoReload = config.value(XS("AutoReload"), m_settings::AutoReload);
    m_settings::HeliHitboxOverride = config.value(XS("HeliHitboxOverride"), m_settings::HeliHitboxOverride);
    m_settings::Aimline = config.value(XS("Aimline"), m_settings::Aimline);
    m_settings::HitboxOverride = config.value(XS("HitboxOverride"), m_settings::HitboxOverride);
    m_settings::reload_time = static_cast<int>(config.value(XS("reload_time"), m_settings::reload_time));
    m_settings::BulletTPRadius = static_cast<int>(config.value(XS("BulletTPRadius"), m_settings::BulletTPRadius));
    m_settings::OOFIndicators = config.value(XS("OOFIndicators"), m_settings::OOFIndicators);
    m_settings::AimMarker = config.value(XS("AimMarker"), m_settings::AimMarker);
    m_settings::DrawFov = config.value(XS("DrawFov"), m_settings::DrawFov);
    m_settings::TargetFriendList = config.value(XS("TargetFriendList"), m_settings::TargetFriendList);
    m_settings::InstantLoot = config.value(XS("InstantLoot"), m_settings::InstantLoot);
    // Repeat this for all your variables

    // Set variables from arrays
    if (config.find(XS("Fov_Color")) != config.end() && config[XS("Fov_Color")].is_array() && config[XS("Fov_Color")].size() == 4) {
        for (size_t i = 0; i < 4; ++i) {
            m_settings::Fov_Color[i] = static_cast<float>(config[XS("Fov_Color")][i]);
        }
    }

    // Load Crosshair_Color from JSON
    if (config.find(XS("Crosshair_Color")) != config.end() && config[XS("Crosshair_Color")].is_array() && config[XS("Crosshair_Color")].size() == 4) {
        for (size_t i = 0; i < 4; ++i) {
            m_settings::Crosshair_Color[i] = static_cast<float>(config[XS("Crosshair_Color")][i]);
        }
    }

    // Load DroppedItemColor from JSON
    if (config.find(XS("DroppedItemColor")) != config.end() && config[XS("DroppedItemColor")].is_array() && config[XS("DroppedItemColor")].size() == 4) {
        for (size_t i = 0; i < 4; ++i) {
            m_settings::DroppedItemColor[i] = static_cast<float>(config[XS("DroppedItemColor")][i]);
        }
    }

    // Load HempColor from JSON
    if (config.find(XS("HempColor")) != config.end() && config[XS("HempColor")].is_array() && config[XS("HempColor")].size() == 4) {
        for (size_t i = 0; i < 4; ++i) {
            m_settings::HempColor[i] = static_cast<float>(config[XS("HempColor")][i]);
        }
    }

    // Load the rest of the settings in a similar manner
    m_settings::AimbotAccuracy = static_cast<float>(config[XS("AimbotAccuracy")]);
    m_settings::ChangeRecoil = config[XS("ChangeRecoil")];
    m_settings::Thickbullet_Arrows = config[XS("Thickbullet_Arrows")];
    m_settings::BulletTP = config[XS("BulletTP")];
    m_settings::Manipulation = config[XS("Manipulation")];
    m_settings::StopPlayer = config[XS("StopPlayer")];
    m_settings::ManipFlags = config[XS("ManipFlags")];
    m_settings::BulletTPFlags = config[XS("BulletTPFlags")];
    m_settings::BlockServerCommands = config[XS("BlockServerCommands")];
    m_settings::Autoshoot = config[XS("Autoshoot")];
    m_settings::AlwaysAutoshoot = config[XS("AlwaysAutoshoot")];
    m_settings::NoSpread = config[XS("NoSpread")];
    m_settings::NoSway = config[XS("NoSway")];
    m_settings::OnHalfDesync = config[XS("OnHalfDesync")];
    m_settings::FastBullets = config[XS("FastBullets")];

    if (config.find(XS("BulletsSpeeds")) != config.end()) {
        m_settings::BulletsSpeeds = static_cast<int>(config[XS("BulletsSpeeds")]);
    }

    // Load SilentMelee from JSON
    if (config.find(XS("SilentMelee")) != config.end()) {
        m_settings::SilentMelee = config[XS("SilentMelee")];
    }

    // Load ManipKey from JSON
    if (config.find(XS("ManipKey")) != config.end()) {
        m_settings::ManipKey = static_cast<RustStructs::KeyCode>(config[XS("ManipKey")]);
    }

    // Load the rest of the settings in a similar manner
    m_settings::AddFriend = static_cast<RustStructs::KeyCode>(config[XS("AddFriend")]);
    m_settings::RemoveFriend = static_cast<RustStructs::KeyCode>(config[XS("RemoveFriend")]);
    m_settings::RemoveAllFriends = static_cast<RustStructs::KeyCode>(config[XS("RemoveAllFriends")]);
    m_settings::removefriend1 = config[XS("removefriend1")];
    m_settings::removefriend2 = config[XS("removefriend2")];
    m_settings::removefriend3 = config[XS("removefriend3")];
    m_settings::ForceAutomatic = config[XS("ForceAutomatic")];
    m_settings::LoadGalaxy = config[XS("LoadGalaxy")];
    m_settings::LoadLightning = config[XS("LoadLightning")];
    m_settings::LoadGeometric = config[XS("LoadGeometric")];
    m_settings::AutoshootKey = static_cast<RustStructs::KeyCode>(config[XS("AutoshootKey")]);
    m_settings::IncludeFatBullet = config[XS("IncludeFatBullet")];
   // m_settings::recoilPercent = config[XS("recoilPercent")];
   // m_settings::RecoilPercentY = config[XS("RecoilPercentY")];
    m_settings::AdminFlags = config[XS("AdminFlags")];
    m_settings::AdminCheat = config[XS("AdminCheat")];
    m_settings::AdminCheatKey = static_cast<RustStructs::KeyCode>(config[XS("AdminCheatKey")]);
    m_settings::SmallerLocalRadius = config[XS("SmallerLocalRadius")];
    m_settings::SpiderMan = config[XS("SpiderMan")];
    m_settings::InfiniteJump = config[XS("InfiniteJump")];
    m_settings::NoAttackRestrictions = config[XS("NoAttackRestrictions")];
    m_settings::AlwaysSprint = config[XS("AlwaysSprint")];
    m_settings::OmniSprint = config[XS("OmniSprint")];
    m_settings::InstantHeal = config[XS("InstantHeal")];
    m_settings::IgnoreTrees = config[XS("IgnoreTrees")];
    m_settings::RemoveAttackAnimations = config[XS("RemoveAttackAnimations")];

    m_settings::IgnorePlayers = config[XS("IgnorePlayers")];
    m_settings::InstantRevive = config[XS("InstantRevive")];
    m_settings::PlayerFov = config[XS("PlayerFov")];
    m_settings::PlayerFovAmount = static_cast<int>(config[XS("PlayerFovAmount")]);
    m_settings::Zoom = config[XS("Zoom")];
    m_settings::ZoomKey = static_cast<RustStructs::KeyCode>(config[XS("ZoomKey")]);
    m_settings::ZoomAmount = static_cast<int>(config[XS("ZoomAmount")]);
    m_settings::AutoFarmTree = config[XS("AutoFarmTree")];
    m_settings::AutoFarmOre = config[XS("AutoFarmOre")];
    m_settings::InstantReviveKey = static_cast<RustStructs::KeyCode>(config[XS("InstantReviveKey")]);
    m_settings::KeepTargetAlive = config[XS("KeepTargetAlive")];
    m_settings::KeepAliveKey = static_cast<RustStructs::KeyCode>(config[XS("KeepAliveKey")]);
    m_settings::Spinbot = config[XS("Spinbot")];
    m_settings::LootBodyThruWall = config[XS("LootBodyThruWall")];
    m_settings::LootBodyThruWallKey = static_cast<RustStructs::KeyCode>(config[XS("LootBodyThruWallKey")]);
    m_settings::LootCorpseThruWall = config[XS("LootCorpseThruWall")];
    m_settings::LootCorpseThruWallKey = static_cast<RustStructs::KeyCode>(config[XS("LootCorpseThruWallKey")]);
    m_settings::Stash = config[XS("Stash")];
    m_settings::Hemp = config[XS("Hemp")];

    if (config.find(XS("CollectablesIcon")) != config.end()) {
        m_settings::CollectablesIcon = config[XS("CollectablesIcon")];
    }

    // Load WaitForInstantHit from JSON
    if (config.find(XS("WaitForInstantHit")) != config.end()) {
        m_settings::WaitForInstantHit = config[XS("WaitForInstantHit")];
    }

    // Load ShowBulletTPAngle from JSON
    if (config.find(XS("ShowBulletTPAngle")) != config.end()) {
        m_settings::ShowBulletTPAngle = config[XS("ShowBulletTPAngle")];
    }

    // Load DroppedItems from JSON
    if (config.find(XS("DroppedItems")) != config.end()) {
        m_settings::DroppedItems = config[XS("DroppedItems")];
    }

    // Load DroppedItemColor from JSON (using the previously defined array)
    if (config.find(XS("DroppedItemColor")) != config.end()) {
        auto colorArray = config[XS("DroppedItemColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::DroppedItemColor[i] = colorArray[i];
            }
        }
    }


    if (config.find(XS("HempColor")) != config.end()) {
        auto colorArray = config[XS("HempColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::HempColor[i] = colorArray[i];
            }
        }
    }

    // Load dieselColorArray from JSON
    if (config.find(XS("DieselColor")) != config.end()) {
        auto colorArray = config[XS("DieselColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::DieselColor[i] = colorArray[i];
            }
        }
    }

    // Load stoneColorArray from JSON
    if (config.find(XS("StoneColor")) != config.end()) {
        auto colorArray = config[XS("StoneColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::StoneColor[i] = colorArray[i];
            }
        }
    }

    // Load metalColorArray from JSON
    if (config.find(XS("MetalColor")) != config.end()) {
        auto colorArray = config[XS("MetalColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::MetalColor[i] = colorArray[i];
            }
        }
    }

    // Load sulfurColorArray from JSON
    if (config.find(XS("SulfurColor")) != config.end()) {
        auto colorArray = config[XS("SulfurColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::SulfurColor[i] = colorArray[i];
            }
        }
    }


    // Load the remaining integer settings
    m_settings::MaxDroppedDistance = static_cast<int>(config[XS("MaxDroppedDistance")]);
    m_settings::MaxTrapsDistance = static_cast<int>(config[XS("MaxTrapsDistance")]);
    m_settings::MaxCrateDistance = static_cast<int>(config[XS("MaxCrateDistance")]);
    m_settings::MaxFoodDistance = static_cast<int>(config[XS("MaxFoodDistance")]);
    m_settings::MaxAPCDistance = static_cast<int>(config[XS("MaxAPCDistance")]);
    m_settings::MaxPlayerDropsDistance = static_cast<int>(config[XS("MaxPlayerDropsDistance")]);
    m_settings::MaxOreDistance = static_cast<int>(config[XS("MaxOreDistance")]);
    m_settings::MaxCollectableDistance = static_cast<int>(config[XS("MaxCollectableDistance")]);
    m_settings::IconsScale = static_cast<int>(config[XS("IconsScale")]);
    m_settings::WorldFontSize = static_cast<int>(config[XS("WorldFontSize")]);

    // Load FoodIcons from JSON
    m_settings::Mushroom = config[XS("Mushroom")];
    m_settings::Pumpkin = config[XS("Pumpkin")];
    m_settings::Corn = config[XS("Corn")];
    m_settings::Potato = config[XS("Potato")];
    m_settings::FoodIcons = config[XS("FoodIcons")];

    // Load AnimalIcons from JSON
    m_settings::Bear = config[XS("Bear")];
    m_settings::Wolf = config[XS("Wolf")];
    m_settings::Stag = config[XS("Stag")];
    m_settings::Boar = config[XS("Boar")];

    // Load DieselBarrel from JSON
    m_settings::DieselBarrel = config[XS("DieselBarrel")];
    m_settings::WorldFontSize = config[XS("WorldFontSize")];

    if (config.find(XS("MushRoomColor")) != config.end()) {
        auto colorArray = config[XS("MushRoomColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::MushRoomColor[i] = colorArray[i];
            }
        }
    }

    // Load PumpkinColor from JSON
    if (config.find(XS("PumpkinColor")) != config.end()) {
        auto colorArray = config[XS("PumpkinColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::PumpkinColor[i] = colorArray[i];
            }
        }
    }

    // Load CornColor from JSON
    if (config.find(XS("CornColor")) != config.end()) {
        auto colorArray = config[XS("CornColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::CornColor[i] = colorArray[i];
            }
        }
    }

    // Load PotatoColor from JSON
    if (config.find(XS("PotatoColor")) != config.end()) {
        auto colorArray = config[XS("PotatoColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::PotatoColor[i] = colorArray[i];
            }
        }
    }

    // Load CorpseColor from JSON
    if (config.find(XS("CorpseColor")) != config.end()) {
        auto colorArray = config[XS("CorpseColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::CorpseColor[i] = colorArray[i];
            }
        }
    }

    // Load BackPackColor from JSON
    if (config.find(XS("BackPackColor")) != config.end()) {
        auto colorArray = config[XS("BackPackColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::BackPackColor[i] = colorArray[i];
            }
        }
    }

    // Load TurretColor from JSON
    if (config.find(XS("TurretColor")) != config.end()) {
        auto colorArray = config[XS("TurretColor")];
        if (colorArray.is_array() && colorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::TurretColor[i] = colorArray[i];
            }
        }
    }

    if (config.find(XS("AutoTurret")) != config.end()) {
        m_settings::AutoTurret = config[XS("AutoTurret")];
    }

    // Load HackableCrate from JSON
    if (config.find(XS("HackableCrate")) != config.end()) {
        m_settings::HackableCrate = config[XS("HackableCrate")];
    }

    // Load BradleyCrate from JSON
    if (config.find(XS("BradleyCrate")) != config.end()) {
        m_settings::BradleyCrate = config[XS("BradleyCrate")];
    }

    // Load HeliCrate from JSON
    if (config.find(XS("HeliCrate")) != config.end()) {
        m_settings::HeliCrate = config[XS("HeliCrate")];
    }

    // Load TurretRange from JSON
    if (config.find(XS("TurretRange")) != config.end()) {
        m_settings::TurretRange = config[XS("TurretRange")];
    }
    if (config.find(XS("TurretOnFlags")) != config.end()) {
        m_settings::TurretOnFlags = config[XS("TurretOnFlags")];
    }
    // Load TurretAuthorizedPlayers from JSON
    if (config.find(XS("TurretAuthorizedPlayers")) != config.end()) {
        m_settings::TurretAuthorizedPlayers = config[XS("TurretAuthorizedPlayers")];
    }

    // Load TurretTurningFlag from JSON
    if (config.find(XS("TurretTurningFlag")) != config.end()) {
        m_settings::TurretTurningFlag = config[XS("TurretTurningFlag")];
    }

    // Load TurretEquippedFlags from JSON
    if (config.find(XS("TurretEquippedFlags")) != config.end()) {
        m_settings::TurretEquippedFlags = config[XS("TurretEquippedFlags")];
    }

    // Load TurretHealth from JSON
    if (config.find(XS("TurretHealth")) != config.end()) {
        m_settings::TurretHealth = config[XS("TurretHealth")];
    }

    // Load CrateColor from JSON
    if (config.find(XS("CrateColor")) != config.end()) {
        auto crateColorArray = config[XS("CrateColor")];
        if (crateColorArray.is_array() && crateColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::CrateColor[i] = crateColorArray[i];
            }
        }
    }

    // Load HeliColor from JSON
    if (config.find(XS("HeliColor")) != config.end()) {
        auto heliColorArray = config[XS("HeliColor")];
        if (heliColorArray.is_array() && heliColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::HeliColor[i] = heliColorArray[i];
            }
        }
    }

    // Load SavePos from JSON
    if (config.find(XS("SavePos")) != config.end()) {
        m_settings::SavePos = config[XS("SavePos")];
    }

    // Load SavePosKey from JSON
    if (config.find(XS("SavePosKey")) != config.end()) {
        m_settings::SavePosKey = config[XS("SavePosKey")];
    }

    // Load nameEsp from JSON
    if (config.find(XS("nameEsp")) != config.end()) {
        m_settings::nameEsp = config[XS("nameEsp")];
    }

    // Load BoxEsp from JSON
    if (config.find(XS("BoxEsp")) != config.end()) {
        m_settings::BoxEsp = config[XS("BoxEsp")];
    }

    if (config.find(XS("DisableHitSounds")) != config.end()) {
        m_settings::DisableHitSounds = config[XS("DisableHitSounds")];
    }

    if (config.find(XS("CustomHitSounds")) != config.end()) {
        m_settings::CustomHitSounds = config[XS("CustomHitSounds")];
    }


    // Load Swastika from JSON
    if (config.find(XS("Swastika")) != config.end()) {
        m_settings::Swastika = config[XS("Swastika")];
    }

    // Load SwastikaSpeed from JSON
    if (config.find(XS("SwastikaSpeed")) != config.end()) {
        m_settings::SwastikaSpeed = config[XS("SwastikaSpeed")];
    }

    // Load SwastikaSize from JSON
    if (config.find(XS("SwastikaSize")) != config.end()) {
        m_settings::SwastikaSize = config[XS("SwastikaSize")];
    }

    // Load CornerBox from JSON
    if (config.find(XS("CornerBox")) != config.end()) {
        m_settings::CornerBox = config[XS("CornerBox")];
    }

    // Load healthBar from JSON
    if (config.find(XS("healthBar")) != config.end()) {
        m_settings::healthBar = config[XS("healthBar")];
    }

    // Load Skeleton from JSON
    if (config.find(XS("Skeleton")) != config.end()) {
        m_settings::Skeleton = config[XS("Skeleton")];
    }

    // Load helditem from JSON
    if (config.find(XS("helditem")) != config.end()) {
        m_settings::helditem = config[XS("helditem")];
    }

    // Load EspVisCheck from JSON
    if (config.find(XS("EspVisCheck")) != config.end()) {
        m_settings::EspVisCheck = config[XS("EspVisCheck")];
    }

    // Load DrawBox_Color from JSON
    if (config.find(XS("DrawBox_Color")) != config.end()) {
        auto drawBoxColorArray = config[XS("DrawBox_Color")];
        if (drawBoxColorArray.is_array() && drawBoxColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::DrawBox_Color[i] = drawBoxColorArray[i];
            }
        }
    }

    // Load VisCheck_Color from JSON
    if (config.find(XS("VisCheck_Color")) != config.end()) {
        auto visCheckColorArray = config[XS("VisCheck_Color")];
        if (visCheckColorArray.is_array() && visCheckColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::VisCheck_Color[i] = visCheckColorArray[i];
            }
        }
    }

    // Load DrawNameTag_Color from JSON
    if (config.find(XS("DrawNameTag_Color")) != config.end()) {
        auto drawNameTagColorArray = config[XS("DrawNameTag_Color")];
        if (drawNameTagColorArray.is_array() && drawNameTagColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::DrawNameTag_Color[i] = drawNameTagColorArray[i];
            }
        }
    }

    // Load DrawHeldItem_Color from JSON
    if (config.find(XS("DrawHeldItem_Color")) != config.end()) {
        auto drawHeldItemColorArray = config[XS("DrawHeldItem_Color")];
        if (drawHeldItemColorArray.is_array() && drawHeldItemColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::DrawHeldItem_Color[i] = drawHeldItemColorArray[i];
            }
        }
    }

    // Load Friend_Color from JSON
    if (config.find(XS("Friend_Color")) != config.end()) {
        auto friendColorArray = config[XS("Friend_Color")];
        if (friendColorArray.is_array() && friendColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Friend_Color[i] = friendColorArray[i];
            }
        }
    }

    // Load Wounded_Color from JSON
    if (config.find(XS("Wounded_Color")) != config.end()) {
        auto woundedColorArray = config[XS("Wounded_Color")];
        if (woundedColorArray.is_array() && woundedColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Wounded_Color[i] = woundedColorArray[i];
            }
        }
    }

    // Load Scientist_color from JSON
    if (config.find(XS("Scientist_color")) != config.end()) {
        auto scientistColorArray = config[XS("Scientist_color")];
        if (scientistColorArray.is_array() && scientistColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Scientist_color[i] = scientistColorArray[i];
            }
        }
    }

    // Load Dead_Color from JSON
    if (config.find(XS("Dead_Color")) != config.end()) {
        auto deadColorArray = config[XS("Dead_Color")];
        if (deadColorArray.is_array() && deadColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Dead_Color[i] = deadColorArray[i];
            }
        }
    }

    // Load Safezone_Color from JSON
    if (config.find(XS("Safezone_Color")) != config.end()) {
        auto safezoneColorArray = config[XS("Safezone_Color")];
        if (safezoneColorArray.is_array() && safezoneColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Safezone_Color[i] = safezoneColorArray[i];
            }
        }
    }

    // Load Target_Color from JSON
    if (config.find(XS("Target_Color")) != config.end()) {
        auto targetColorArray = config[XS("Target_Color")];
        if (targetColorArray.is_array() && targetColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Target_Color[i] = targetColorArray[i];
            }
        }
    }

    // Load fontsize from JSON
    if (config.find(XS("fontsize")) != config.end()) {
        m_settings::fontsize = config[XS("fontsize")];
    }

    // Load TagsVisCheck from JSON
    if (config.find(XS("TagsVisCheck")) != config.end()) {
        m_settings::TagsVisCheck = config[XS("TagsVisCheck")];
    }

    // Load DrawNPC from JSON
    if (config.find(XS("DrawNPC")) != config.end()) {
        m_settings::DrawNPC = config[XS("DrawNPC")];
    }

    // Load NPCDistance from JSON
    if (config.find(XS("NPCDistance")) != config.end()) {
        m_settings::NPCDistance = config[XS("NPCDistance")];
    }

    // Load DrawDead from JSON
    if (config.find(XS("DrawDead")) != config.end()) {
        m_settings::DrawDead = config[XS("DrawDead")];
    }

    // Load DrawAis from JSON
    if (config.find(XS("DrawAis")) != config.end()) {
        m_settings::DrawAis = config[XS("DrawAis")];
    }

    // Load DrawSleepers from JSON
    if (config.find(XS("DrawSleepers")) != config.end()) {
        m_settings::DrawSleepers = config[XS("DrawSleepers")];
    }

    // Load Sleeper_Color from JSON
    if (config.find(XS("Sleeper_Color")) != config.end()) {
        auto sleeperColorArray = config[XS("Sleeper_Color")];
        if (sleeperColorArray.is_array() && sleeperColorArray.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                m_settings::Sleeper_Color[i] = sleeperColorArray[i];
            }
        }
    }

    // Load DrawWounded from JSON
    if (config.find(XS("DrawWounded")) != config.end()) {
        m_settings::DrawWounded = config[XS("DrawWounded")];
    }

    // Load DrawTarget from JSON
    if (config.find(XS("DrawTarget")) != config.end()) {
        m_settings::DrawTarget = config[XS("DrawTarget")];
    }

    // Load DrawSafezone from JSON
    if (config.find(XS("DrawSafezone")) != config.end()) {
        m_settings::DrawSafezone = config[XS("DrawSafezone")];
    }

    // Load PlayerESPDistance from JSON
    if (config.find(XS("PlayerESPDistance")) != config.end()) {
        m_settings::PlayerESPDistance = config[XS("PlayerESPDistance")];
    }

    // Load Flyhack_Indicator from JSON
    if (config.find(XS("Flyhack_Indicator")) != config.end()) {
        m_settings::Flyhack_Indicator = config[XS("Flyhack_Indicator")];
    }

    // Load AntiFlyKick from JSON
    if (config.find(XS("AntiFlyKick")) != config.end()) {
        m_settings::AntiFlyKick = config[XS("AntiFlyKick")];
    }

    // Load Brightnight from JSON
    if (config.find(XS("Brightnight")) != config.end()) {
        m_settings::Brightnight = config[XS("Brightnight")];
    }

    // Load Stars from JSON
    if (config.find(XS("Stars")) != config.end()) {
        m_settings::Stars = config[XS("Stars")];
    }

    // Load BrightCave from JSON
    if (config.find(XS("BrightCave")) != config.end()) {
        m_settings::BrightCave = config[XS("BrightCave")];
    }

    // Load TimeChanger from JSON
    if (config.find(XS("TimeChanger")) != config.end()) {
        m_settings::TimeChanger = config[XS("TimeChanger")];
    }

    // Load GameTime from JSON
    if (config.find(XS("GameTime")) != config.end()) {
        m_settings::GameTime = config[XS("GameTime")];
    }

    // Load RemoveUnderwaterEffects from JSON
    if (config.find(XS("RemoveUnderwaterEffects")) != config.end()) {
        m_settings::RemoveUnderwaterEffects = config[XS("RemoveUnderwaterEffects")];
    }

    config.clear();

    const auto string = std::wstring(XS(L"[Serotonin] Loaded Config!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}


void Configs::SaveConfig()
{

    json config;
    config[XS("SilentAim")] = m_settings::SilentAim;
    config[XS("PlayerChams")] = m_settings::PlayerChams;
    config[XS("NoMovementRestrictions")] = m_settings::NoMovementRestrictions;
    config[XS("AimbotFOV")] = static_cast<int>(m_settings::AimbotFOV);
    config[XS("TestSlider")] = static_cast<int>(m_settings::TestSlider);
    config[XS("NormalThickBullet")] = m_settings::NormalThickBullet;
    config[XS("DrawInventory")] = m_settings::DrawInventory;
    config[XS("DrawClothing")] = m_settings::DrawClothing;
    config[XS("DrawInventoryIcons")] = m_settings::DrawInventoryIcons;
    config[XS("DrawClothingIcons")] = m_settings::DrawClothingIcons;
    config[XS("NormalThickBulletThickness")] = static_cast<int>(m_settings::NormalThickBulletThickness);
    config[XS("AimbotNPC")] = m_settings::AimbotNPC;
    config[XS("HeliAimbot")] = m_settings::HeliAimbot;
    config[XS("InstantEoka")] = m_settings::InstantEoka;
    config[XS("HitMaterial")] = m_settings::HitMaterial;

    config[XS("TargetWounded")] = m_settings::TargetWounded;
    config[XS("ShowUsers")] = m_settings::ShowUsers;
    config[XS("SelectedAimbone")] = m_settings::SelectedAimbone;
    config[XS("MeleeAimbot")] = m_settings::MeleeAimbot;
    config[XS("FloorHugger")] = m_settings::FloorHugger;
    config[XS("HackableCrateTimer")] = m_settings::HackableCrateTimer;
    config[XS("AlwaysManipulate")] = m_settings::AlwaysManipulate;
    config[XS("PatrolHelicopter")] = m_settings::PatrolHelicopter;
    config[XS("DrawDistance")] = m_settings::DrawDistance;
    config[XS("InteractiveDebug")] = m_settings::InteractiveDebug;
    config[XS("HackableCrateFlags")] = m_settings::HackableCrateFlags;
    config[XS("InstantBullet")] = m_settings::InstantBullet;
    config[XS("FixDebugCamera")] = m_settings::FixDebugCamera;
    config[XS("SelectedChams")] = m_settings::SelectedChams;
    config[XS("InstantKill")] = m_settings::InstantKill;
    config[XS("WaitForBulletTP")] = m_settings::WaitForBulletTP;
    config[XS("Target_Indicator")] = m_settings::Target_Indicator;
    config[XS("NormalFastBullet")] = m_settings::NormalFastBullet;
    config[XS("NoWeaponBob")] = m_settings::NoWeaponBob;
    config[XS("WeaponSpammer")] = m_settings::WeaponSpammer;
    config[XS("WeaponSpamDelay")] = static_cast<int>(m_settings::WeaponSpamDelay);
    config[XS("InteractiveKey")] = static_cast<int>(m_settings::InteractiveKey);
    config[XS("WeaponSpamKey")] = static_cast<int>(m_settings::WeaponSpamKey);
    config[XS("PierceMaterials")] = m_settings::PierceMaterials;
    config[XS("Crosshair")] = m_settings::Crosshair;
    config[XS("BaseCheck")] = m_settings::BaseCheck;
    config[XS("BulletTracers")] = m_settings::BulletTracers;
    config[XS("SelectedHitbox")] = m_settings::SelectedHitbox;
    config[XS("BulletTPIntensity")] = m_settings::BulletTPIntensity;
    config[XS("AutoReload")] = m_settings::AutoReload;
    config[XS("HeliHitboxOverride")] = m_settings::HeliHitboxOverride;
    config[XS("Aimline")] = m_settings::Aimline;
    config[XS("HitboxOverride")] = m_settings::HitboxOverride;
    config[XS("reload_time")] = static_cast<int>(m_settings::reload_time);
    config[XS("BulletTPRadius")] = static_cast<int>(m_settings::BulletTPRadius);
    config[XS("OOFIndicators")] = m_settings::OOFIndicators;
    config[XS("AimMarker")] = m_settings::AimMarker;
    config[XS("DrawFov")] = m_settings::DrawFov;
    config[XS("TargetFriendList")] = m_settings::TargetFriendList;
    config[XS("InstantLoot")] = m_settings::InstantLoot;

    json fovColorArray = json::array();
    fovColorArray.push_back(static_cast<int>(m_settings::Fov_Color[0]));
    fovColorArray.push_back(static_cast<int>(m_settings::Fov_Color[1]));
    fovColorArray.push_back(static_cast<int>(m_settings::Fov_Color[2]));
    fovColorArray.push_back(static_cast<int>(m_settings::Fov_Color[3]));

    config[XS("Fov_Color")] = fovColorArray;
    json crossHairColorArray = json::array();
    crossHairColorArray.push_back(static_cast<int>(m_settings::Crosshair_Color[0]));
    crossHairColorArray.push_back(static_cast<int>(m_settings::Crosshair_Color[1]));
    crossHairColorArray.push_back(static_cast<int>(m_settings::Crosshair_Color[2]));
    crossHairColorArray.push_back(static_cast<int>(m_settings::Crosshair_Color[3]));
    config[XS("Crosshair_Color")] = crossHairColorArray;

    json droppedItemColorArray = {
         static_cast<int>(m_settings::DroppedItemColor[0]),
         static_cast<int>(m_settings::DroppedItemColor[1]),
         static_cast<int>(m_settings::DroppedItemColor[2]),
         static_cast<int>(m_settings::DroppedItemColor[3])
    };

    json hempColorArray = {
        static_cast<int>(m_settings::HempColor[0]),
        static_cast<int>(m_settings::HempColor[1]),
        static_cast<int>(m_settings::HempColor[2]),
        static_cast<int>(m_settings::HempColor[3])
    };

    json dieselColorArray = {
        static_cast<int>(m_settings::DieselColor[0]),
        static_cast<int>(m_settings::DieselColor[1]),
        static_cast<int>(m_settings::DieselColor[2]),
        static_cast<int>(m_settings::DieselColor[3])
    };

    json stoneColorArray = {
        static_cast<int>(m_settings::StoneColor[0]),
        static_cast<int>(m_settings::StoneColor[1]),
        static_cast<int>(m_settings::StoneColor[2]),
        static_cast<int>(m_settings::StoneColor[3])
    };

    json metalColorArray = {
        static_cast<int>(m_settings::MetalColor[0]),
        static_cast<int>(m_settings::MetalColor[1]),
        static_cast<int>(m_settings::MetalColor[2]),
        static_cast<int>(m_settings::MetalColor[3])
    };

    json sulfurColorArray = {
        static_cast<int>(m_settings::SulfurColor[0]),
        static_cast<int>(m_settings::SulfurColor[1]),
        static_cast<int>(m_settings::SulfurColor[2]),
        static_cast<int>(m_settings::SulfurColor[3])
    };


    config[XS("AimbotAccuracy")] = static_cast<int>(m_settings::AimbotAccuracy);
    config[XS("ChangeRecoil")] = m_settings::ChangeRecoil;
    config[XS("Thickbullet_Arrows")] = m_settings::Thickbullet_Arrows;
    config[XS("BulletTP")] = m_settings::BulletTP;
    config[XS("Manipulation")] = m_settings::Manipulation;
    config[XS("StopPlayer")] = m_settings::StopPlayer;
    config[XS("ManipFlags")] = m_settings::ManipFlags;
    config[XS("BulletTPFlags")] = m_settings::BulletTPFlags;
    config[XS("BlockServerCommands")] = m_settings::BlockServerCommands;
    config[XS("Autoshoot")] = m_settings::Autoshoot;
    config[XS("AlwaysAutoshoot")] = m_settings::AlwaysAutoshoot;
    config[XS("NoSpread")] = m_settings::NoSpread;
    config[XS("NoSway")] = m_settings::NoSway;
    config[XS("OnHalfDesync")] = m_settings::OnHalfDesync;
    config[XS("FastBullets")] = m_settings::FastBullets;
    config[XS("BulletsSpeeds")] = static_cast<int>(m_settings::BulletsSpeeds);
    config[XS("SilentMelee")] = m_settings::SilentMelee;
    config[XS("ManipKey")] = static_cast<int>(m_settings::ManipKey);
    config[XS("AddFriend")] = static_cast<int>(m_settings::AddFriend);
    config[XS("RemoveFriend")] = static_cast<int>(m_settings::RemoveFriend);
    config[XS("RemoveAllFriends")] = static_cast<int>(m_settings::RemoveAllFriends);
    config[XS("removefriend1")] = m_settings::removefriend1;
    config[XS("removefriend2")] = m_settings::removefriend2;
    config[XS("removefriend3")] = m_settings::removefriend3;
    config[XS("ForceAutomatic")] = m_settings::ForceAutomatic;
    config[XS("LoadGalaxy")] = m_settings::LoadGalaxy;
    config[XS("LoadLightning")] = m_settings::LoadLightning;
    config[XS("LoadGeometric")] = m_settings::LoadGeometric;
    config[XS("AutoshootKey")] = static_cast<int>(m_settings::AutoshootKey);
    config[XS("IncludeFatBullet")] = m_settings::IncludeFatBullet;
   // config[XS("recoilPercent")] = m_settings::recoilPercent;
   // config[XS("RecoilPercentY")] = m_settings::RecoilPercentY;
    config[XS("AdminFlags")] = m_settings::AdminFlags;
    config[XS("AdminCheat")] = m_settings::AdminCheat;
    config[XS("AdminCheatKey")] = static_cast<int>(m_settings::AdminCheatKey);
    config[XS("SmallerLocalRadius")] = m_settings::SmallerLocalRadius;
    config[XS("SpiderMan")] = m_settings::SpiderMan;
    config[XS("InfiniteJump")] = m_settings::InfiniteJump;
    config[XS("NoAttackRestrictions")] = m_settings::NoAttackRestrictions;
    config[XS("AlwaysSprint")] = m_settings::AlwaysSprint;
    config[XS("OmniSprint")] = m_settings::OmniSprint;
    config[XS("InstantHeal")] = m_settings::InstantHeal;
    config[XS("IgnoreTrees")] = m_settings::IgnoreTrees;
    config[XS("RemoveAttackAnimations")] = m_settings::RemoveAttackAnimations;

    config[XS("IgnorePlayers")] = m_settings::IgnorePlayers;
    config[XS("InstantRevive")] = m_settings::InstantRevive;
    config[XS("PlayerFov")] = m_settings::PlayerFov;
    config[XS("PlayerFovAmount")] = static_cast<int>(m_settings::PlayerFovAmount);
    config[XS("Zoom")] = m_settings::Zoom;
    config[XS("ZoomKey")] = static_cast<int>(m_settings::ZoomKey);
    config[XS("ZoomAmount")] = static_cast<int>(m_settings::ZoomAmount);
    config[XS("AutoFarmTree")] = m_settings::AutoFarmTree;
    config[XS("AutoFarmOre")] = m_settings::AutoFarmOre;
    config[XS("InstantReviveKey")] = static_cast<int>(m_settings::InstantReviveKey);
    config[XS("KeepTargetAlive")] = m_settings::KeepTargetAlive;
    config[XS("KeepAliveKey")] = static_cast<int>(m_settings::KeepAliveKey);
    config[XS("Spinbot")] = m_settings::Spinbot;
    config[XS("LootBodyThruWall")] = m_settings::LootBodyThruWall;
    config[XS("LootBodyThruWallKey")] = static_cast<int>(m_settings::LootBodyThruWallKey);
    config[XS("LootCorpseThruWall")] = m_settings::LootCorpseThruWall;
    config[XS("LootCorpseThruWallKey")] = static_cast<int>(m_settings::LootCorpseThruWallKey);
    config[XS("Stash")] = m_settings::Stash;
    config[XS("Hemp")] = m_settings::Hemp;
    config[XS("CollectablesIcon")] = m_settings::CollectablesIcon;
    config[XS("WaitForInstantHit")] = m_settings::WaitForInstantHit;
    config[XS("ShowBulletTPAngle")] = m_settings::ShowBulletTPAngle;
    config[XS("DroppedItems")] = m_settings::DroppedItems;
    config[XS("DroppedItemColor")] = droppedItemColorArray;  // Use the previously defined array
    config[XS("HempColor")] = hempColorArray;  // Use the previously defined array
    config[XS("DieselColor")] = dieselColorArray;  // Use the previously defined array
    config[XS("StoneColor")] = stoneColorArray;  // Use the previously defined array
    config[XS("MetalColor")] = metalColorArray;  // Use the previously defined array
    config[XS("SulfurColor")] = sulfurColorArray;  // Use the previously defined array
    config[XS("MaxDroppedDistance")] = static_cast<int>(m_settings::MaxDroppedDistance);
    config[XS("MaxTrapsDistance")] = static_cast<int>(m_settings::MaxTrapsDistance);
    config[XS("MaxCrateDistance")] = static_cast<int>(m_settings::MaxCrateDistance);
    config[XS("MaxFoodDistance")] = static_cast<int>(m_settings::MaxFoodDistance);
    config[XS("MaxAPCDistance")] = static_cast<int>(m_settings::MaxAPCDistance);
    config[XS("MaxPlayerDropsDistance")] = static_cast<int>(m_settings::MaxPlayerDropsDistance);
    config[XS("StoneOre")] = m_settings::StoneOre;
    config[XS("MetalOre")] = m_settings::MetalOre;
    config[XS("SulfurOre")] = m_settings::SulfurOre;
    config[XS("OreIcons")] = m_settings::OreIcons;
    config[XS("MaxOreDistance")] = static_cast<int>(m_settings::MaxOreDistance);
    config[XS("MaxCollectableDistance")] = static_cast<int>(m_settings::MaxCollectableDistance);
    config[XS("IconsScale")] = static_cast<int>(m_settings::IconsScale);

    config[XS("Mushroom")] = m_settings::Mushroom;
    config[XS("Pumpkin")] = m_settings::Pumpkin;
    config[XS("Corn")] = m_settings::Corn;
    config[XS("Potato")] = m_settings::Potato;
    config[XS("FoodIcons")] = m_settings::FoodIcons;

    config[XS("Bear")] = m_settings::Bear;
    config[XS("Wolf")] = m_settings::Wolf;
    config[XS("Stag")] = m_settings::Stag;
    config[XS("Boar")] = m_settings::Boar;

    config[XS("DieselBarrel")] = m_settings::DieselBarrel;
    config[XS("WorldFontSize")] = static_cast<int>(m_settings::WorldFontSize);

    json mushRoomColorArray = {
        static_cast<int>(m_settings::MushRoomColor[0]),
        static_cast<int>(m_settings::MushRoomColor[1]),
        static_cast<int>(m_settings::MushRoomColor[2]),
        static_cast<int>(m_settings::MushRoomColor[3])
    };

    json pumpkinColorArray = {
       static_cast<int>(m_settings::PumpkinColor[0]),
       static_cast<int>(m_settings::PumpkinColor[1]),
       static_cast<int>(m_settings::PumpkinColor[2]),
       static_cast<int>(m_settings::PumpkinColor[3])
    };

    json cornColorArray = {
         static_cast<int>(m_settings::CornColor[0]),
        static_cast<int>(m_settings::CornColor[1]),
        static_cast<int>(m_settings::CornColor[2]),
         static_cast<int>(m_settings::CornColor[3])
    };

    json potatoColorArray = {
         static_cast<int>(m_settings::PotatoColor[0]),
        static_cast<int>(m_settings::PotatoColor[1]),
        static_cast<int>(m_settings::PotatoColor[2]),
         static_cast<int>(m_settings::PotatoColor[3])
    };

    config[XS("MushRoomColor")] = mushRoomColorArray;  // Use the previously defined array
    config[XS("PumpkinColor")] = pumpkinColorArray;  // Use the previously defined array
    config[XS("CornColor")] = cornColorArray;  // Use the previously defined array
    config[XS("PotatoColor")] = potatoColorArray;  // Use the previously defined array

    config[XS("Corpse")] = m_settings::Corpse;
    config[XS("BackPack")] = m_settings::BackPack;

    json corpseColorArray = {
        static_cast<int>(m_settings::CorpseColor[0]),
        static_cast<int>(m_settings::CorpseColor[1]),
        static_cast<int>(m_settings::CorpseColor[2]),
        static_cast<int>(m_settings::CorpseColor[3])
    };
    json backPackColorArray = {
     static_cast<int>(m_settings::BackPackColor[0]),
     static_cast<int>(m_settings::BackPackColor[1]),
     static_cast<int>(m_settings::BackPackColor[2]),
     static_cast<int>(m_settings::BackPackColor[3])
    };

    json turretColorArray = {
       static_cast<int>(m_settings::TurretColor[0]),
       static_cast<int>(m_settings::TurretColor[1]),
       static_cast<int>(m_settings::TurretColor[2]),
       static_cast<int>(m_settings::TurretColor[3])
    };

    config[XS("CorpseColor")] = corpseColorArray;  // Use the previously defined array
    config[XS("BackPackColor")] = backPackColorArray;  // Use the previously defined array

    config[XS("AutoTurret")] = m_settings::AutoTurret;
    config[XS("HackableCrate")] = m_settings::HackableCrate;
    config[XS("BradleyCrate")] = m_settings::BradleyCrate;
    config[XS("HeliCrate")] = m_settings::HeliCrate;
    config[XS("TurretRange")] = m_settings::TurretRange;
    config[XS("TurretOnFlags")] = m_settings::TurretOnFlags;
    config[XS("TurretAuthorizedPlayers")] = m_settings::TurretAuthorizedPlayers;
    config[XS("TurretTurningFlag")] = m_settings::TurretTurningFlag;
    config[XS("TurretEquippedFlags")] = m_settings::TurretEquippedFlags;
    config[XS("TurretHealth")] = m_settings::TurretHealth;
    config[XS("TurretColor")] = turretColorArray;  // Use the previously defined array

    json crateColorArray = {
      static_cast<int>(m_settings::CrateColor[0]),
      static_cast<int>(m_settings::CrateColor[1]),
      static_cast<int>(m_settings::CrateColor[2]),
      static_cast<int>(m_settings::CrateColor[3])
    };

    json heliColorArray = {
   static_cast<int>(m_settings::HeliColor[0]),
   static_cast<int>(m_settings::HeliColor[1]),
   static_cast<int>(m_settings::HeliColor[2]),
   static_cast<int>(m_settings::HeliColor[3])
    };

    config[XS("CrateColor")] = crateColorArray;  // Use the previously defined array
    config[XS("HeliColor")] = heliColorArray;  // Use the previously defined array
    config[XS("SavePos")] = m_settings::SavePos;
    config[XS("SavePosKey")] = static_cast<int>(m_settings::SavePosKey);

    config[XS("nameEsp")] = m_settings::nameEsp;
    config[XS("BoxEsp")] = m_settings::BoxEsp;
    config[XS("Swastika")] = m_settings::Swastika;
    config[XS("SwastikaSpeed")] = static_cast<int>(m_settings::SwastikaSpeed);
    config[XS("SwastikaSize")] = static_cast<int>(m_settings::SwastikaSize);

    config[XS("CustomHitSounds")] = m_settings::CustomHitSounds;
    config[XS("DisableHitSounds")] = m_settings::DisableHitSounds;


    config[XS("CornerBox")] = m_settings::CornerBox;
    config[XS("healthBar")] = m_settings::healthBar;
    config[XS("Skeleton")] = m_settings::Skeleton;
    config[XS("helditem")] = m_settings::helditem;
    config[XS("EspVisCheck")] = m_settings::EspVisCheck;

    json drawBoxColorArray = json::array();
    drawBoxColorArray.push_back(static_cast<int>(m_settings::DrawBox_Color[0]));
    drawBoxColorArray.push_back(static_cast<int>(m_settings::DrawBox_Color[1]));
    drawBoxColorArray.push_back(static_cast<int>(m_settings::DrawBox_Color[2]));
    drawBoxColorArray.push_back(static_cast<int>(m_settings::DrawBox_Color[3]));
    config[XS("DrawBox_Color")] = drawBoxColorArray;

    json visCheckColorArray = json::array();
    visCheckColorArray.push_back(static_cast<int>(m_settings::VisCheck_Color[0]));
    visCheckColorArray.push_back(static_cast<int>(m_settings::VisCheck_Color[1]));
    visCheckColorArray.push_back(static_cast<int>(m_settings::VisCheck_Color[2]));
    visCheckColorArray.push_back(static_cast<int>(m_settings::VisCheck_Color[3]));
    config[XS("VisCheck_Color")] = visCheckColorArray;

    json drawNameTagColorArray = json::array();
    drawNameTagColorArray.push_back(static_cast<int>(m_settings::DrawNameTag_Color[0]));
    drawNameTagColorArray.push_back(static_cast<int>(m_settings::DrawNameTag_Color[1]));
    drawNameTagColorArray.push_back(static_cast<int>(m_settings::DrawNameTag_Color[2]));
    drawNameTagColorArray.push_back(static_cast<int>(m_settings::DrawNameTag_Color[3]));
    config[XS("DrawNameTag_Color")] = drawNameTagColorArray;

    json drawHeldItemColorArray = json::array();
    drawHeldItemColorArray.push_back(static_cast<int>(m_settings::DrawHeldItem_Color[0]));
    drawHeldItemColorArray.push_back(static_cast<int>(m_settings::DrawHeldItem_Color[1]));
    drawHeldItemColorArray.push_back(static_cast<int>(m_settings::DrawHeldItem_Color[2]));
    drawHeldItemColorArray.push_back(static_cast<int>(m_settings::DrawHeldItem_Color[3]));
    config[XS("DrawHeldItem_Color")] = drawHeldItemColorArray;

    json friendColorArray = json::array();
    friendColorArray.push_back(static_cast<int>(m_settings::Friend_Color[0]));
    friendColorArray.push_back(static_cast<int>(m_settings::Friend_Color[1]));
    friendColorArray.push_back(static_cast<int>(m_settings::Friend_Color[2]));
    friendColorArray.push_back(static_cast<int>(m_settings::Friend_Color[3]));
    config[XS("Friend_Color")] = friendColorArray;

    json woundedColorArray = json::array();
    woundedColorArray.push_back(static_cast<int>(m_settings::Wounded_Color[0]));
    woundedColorArray.push_back(static_cast<int>(m_settings::Wounded_Color[1]));
    woundedColorArray.push_back(static_cast<int>(m_settings::Wounded_Color[2]));
    woundedColorArray.push_back(static_cast<int>(m_settings::Wounded_Color[3]));
    config[XS("Wounded_Color")] = woundedColorArray;

    json scientistColorArray = json::array();
    scientistColorArray.push_back(static_cast<int>(m_settings::Scientist_color[0]));
    scientistColorArray.push_back(static_cast<int>(m_settings::Scientist_color[1]));
    scientistColorArray.push_back(static_cast<int>(m_settings::Scientist_color[2]));
    scientistColorArray.push_back(static_cast<int>(m_settings::Scientist_color[3]));
    config[XS("Scientist_color")] = scientistColorArray;

    json deadColorArray = json::array();
    deadColorArray.push_back(static_cast<int>(m_settings::Dead_Color[0]));
    deadColorArray.push_back(static_cast<int>(m_settings::Dead_Color[1]));
    deadColorArray.push_back(static_cast<int>(m_settings::Dead_Color[2]));
    deadColorArray.push_back(static_cast<int>(m_settings::Dead_Color[3]));
    config[XS("Dead_Color")] = deadColorArray;

    json safezoneColorArray = json::array();
    safezoneColorArray.push_back(static_cast<int>(m_settings::Safezone_Color[0]));
    safezoneColorArray.push_back(static_cast<int>(m_settings::Safezone_Color[1]));
    safezoneColorArray.push_back(static_cast<int>(m_settings::Safezone_Color[2]));
    safezoneColorArray.push_back(static_cast<int>(m_settings::Safezone_Color[3]));
    config[XS("Safezone_Color")] = safezoneColorArray;

    json targetColorArray = json::array();
    targetColorArray.push_back(static_cast<int>(m_settings::Target_Color[0]));
    targetColorArray.push_back(static_cast<int>(m_settings::Target_Color[1]));
    targetColorArray.push_back(static_cast<int>(m_settings::Target_Color[2]));
    targetColorArray.push_back(static_cast<int>(m_settings::Target_Color[3]));
    config[XS("Target_Color")] = targetColorArray;

    config[XS("fontsize")] = static_cast<int>(m_settings::fontsize);
    config[XS("TagsVisCheck")] = m_settings::TagsVisCheck;

    config[XS("DrawNPC")] = m_settings::DrawNPC;
    config[XS("NPCDistance")] = static_cast<int>(m_settings::NPCDistance);
    config[XS("DrawDead")] = m_settings::DrawDead;
    config[XS("DrawAis")] = m_settings::DrawAis;
    config[XS("DrawSleepers")] = m_settings::DrawSleepers;

    json sleeperColorArray = json::array();
    sleeperColorArray.push_back(static_cast<int>(m_settings::Sleeper_Color[0]));
    sleeperColorArray.push_back(static_cast<int>(m_settings::Sleeper_Color[1]));
    sleeperColorArray.push_back(static_cast<int>(m_settings::Sleeper_Color[2]));
    sleeperColorArray.push_back(static_cast<int>(m_settings::Sleeper_Color[3]));
    config[XS("Sleeper_Color")] = sleeperColorArray;

    config[XS("DrawWounded")] = m_settings::DrawWounded;
    config[XS("DrawTarget")] = m_settings::DrawTarget;
    config[XS("DrawSafezone")] = m_settings::DrawSafezone;
    config[XS("PlayerESPDistance")] = static_cast<int>(m_settings::PlayerESPDistance);

    config[XS("Flyhack_Indicator")] = m_settings::Flyhack_Indicator;
    config[XS("AntiFlyKick")] = m_settings::AntiFlyKick;

    config[XS("Brightnight")] = m_settings::Brightnight;
    config[XS("Stars")] = m_settings::Stars;
    config[XS("BrightCave")] = m_settings::BrightCave;
    config[XS("TimeChanger")] = m_settings::TimeChanger;
    config[XS("GameTime")] = static_cast<int>(m_settings::GameTime);
    config[XS("RemoveUnderwaterEffects")] = m_settings::RemoveUnderwaterEffects;

    std::string jsonString = config.dump(4);

    std::string file_name;
    if (m_settings::SelectedConfig == 0)
    {
        file_name = XS("Legit.json");
    }
    else if (m_settings::SelectedConfig == 1)
    {
        file_name = XS("Rage.json");
    }
    else if (m_settings::SelectedConfig == 2)
    {
        file_name = XS("Config1.json");
    }
    else if (m_settings::SelectedConfig == 3)
    {
        file_name = XS("Config2.json");
    }
    else if (m_settings::SelectedConfig == 4)
    {
        file_name = XS("Config3.json");
    }

    FILE* file = LI_FN(fopen)(file_name.c_str(), XS("w"));
    if (file == nullptr) {
        return;
    }

    size_t dataSize = jsonString.size();
    size_t bytesWritten = LI_FN(fwrite)(jsonString.c_str(), 1, dataSize, file);

    if (bytesWritten != dataSize) {
        LI_FN(fclose)(file);
        return;
    }

    LI_FN(fclose)(file);
    config.clear();
    const auto string = std::wstring(XS(L"[Serotonin] Saved Config!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

}

void Buttons::ClearRaidCache() {

    LogSystem::loggedExplosions.clear();

    const auto string = std::wstring(XS(L"[Serotonin] Cleared Raid Cache!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}

void Buttons::ClearLOSPoints() {

    Features().GeneratedPoints = false;

    const auto string = std::wstring(XS(L"[Serotonin] Reset LOS Points!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}