#include "../hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"

float flyhackDistanceVertical = 0.f;
float flyhackDistanceHorizontal = 0.f;
float flyhackPauseTime;

bool TestFlying(AssemblyCSharp::BasePlayer* _This, Vector3 oldPos, Vector3 newPos)
{
	if (!InGame)
		return false;

	if (auto LocalPlayer = _This)
	{
		flyhackPauseTime = maxx(0.f, flyhackPauseTime - UnityEngine::Time::get_fixedDeltaTime());
		bool inAir = false;

		float radius = LocalPlayer->GetRadius();
		float height = LocalPlayer->GetHeight(false);

		Vector3 vector = (oldPos + newPos) * 0.5f;
		Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
		Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
		float radius2 = radius - 0.05f;

		bool a = UnityEngine::Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, RustStructs::Ignore);
		inAir = !a;

		if (inAir)
		{
			bool flag = false;

			Vector3 vector4 = newPos - oldPos;
			float num3 = Math::abs(vector4.y);
			float num4 = vector4.Magnitude2D();

			if (vector4.y >= 0.f) {
				flyhackDistanceVertical += vector4.y;
				flag = true;
			}
			if (num3 < num4) {
				flyhackDistanceHorizontal += num4;
				flag = true;
			}
			if (flag) {
				float num5 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num6 = _This->GetJumpHeight() + num5 + 3.5f;
				if (flyhackDistanceVertical > num6) {
					return true;
				}
				float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7 + 3.5;
				if (flyhackDistanceHorizontal > num8) {
					return true;
				}
			}
		}
		else
		{
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
	}
	return false;
}

bool CheckFlyhack(AssemblyCSharp::BasePlayer* _This, bool PreventFlyhack)
{
	if (!InGame)
		return false;

	bool result;

	if (!IsAddressValid(_This->lastSentTick()))
		return false;

	if (!IsAddressValid(_This->get_transform()))
		return false;

	if (auto LocalPlayer = _This)
	{
		if (auto Transform = LocalPlayer->get_transform())
		{
			if (!_This->IsDead() && !_This->IsSleeper())
			{
				if (LocalPlayer->lastSentTick() && LocalPlayer->get_transform())
				{
					Vector3 oldPos = LocalPlayer->lastSentTick()->position();

					Vector3 modelPos = LocalPlayer->get_transform()->get_position();

					result = TestFlying(LocalPlayer, oldPos, modelPos);

					float num5 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num6 = _This->GetJumpHeight() + num5 + 3.0f;

					m_settings::MaxVerticalFlyhack = num6;
					m_settings::VerticalFlyhack = flyhackDistanceVertical;

					float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num8 = 5.f + num7;

					m_settings::MaxHorisontalFlyhack = num8 + 3.0f;
					m_settings::HorisontalFlyhack = flyhackDistanceHorizontal;

					if (result && PreventFlyhack)
					{
						const auto last_sent_tick = LocalPlayer->lastSentTick();
						const auto player_movement = LocalPlayer->movement();
						if (player_movement && last_sent_tick) {
							auto LastSentTickPos = last_sent_tick->position();
							reinterpret_cast<AssemblyCSharp::BaseMovement*>(player_movement)->set_TargetMovement(Vector3());
							reinterpret_cast<AssemblyCSharp::BaseMovement*>(player_movement)->TeleportTo(Vector3(LastSentTickPos.x, LastSentTickPos.y - 0.001, LastSentTickPos.z), LocalPlayer);
							if (const auto rigid_body = player_movement->body()) {
								rigid_body->set_velocity(Vector3());
							}
						}
					}
					return result;
				}
			}
		}
	}

	return false;
}

inline bool FirstInit = false;

