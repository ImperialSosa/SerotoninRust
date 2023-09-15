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

};