#pragma once
#include "Hooker.hpp"

#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"



class Hooks {
public:

	static auto Instance() -> Hooks*
	{
		Hooks obj;
		return &obj;
	}

public:
	void BeginHooks();

private:
	HOOK(void, OnGUI, (AssemblyCSharp::ExplosionsFPS* _This))
	HOOK(void, Update_, (AssemblyCSharp::MainMenuSystem* _This))
	HOOK(void, ClientInput, (AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2))
	HOOK(void, ProjectileShootHook, (ProtoBuf::ProjectileShoot* _This, ProtoBuf::Stream* Stream))
	HOOK(void, DoAttack, (AssemblyCSharp::BaseProjectile* _This))
	HOOK(void, ProjectileUpdate, (AssemblyCSharp::Projectile* _This))
	HOOK(void, PPA_WriteToStream, (ProtoBuf::PlayerProjectileAttack* _This, ProtoBuf::Stream* Stream))
	HOOK(void, PlayerWalkMovement, (AssemblyCSharp::PlayerWalkMovement* _This, AssemblyCSharp::InputState* _State, AssemblyCSharp::ModelState* _ModelState))
	HOOK(void, TryToMove, (AssemblyCSharp::ItemIcon* _This))
	HOOK(void, SkyUpdate, (AssemblyCSharp::TOD_Camera* _This))
	HOOK(void, SteamPlatformUpdate, (RustPlatformSteam::SteamPlatform* _This))
	HOOK(void, OnAttacked, (AssemblyCSharp::BasePlayer* instance, AssemblyCSharp::HitInfo* hitinfo))
	HOOK(void, LateUpdate, (AssemblyCSharp::TOD_Sky* TOD_Sky))
	HOOK(void, BlockSprint, (AssemblyCSharp::BasePlayer* instance, float duration))
	HOOK(void, OnNetworkMessage, (AssemblyCSharp::Client* _This, Network::Message* packet))
	HOOK(void, OnInput, (AssemblyCSharp::BaseMelee* _This))	
	HOOK(void, DoAttackBow, (AssemblyCSharp::BowWeapon* _This))
	HOOK(void, FlintStrikeWeaponDoAttack, (AssemblyCSharp::FlintStrikeWeapon* _This))
		HOOK(void, DoAttackMelee, (AssemblyCSharp::BaseMelee* _This))

};