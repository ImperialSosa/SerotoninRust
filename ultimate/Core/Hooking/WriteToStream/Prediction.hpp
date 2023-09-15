#pragma once

#include "../Hooks.hpp"


using AssemblyCSharp::BasePlayer;
using AssemblyCSharp::ItemModProjectile;
using AssemblyCSharp::BaseProjectile;
using AssemblyCSharp::Projectile;
inline float InitialDistanceDebug = 0.f;
inline bool CalledLaunchFromHook = false;
inline AssemblyCSharp::Projectile* LaunchedProjectilesArray[256];
inline size_t LaunchedProjectileSize;
inline bool InstantHitReady = false;

inline Vector3 GetAimDirectionToTarget(BasePlayer* Local, BaseProjectile* Projectile, Vector3 TargetPosition, Vector3 TargetVelocity, ItemModProjectile* mod, Vector3 EyesPosition)
{
	if (!InGame)
		return Vector3();

	if (!IsAddressValid(Local))
		return Vector3();

	if (!IsAddressValid(Projectile))
		return Vector3();

	if (!IsAddressValid(mod))
		return Vector3();



	auto fVelocity = mod->projectileVelocity();
	auto fVelocityScale = Projectile->GetProjectileVelocityScale(false) * (1.f);
	auto fProjectilePrefab = mod->projectileObject()->Get()->GetComponent<AssemblyCSharp::Projectile>(FPSystem::Type::Projectile());
	auto fDrag = fProjectilePrefab->drag();
	auto fGraviModifier = fProjectilePrefab->gravityModifier();
	auto vGravity = Vector3(0.f, -9.81f, 0.f);

	auto fFinalVelocity = fVelocity * fVelocityScale;
	auto vTrueGravity = vGravity * fGraviModifier;

	Vector3 TemporaryTargetPosition = TargetPosition;

	// 30 Sims
	for (size_t j = 0; j < 50; j++)
	{
		Vector3 Direction = (TemporaryTargetPosition - EyesPosition).Normalized();

		Vector3 Velocity = Direction * fFinalVelocity;

		Vector3 CurrentPosition = EyesPosition;
		Vector3 PreviousPosition = CurrentPosition;

		Vector3 MissedOffset = { 0, 0, 0 };
		Vector3 ClosestPoint(FLT_MAX, FLT_MAX, FLT_MAX);

		Vector3 SimulatedTargetPosition = TargetPosition;
		float SimulatedTargetTime = 0.f;

		Vector3 initialPosition = CurrentPosition;
		float initalDistance = fProjectilePrefab->initialDistance();


		if (m_settings::InstantBullet)
		{
			auto desyncTimeClamped = minm(UnityEngine::Time::get_realtimeSinceStartup() - Local->lastSentTickTime(), 1.f);
			auto desyncTimeClampedServer = maxx(desyncTimeClamped - 0.03125f * 5.f, 0.2f);
			float num11 = desyncTimeClampedServer;
			float distanceToTarget = CurrentPosition.Distance(TemporaryTargetPosition);// this should be changed to total project air distance due to arc
			float magnitude2 = Velocity.Magnitude();
			initalDistance = fProjectilePrefab->initialDistance() + num11 * magnitude2;
			InitialDistanceDebug = initalDistance;
		}

		size_t TotalSteps = static_cast<size_t>(8.0f / 0.03125f);

		for (size_t Step = 0; Step < TotalSteps; Step++)
		{
			PreviousPosition = CurrentPosition;

			// move our current position by the velocity
			//
			CurrentPosition += (Velocity * 0.03125f);

			// Modify our velocity by gravity, since gravity is generally a vector of 0, -9.81, 0 per second,
			// and deltaTime is probably .03125 seconds, we are basically reducing Velocity y axis by adding a negative number
			//
			Velocity += (vTrueGravity * 0.03125f);

			// We are now reducing all 3 axis of velocity by itself multiply by drag value
			// fDrag is just a multiplier of velocity per second and since it is the opposite of the current
			// velocity, we are subtracting
			//
			Velocity -= (Velocity * fDrag * 0.03125f);

			// Line here is the direction that points the previous position
			// toward the current position, so it is this calculation frame frame's segment's vector


			auto Line = CurrentPosition - PreviousPosition;

			if (initialPosition.Distance(CurrentPosition) > initalDistance || InitialDistanceDebug == 0.f)
			{
				// Simulating future player position based off current travelTime
				//
				SimulatedTargetTime += 0.03125f;
				SimulatedTargetPosition = (TargetPosition + (TargetVelocity * (SimulatedTargetTime)));
			}
			else
			{
				SimulatedTargetPosition = TargetPosition;
			}

			// Magnitude here is basically the change of the current line across all 3 axis
			//
			auto LineLength = Line.Magnitude();
			Line.UnityNormalize();
			auto v = SimulatedTargetPosition - PreviousPosition;
			auto d = v.Dot(Line);

			if (d < 0.0f)
			{
				d = 0.0f;
			}
			else if (d > LineLength)
			{
				d = LineLength;
			}

			Vector3 CurrentPoint = PreviousPosition + Line * d;

			float DistanceMissed = CurrentPoint.Distance(SimulatedTargetPosition);

			// If our Nearest point is practically ON the target, then that mean we can hit the entity with this aimAngle
			//
			if (DistanceMissed < 0.1f)
			{
				// Total amount of time the bullet traveled for to arrive at this point
				//
				ClosestPoint = CurrentPoint;

				return TemporaryTargetPosition;
			}

			// If this misses our target but it is a closer point in the path, save it
			//
			else if (DistanceMissed < ClosestPoint.Distance(SimulatedTargetPosition))
			{
				// How far is this point from the target (as the sim go on, it will get closer and closer)
				//
				MissedOffset = SimulatedTargetPosition - CurrentPoint;
				ClosestPoint = CurrentPoint;
			}
		}

		TemporaryTargetPosition += MissedOffset;
	}

	return Vector3();
}
