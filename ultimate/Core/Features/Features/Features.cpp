#include "Features.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../Visuals/Visuals.hpp"
#include "../EyeHack/EyeHack.hpp"
#include <array>


std::vector<Vector3> GenerateCircle(float radius, int points, bool BulletTP = false) {
	std::vector<Vector3> result;
	float step = (2.0f * M_PI) / points;
	float maxYValue = 1.5f;

	for (int i = 0; i < points; i++) {
		float angle = i * step;
		float x = radius * Math::cosf(angle);
		float z = radius * Math::sinf(angle);

		// Adjust the yValue to gradually increase to maxYValue
		float yValue = (i / static_cast<float>(points - 1)) * maxYValue;

		result.push_back(Vector3(x, yValue, z));//
		result.push_back(Vector3(-x, -yValue, -z));
		result.push_back(Vector3(-x, 0.f, 0.f));
		result.push_back(Vector3(x, 0.f, 0.f));

		result.push_back(Vector3(0.f, 0.f, z));
		result.push_back(Vector3(0.f, 0.f, -z));

		result.push_back(Vector3(x, 0.f, z));
		result.push_back(Vector3(x, -yValue, z));
		result.push_back(Vector3(0.f, -yValue, 0.f));
	}

	return result;
}


inline void GenerateBulletTPAngles(std::vector<Vector3>& re, float radius = 2.4f)
{
	const int points = 3;
	const float step = 1.57079632679489661923f / points;
	const float radiusY = 2.4f;
	const float halfRadiusY = radiusY;

	for (float y = -halfRadiusY; y < halfRadiusY; y += 0.3f)
	{
		const float sinY = Math::sinf(y);
		const float cosY = Math::cosf(y);

		float current = 0;

		for (size_t i = 0; i < points; i++)
		{
			const float sinCurrent = Math::sinf(current);
			const float cosCurrent = Math::cosf(current);
			const float x = sinCurrent * radius;
			const float z = cosCurrent * radius;

			re.emplace_back(0, y, 0);
			re.emplace_back(x, 0.f, z);
			re.emplace_back(-x, 0.f, z);
			re.emplace_back(x, 0.f, -z);
			re.emplace_back(-x, 0.f, -z);
			re.emplace_back(x, y, z);
			re.emplace_back(-x, y, -z);
			re.emplace_back(-x, -y, -z);
			re.emplace_back(x, -y, z);
			re.emplace_back(0.f, -y, z);
			re.emplace_back(0.f, -y, -z);
			current += step;
		}
	}
}


inline void BulletTPAnglesHarvey1(std::vector<Vector3>& re, float radius = 2.4f)
{
	const int points = 3;
	const float step = 1.57079632679489661923f / points;
	const float radiusY = 2.4f;
	const float halfRadiusY = radiusY;

	for (float y = -halfRadiusY; y < halfRadiusY; y += 0.3f)
	{
		const float sinY = Math::sinf(y);
		const float cosY = Math::cosf(y);

		float current = 0;

		for (size_t i = 0; i < points; i++)
		{
			const float sinCurrent = Math::sinf(current);
			const float cosCurrent = Math::cosf(current);
			const float x = sinCurrent * radius;
			const float z = cosCurrent * radius;

			re.emplace_back(0, y, 0); //2.4m
			re.emplace_back(x, 0.f, z);
			re.emplace_back(-x, 0.f, z);
			re.emplace_back(x, 0.f, -z);
			re.emplace_back(-x, 0.f, -z);
			re.emplace_back(x, y, z);
			re.emplace_back(-x, y, -z);
			re.emplace_back(-x, -y, -z);
			re.emplace_back(x, -y, z);
			re.emplace_back(0.f, -y, z);
			re.emplace_back(0.f, -y, -z);

			re.emplace_back(0, y / 1.1, 0); //2.2m
			re.emplace_back(x / 1.1, 0.f, z / 1.1);
			re.emplace_back(-x / 1.1, 0.f, z / 1.1);
			re.emplace_back(x / 1.1, 0.f, -z / 1.1);
			re.emplace_back(-x / 1.1, 0.f, -z / 1.1);
			re.emplace_back(x / 1.1, y / 1.1, z / 1.1);
			re.emplace_back(-x / 1.1, y / 1.1, -z / 1.1);
			re.emplace_back(-x / 1.1, -y / 1.1, -z / 1.1);
			re.emplace_back(x / 1.1, -y / 1.1, z / 1.1);
			re.emplace_back(0.f, -y / 1.1, z / 1.1);
			re.emplace_back(0.f, -y / 1.1, -z / 1.1);

			re.emplace_back(0, y / 1.2, 0); //2.0m
			re.emplace_back(x / 1.2, 0.f, z / 1.2);
			re.emplace_back(-x / 1.2, 0.f, z / 1.2);
			re.emplace_back(x / 1.2, 0.f, -z / 1.2);
			re.emplace_back(-x / 1.2, 0.f, -z / 1.2);
			re.emplace_back(x / 1.2, y / 1.2, z / 1.2);
			re.emplace_back(-x / 1.2, y / 1.2, -z / 1.2);
			re.emplace_back(-x / 1.2, -y / 1.2, -z / 1.2);
			re.emplace_back(x / 1.2, -y / 1.2, z / 1.2);
			re.emplace_back(0.f, -y / 1.2, z / 1.2);
			re.emplace_back(0.f, -y / 1.2, -z / 1.2);

			re.emplace_back(0, y / 1.3, 0); //1.8m
			re.emplace_back(x / 1.3, 0.f, z / 1.3);
			re.emplace_back(-x / 1.3, 0.f, z / 1.3);
			re.emplace_back(x / 1.3, 0.f, -z / 1.3);
			re.emplace_back(-x / 1.3, 0.f, -z / 1.3);
			re.emplace_back(x / 1.3, y / 1.3, z / 1.3);
			re.emplace_back(-x / 1.3, y / 1.3, -z / 1.3);
			re.emplace_back(-x / 1.3, -y / 1.3, -z / 1.3);
			re.emplace_back(x / 1.3, -y / 1.3, z / 1.3);
			re.emplace_back(0.f, -y / 1.3, z / 1.3);
			re.emplace_back(0.f, -y / 1.3, -z / 1.3);

			current += step;
		}
	}
}

