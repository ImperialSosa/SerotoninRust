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
	auto LineCast(Vector3 a, Vector3 b) -> bool;
	Vector3 GetManipulationAngle();
public:
	static inline AssemblyCSharp::BasePlayer* LocalPlayer;
	static inline Vector3 ManipulationAngle;
	static inline Vector3 BulletTPAngle;
	static inline Vector3 BTPSeperator;

};