void Hooks::ClientInput(AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2)
{
	if(!InGame)
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		Features().Instance()->LocalPlayer = a1;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);

	if (!IsAddressValid(ToAddress(Hooks::ProjectileShootHookhk.get_original<void*>()))
		|| !IsAddressValid(ToAddress(Hooks::PPA_WriteToStreamhk.get_original<void*>())))
	{
		Hooks::ProjectileShootHookhk.VirtualFunctionHook(XS("ProjectileShoot"), HASH("WriteToStream"), &Hooks::ProjectileShootHook, XS("ProtoBuf"), 1);
		Hooks::PPA_WriteToStreamhk.VirtualFunctionHook(XS("PlayerProjectileAttack"), HASH("WriteToStream"), &Hooks::PPA_WriteToStream, XS("ProtoBuf"), 1);
	}

	if (!FirstInit)
	{
		Hooks::TryToMovehk.VirtualFunctionHook(XS("ItemIcon"), HASH("TryToMove"), &Hooks::TryToMove, XS(""), 0);
		Hooks::PlayerWalkMovementhk.VirtualFunctionHook(XS("PlayerWalkMovement"), HASH("ClientInput"), &Hooks::PlayerWalkMovement, XS(""), 2);
		FirstInit = true;
	}

	if (m_settings::Flyhack_Indicator)
		CheckFlyhack(a1, m_settings::AntiFlyKick);

	float timeSinceLastTick = (UnityEngine::Time::get_realtimeSinceStartup() - Features().Instance()->LocalPlayer->lastSentTickTime());
	float last_tick_time = maxx(0.f, minm(timeSinceLastTick, 1.f));
	m_settings::last_tick_time = last_tick_time;

	float num = 1.5f;
	float eye_clientframes = 2.0f;
	float eye_serverframes = 2.0f;
	float num2 = eye_clientframes / 60.f;
	float num3 = eye_serverframes * Max3(UnityEngine::Time::get_deltaTime(), UnityEngine::Time::get_smoothDeltaTime(), UnityEngine::Time::get_fixedDeltaTime());
	float num4 = (last_tick_time + num2 + num3) * num;

	float num5 = Features().Instance()->LocalPlayer->MaxEyeVelocity() + Features().Instance()->LocalPlayer->GetParentVelocity().Magnitude();
	float num6 = Features().Instance()->LocalPlayer->BoundsPadding() + num4 * num5;

	m_settings::max_spoofed_eye_distance = num6;


	if (m_settings::WaitForInstantHit)
	{
		auto desynctime = UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;


		if (desyncpercentage >= 0.85f)
		{
			InstantHitReady = true;
		}
		else
		{
			InstantHitReady = false;
		}
	}

	if (UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = .99f;
	}
	else
	{
		Features().Instance()->LocalPlayer->clientTickInterval() = 0.05f;
	}

	if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		Features().Instance()->FindManipulationAngles(num6);
	}
	else
	{
		Features().ManipulationAngle = Vector3();
		m_settings::can_manipulate = false;
		m_settings::StartShooting = false;
		m_settings::Manipulation_Indicator = false;
	}


	if (m_settings::BulletTP)
	{
		Features().Instance()->FindBulletTPAngles(num6);
	}
	else if (!Features().BulletTPAngle.IsZero()) {
		Features().BulletTPAngle = Vector3(0, 0, 0);
		m_settings::Thickbullet_Indicator = false;
		m_settings::Thickbullet_AutoShoot = false;
	}

	auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();

	if (IsAddressValid(Features().LocalPlayer) && IsAddressValid(BaseProjectile) && BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
	{
		Features().AutoShoot(BaseProjectile);
		Features().FastBullet(BaseProjectile);
		Features().BulletQueue(BaseProjectile);
		Features().AutoReload(BaseProjectile);
	}

	Features().RemoveCollision();

	if (m_settings::AdminFlags)
	{
		a1->playerFlags() |= RustStructs::PlayerFlags::IsAdmin;
	}

	if (m_settings::AdminCheat)
	{
		if (UnityEngine::Input::GetKey(m_settings::AdminCheatKey))
			a1->GetBaseMovement()->adminCheat() = true;
		else
			a1->GetBaseMovement()->adminCheat() = false;
	}

	if (m_settings::NoAttackRestrictions)
	{
		//Shooting whilst mounted
		if (const auto Mounted = a1->mounted())
		{
			Mounted->canWieldItems() = true;
		}

		//CanAttack
		if (const auto ModelState = a1->modelState())
		{
			ModelState->set_flag(RustStructs::ModelState_Flag::OnGround);
			a1->GetBaseMovement()->set_Grounded(1.f);
		}

	}


	Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(a1, a2);
}