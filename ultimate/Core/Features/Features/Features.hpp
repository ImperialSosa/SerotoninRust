#pragma once

#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

#define M_PI_2 1.57079632679489661923


class Features {
public:
	static auto Instance() -> Features*
	{
		Features obj;
		return &obj;
	}
public:

	auto FindManipulationAngles(float MaxDesyncValue) -> void;
	auto FindBulletTPAngles(float MaxDesyncValue) -> void;
	Vector3 GetManipulationAngle();
	auto AutoShoot(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;
	auto FastBullet(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;
	auto BulletQueue(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;
	auto AutoReload(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;

	auto RemoveCollision() -> void;
public:
	static inline AssemblyCSharp::BasePlayer* LocalPlayer;
	static inline Vector3 ManipulationAngle;
	static inline Vector3 BulletTPAngle;
	static inline Vector3 BTPSeperator;

};