inline void BulletTPAnglesModeIntense(std::vector<Vector3>& re, float step = 0.4)
{
	for (float x = -2.2; x <= 2.2; x += step) {
		for (float y = -2.4; y <= 2.4; y += step) {
			for (float z = -2.2; z <= 2.2; z += step) {
				re.emplace_back(x, y, z);
			}
		}
	}
}

bool can_manipulate(AssemblyCSharp::BasePlayer* ply, Vector3 pos, float mm_eye = 7.f) //7m only check rn
{
	if (!InGame || !IsAddressValid(ply))
		return false;


	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget();
	if (!IsAddressValid(AimbotTarget.m_player))
		return false;

	if (m_settings::BulletTP)
	{
		Vector3 re_p = ply->eyes()->get_position();

		if (AssemblyCSharp::IsVisible(re_p, pos)) {
			Features().ManipulationAngle = Vector3(0, 0, 0);
			return true;
		}

		auto do_check = [&](Vector3 a) {

			Vector3 p = re_p + a;

			if (!AssemblyCSharp::IsVisible(p, re_p))
				return false;


			if (!EyeHack().ValidateEyePos(Features().LocalPlayer, p))
				return false;

			if (!EyeHack().ValidateEyePos(Features().LocalPlayer, re_p + a))
				return false;


			if (!AssemblyCSharp::IsVisible(p, a + Features().BTPSeperator))
				return false;

			Features().ManipulationAngle = a;
			return true;
		};



		for (float y = 1.5f; y > -1.5f; y -= 0.3f) {
			int points = 5;
			float step = (M_PI_2) / points;
			float x, z, current = 0;
			for (size_t i = 0; i < points; i++)
			{
				x = Math::sinf(current) * mm_eye;
				z = Math::cosf(current) * mm_eye;

				Vector3 p1 = Vector3(x, y, z);
				Vector3 p2 = Vector3(-x, y, z);
				Vector3 p3 = Vector3(x, y, -z);
				Vector3 p4 = Vector3(-x, y, -z);

				Vector3 re_p = ply->eyes()->get_position();

				Vector3 p = re_p + p1;

				if (do_check(p1)) return true;
				if (do_check(p2)) return true;
				if (do_check(p3)) return true;
				if (do_check(p4)) return true;

				current += step;
			}
		}

		Features().ManipulationAngle = Vector3(0, 0, 0);
		return false;
	}
	else
	{
		Vector3 re_p = ply->eyes()->get_position();

		if (AssemblyCSharp::IsVisible(re_p, pos)) {
			Features().ManipulationAngle = Vector3(0, 0, 0);
			return true;
		}

		auto do_check = [&](Vector3 a) {

			Vector3 p = re_p + a;

			if (!AssemblyCSharp::IsVisible(p, re_p))
				return false;

			if (!EyeHack().ValidateEyePos(Features().LocalPlayer, p))
				return false;

			UnityEngine::DDraw().Sphere(p, 0.05f, Color::Red(), 0.02f, 10);

			auto tick_time = Features().LocalPlayer->lastSentTickTime();
			float desyncTime = (UnityEngine::Time::get_realtimeSinceStartup() - tick_time) - 0.03125 * 3;
			float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * Features().LocalPlayer->MaxVelocity()) - 0.05f;
			float max_v_multicplier = 4.5f;
			float v_mm_max_eye = 1.5f;

			if (!AssemblyCSharp::IsVisible(p, pos)) {
				bool t = false;
				auto right = Features().LocalPlayer->eyes()->BodyRight();
				auto forward = Features().LocalPlayer->eyes()->BodyForward();
				auto _forward = Features().LocalPlayer->eyes()->HeadForward();

				Vector3 z = pos;
				std::array < Vector3, 41 >positions = {
				z + Vector3(0.f, (v_mm_max_eye / 5), 0.f), // small up

				z + Vector3(0.f, v_mm_max_eye / 2, 0.f), // medium up

				z + Vector3(0.f, v_mm_max_eye, 0.f), // big up

				z + Vector3(0.f, -(1.4f / 2), 0.f), // small down

				z + Vector3(0.f, -1.4f, 0.f), // big down

				z + Vector3(right.x * (mm_max_eye / 2), 0.f, right.z * (mm_max_eye / 2)), // small right

				z + Vector3(right.x * mm_max_eye, 0.f, right.z * mm_max_eye), // big right

				z + Vector3(right.x * (mm_max_eye / 2), (1.4f / 2), right.z * (mm_max_eye / 2)), // small right up

				z + Vector3(right.x * mm_max_eye, 1.4f, right.z * mm_max_eye), // big right up

				z + Vector3(right.x * (mm_max_eye / 2), -(1.4f / 2), right.z * (4.f / 2)), // small right down

				z + Vector3(right.x * mm_max_eye, -1.4f, right.z * mm_max_eye), // big right down

				z + Vector3(-(right.x * (mm_max_eye / 2)), 0.f, -(right.z * (mm_max_eye / 2))), // small left

				z + Vector3(-(right.x * mm_max_eye), 0.f, -(right.z * mm_max_eye)), // big left

				z + Vector3(-(right.x * (mm_max_eye / 2)), (1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left up

				z + Vector3(-(right.x * mm_max_eye), 1.4f, -(right.z * mm_max_eye)), // big left up

				z + Vector3(-(right.x * (mm_max_eye / 2)), -(1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left down

				z + Vector3(-(right.x * mm_max_eye), -1.4f, -(right.z * mm_max_eye)), // big left down 

				z + Vector3(forward.x * (mm_max_eye / 2), 0.f, forward.z * (mm_max_eye / 2)),// small forward

				z + Vector3(forward.x * mm_max_eye, 0.f, forward.z * mm_max_eye), // big forward

				z + Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))), // small backward

				z + Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big backward

				z + Vector3(forward.x * (mm_max_eye / 2), (1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward up

				z + Vector3(forward.x * mm_max_eye, 1.4f, forward.z * mm_max_eye), // big forward up

				z + Vector3(forward.x * (mm_max_eye / 2), -(1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward down

				z + Vector3(forward.x * mm_max_eye, -1.4f, forward.z * mm_max_eye), // big forward down

				z + Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))),// small reverse

				z + Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big reverse 

				z + Vector3(-(forward.x * (mm_max_eye / 2)), (1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse up

				z + Vector3(-(forward.x * 4.f), 1.4f, -(forward.z * 4.f)), // big reverse up

				z + Vector3(-(forward.x * (mm_max_eye / 2)), -(1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse down

				z + Vector3(-(forward.x * mm_max_eye), -1.4f, -(forward.z * mm_max_eye)), // big reverse down

				z + Vector3(right.x * mm_max_eye, v_mm_max_eye, right.z * (mm_max_eye)) * 0.9f, // big diag-up-right

				z + Vector3(-right.x * (mm_max_eye), (v_mm_max_eye), -right.z * (mm_max_eye)) * 0.9f, // big diag-up-left

				z + Vector3(right.x * mm_max_eye, -v_mm_max_eye, right.z * (mm_max_eye)) * 0.9f, // big diag-down-right

				z + Vector3(-right.x * (mm_max_eye), (-v_mm_max_eye), -right.z * (mm_max_eye)) * 0.9f, // big diag-up-left

				z + Vector3((right.x / 2) * mm_max_eye, v_mm_max_eye, (right.z / 2) * (mm_max_eye)), // big diag-up-right

				z + Vector3(-(right.x / 2) * (mm_max_eye), (v_mm_max_eye), -(right.z / 2) * (mm_max_eye)), // big diag-up-left

				z + Vector3((right.x / 2) * mm_max_eye, -v_mm_max_eye, (right.z / 2) * (mm_max_eye)), // big diag-down-right

				z + Vector3(-(right.x / 2) * (mm_max_eye), (-v_mm_max_eye), -(right.z / 2) * (mm_max_eye)), // big diag-up-left

				z + Vector3((forward.x / 2) * (mm_max_eye / 2), (v_mm_max_eye / 1), (forward.z / 2) * (mm_max_eye / 2)), // big diag-up-forward

				z + Vector3(-((forward.x / 2) * (mm_max_eye / 2)), (v_mm_max_eye / 1), -((forward.z / 2) * mm_max_eye / 2)), // big diag-up-backward
				};


				for (auto v : positions) {

					if (v.y > 1.f)
						continue;

					if (v.y > -1.f)
						continue;

					if (v.x > 9.f)
						continue;

					if (v.x > -9.f)
						continue;

					if (v.z > 9.f)
						continue;

					if (v.z > -9.f)
						continue;


					if (!EyeHack().ValidateEyePos(Features().LocalPlayer, v))
						break;

					if (!EyeHack().ValidateEyePos(Features().LocalPlayer, z))
						break;

					if (AssemblyCSharp::IsVisible(p, v)) {
						if (AssemblyCSharp::IsVisible(z, v)) {
							t = true;
							break;
						}
					}

				}

				if (!t) return false;
			}
			Features().ManipulationAngle = a;
			return true;
		};



		for (float y = 1.5f; y > -1.5f; y -= 0.3f) {
			int points = 5;
			float step = (M_PI_2) / points;
			float x, z, current = 0;
			for (size_t i = 0; i < points; i++)
			{
				x = Math::sinf(current) * mm_eye;
				z = Math::cosf(current) * mm_eye;

				Vector3 p1 = Vector3(x, y, z);
				Vector3 p2 = Vector3(-x, y, z);
				Vector3 p3 = Vector3(x, y, -z);
				Vector3 p4 = Vector3(-x, y, -z);

				Vector3 re_p = ply->eyes()->get_position();

				Vector3 p = re_p + p1;

				if (do_check(p1)) return true;
				if (do_check(p2)) return true;
				if (do_check(p3)) return true;
				if (do_check(p4)) return true;

				current += step;
			}
		}

		Features().ManipulationAngle = Vector3(0, 0, 0);
		return false;

	}
}

auto Features::FindBulletTPAngles(float maxDesyncValue) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(LocalPlayer))
		return;

	if (!LocalPlayer->IsAlive())
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget();
	if (!IsAddressValid(AimbotTarget.m_player))
		return;

	Vector3 targetPosition = AimbotTarget.m_position;
	if (Vector3().IsNaNOrInfinity(targetPosition))
		return;

	float maxDist = 2.4f;

	std::vector<Vector3> arrz;
	if (m_settings::BulletTPIntensity == 0)
		GenerateBulletTPAngles(arrz, maxDist);
	else if (m_settings::BulletTPIntensity == 1)
		BulletTPAnglesHarvey1(arrz, maxDist);
	else if (m_settings::BulletTPIntensity == 2)
		BulletTPAnglesModeIntense(arrz, 0.4);
	else if (m_settings::BulletTPIntensity == 3)
		BulletTPAnglesModeIntense(arrz, 0.2);

	for (const auto& s : arrz)
	{
		Vector3 point = targetPosition + s;
		this->BTPSeperator = targetPosition + s;
		if (AssemblyCSharp::IsVisible(LocalPlayer->eyes()->get_position() + this->ManipulationAngle, point) &&
			EyeHack().ValidateEyePos(AimbotTarget.m_player, point, true))
		{
			UnityEngine::DDraw().Sphere(point, 0.1f, Color::Orange(), 0.05f, 0);


			m_settings::StartShooting = true;
			m_settings::Thickbullet_Indicator = true;
			this->BulletTPAngle = targetPosition + s;
			return;
		}
	}

	this->BulletTPAngle = targetPosition;
}


auto Features::FindManipulationAngles(float MaxDesyncValue) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(LocalPlayer))
		return;


	if (!LocalPlayer->IsAlive())
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget();
	if (!IsAddressValid(AimbotTarget.m_player))
		return;

	Vector3 targetPosition = AimbotTarget.m_position;
	if (Vector3().IsNaNOrInfinity(targetPosition))
		return;

	auto eyes = LocalPlayer->eyes();
	if (!IsAddressValid(eyes))
		return;

	
	if (can_manipulate(LocalPlayer, targetPosition, m_settings::max_spoofed_eye_distance))
	{
		m_settings::StartShooting = true;
		m_settings::Manipulation_Indicator = true;
	}
	else
	{
		m_settings::StartShooting = false;
		m_settings::Manipulation_Indicator = false;
	}

}

auto Features::GetManipulationAngle() -> Vector3 {
	if (Vector3().IsNaNOrInfinity(this->ManipulationAngle))
		return Vector3();

	return this->ManipulationAngle;
}

auto Features::LineCast(Vector3 a, Vector3 b) -> bool
{
	UnityEngine::RaycastHit hit;
	return UnityEngine::Physics::Linecast(a, b, hit, 10551296);
}