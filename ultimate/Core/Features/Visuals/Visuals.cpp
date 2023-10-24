#include "Visuals.hpp"
#include "../../Hooking/Hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../Features/Features.hpp"
#include <array>
#include <algorithm>
inline std::array<int, 20> valid_bones = {
		1, 2, 3, 5, 6, 14, 15, 17, 18, 21, 23, 24, 25, 26, 27, 48, 55, 56, 57, 76
};

inline float NormalizeAngle(float angle) {
	while (angle > 360.0f) {
		angle -= 360.0f;
	}
	while (angle < 0.0f) {
		angle += 360.0f;
	}
	return angle;
}

inline Vector3 NormalizeAngles(Vector3 angles) {
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

inline Vector3 EulerAngles(Vector4 q1) {
	float num = q1.w * q1.w;
	float num2 = q1.x * q1.x;
	float num3 = q1.y * q1.y;
	float num4 = q1.z * q1.z;
	float num5 = num2 + num3 + num4 + num;
	float num6 = q1.x * q1.w - q1.y * q1.z;
	Vector3 vector;
	if (num6 > 0.4995f * num5) {
		vector.y = 2.0f * Math::atan2f(q1.y, q1.x);
		vector.x = 1.57079637f;
		vector.z = 0.0f;
		return NormalizeAngles(vector * 57.2958f);
	}
	if (num6 < -0.4995f * num5) {
		vector.y = -2.0f * Math::atan2f(q1.y, q1.x);
		vector.x = -1.57079637f;
		vector.z = 0.0f;
		return NormalizeAngles(vector * 57.2958f);
	}
	Vector4 quaternion = Vector4(q1.w, q1.z, q1.x, q1.y);
	vector.y = Math::atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
	vector.x = Math::asinf(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
	vector.z = Math::atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
	return NormalizeAngles(vector * 57.2958f);
}

Vector2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
	float mainAngle = flAngle;
	mainAngle += 45.f;

	float flYaw = (mainAngle) * (M_PI / 180.0);

	float viewcosyawzzzzzzz = Math::cosf(flYaw);
	float viewsinyawzzzzzzz = Math::sinf(flYaw);

	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));

	return Vector2(posonscreenX, posonscreenY);
}

void DrawTriangles(Vector2 center) {
	Color col = Color(1, 1, 1, 1.f);
	auto pixelsize = 5; auto trianglecount = 5;
	Vector2 triangleList[5][3] = {
		{ Vector2{ 0, 0 }, Vector2{ 0, 0 }, Vector2{ 0, 0 } },
		{ Vector2{ 0, 0 }, Vector2{ 0, 0 }, Vector2{ 0, 0 } },
		{ Vector2{ 0, 0 }, Vector2{ 0, 0 }, Vector2{ 0, 0 } },
		{ Vector2{ 0, 0 }, Vector2{ 0, 0 }, Vector2{ 0, 0 } },
		{ Vector2{ 0, 0 }, Vector2{ 0, 0 }, Vector2{ 0, 0 } }
	};
	for (size_t n = 0; n < trianglecount; n++)
	{
		std::vector<Vector2> v = {};
		for (size_t i = 0; i < 3; i++)
		{
			triangleList[n][i].x = LI_FN(rand)() % (pixelsize / 2) + 1;
			triangleList[n][i].y = LI_FN(rand)() % (pixelsize / 2) + 1;

			if (triangleList[n][i].x > triangleList[n][i].y)
			{
				float tmp = triangleList[n][i].x;
				triangleList[n][i].x = triangleList[n][i].y;
				triangleList[n][i].y = tmp;
			}
		}
	}


	auto morphTriangleIdx = new int[pixelsize];
	auto morphVertexIdx = new int[pixelsize];
	auto morphDeltaX = new int[pixelsize];
	auto morphDeltaY = new int[pixelsize];
	auto setMorphParams = [&]() {
		for (size_t i = 0; i < 3; i++)
		{
			morphTriangleIdx[i] = LI_FN(rand)() % pixelsize + 0;
			morphVertexIdx[i] = LI_FN(rand)() % 3 + 0;
			morphDeltaX[i] = 0;
			morphDeltaY[i] = 0;
			if ((LI_FN(rand)() % 1 + 0) == 0)
				morphDeltaX[i] = 1;
			else
				morphDeltaX[i] = -1;
		}
		};

	if ((LI_FN(rand)() % 10 + 1) == 1)
		setMorphParams();

	for (size_t i = 0; i < 5; i++)
	{
		float x = triangleList[morphTriangleIdx[i]][morphVertexIdx[i]].x = morphDeltaX[i];
		float y = triangleList[morphTriangleIdx[i]][morphVertexIdx[i]].y = morphDeltaY[i];

		if (x > pixelsize / 2 - 1)
		{
			x = pixelsize / 2 - 1;
			morphDeltaX[i] = -1;
		}
		else if (x < 0)
		{
			x = 0;
			morphDeltaX[i] = 1;
		}

		if (y > pixelsize / 2 - 1)
		{
			y = pixelsize / 2 - 1;
			morphDeltaY[i] = -1;
		}
		else if (y < 0)
		{
			y = 0;
			morphDeltaY[i] = 1;
		}

		if (x > y) {
			float tmp = x;
			x = y;
			y = tmp;
		}

		triangleList[morphTriangleIdx[i]][morphVertexIdx[i]].x = x;
		triangleList[morphTriangleIdx[i]][morphVertexIdx[i]].y = y;
	}

	std::vector<Vector2> v = { };
	std::vector<Vector2> w = { };

	auto reflect = [&](std::vector<Vector2>& v, std::vector<Vector2>& w, int n, int offset) {
		for (int i = 0; i < v.size(); i++)
		{
			if (n == 0)
			{
				w[i].x = v[i].x + offset;
				w[i].y = v[i].y + offset;
			}
			else if (n == 1)
			{
				w[i].x = -v[i].x + offset;
				w[i].y = v[i].y + offset;
			}
			else if (n == 2)
			{
				w[i].x = v[i].x + offset;
				w[i].y = -v[i].y + offset;
			}
			else if (n == 3)
			{
				w[i].x = -v[i].x + offset;
				w[i].y = -v[i].y + offset;
			}
			else if (n == 4)
			{
				w[i].x = v[i].y + offset;
				w[i].y = v[i].x + offset;
			}
			else if (n == 5)
			{
				w[i].x = -v[i].y + offset;
				w[i].y = v[i].x + offset;
			}
			else if (n == 6)
			{
				w[i].x = v[i].y + offset;
				w[i].y = -v[i].x + offset;
			}
			else if (n == 7)
			{
				w[i].x = -v[i].y + offset;
				w[i].y = -v[i].x + offset;
			}
		}
		};

	for (size_t n = 0; n < trianglecount; n++)
	{
		for (size_t k = 0; k < 3; k++)
		{
			v[k].x = triangleList[n][k].x;
			v[k].y = triangleList[n][k].y;
		}

		for (size_t k = 0; k < 3; k++)
		{
			reflect(v, w, k, pixelsize / 2);

			for (size_t z = 0; z < trianglecount; z++)
			{
				for (size_t ii = 0; ii < 3; ii++)
				{
					w[ii].x += center.x;
					w[ii].y += center.y;
				}

				UnityEngine::GL().Line(w[0], w[1], col);
				UnityEngine::GL().Line(w[1], w[2], col);
				UnityEngine::GL().Line(w[0], w[2], col);
			}
		}
	}
}

//Radar Function
Vector2 WorldToRadar(Vector3 origin, Vector2 position, INT size, FLOAT rotation)
{
	Vector2 clampRotation
	((float)Math::cosf((rotation * (M_PI / 180.f)) + M_PI),
		-(float)Math::sinf((rotation * (M_PI / 180.f)) + M_PI));

	Vector2 clampCoords
	((origin.x * clampRotation.x + origin.z * clampRotation.y),
		(origin.x * clampRotation.y - origin.z * clampRotation.x));

	INT clampSize
	(size / 2.0f);

	Vector2 bVec
	(-clampCoords.x + position.x + clampSize,
		-clampCoords.y + position.y + clampSize);

	bVec.x = -clampCoords.x + position.x + clampSize;
	bVec.y = -clampCoords.y + position.y + clampSize;

	if (bVec.x > (position.x + size)) bVec.x = (position.x + size);
	else if (bVec.x < (position.x)) bVec.x = position.x;

	if (bVec.y > (position.y + size)) bVec.y = (position.y + size);
	else if (bVec.y < (position.y)) bVec.y = position.y;

	return bVec;
}

box_bounds Visuals::get_bounds(AssemblyCSharp::BasePlayer* player, float expand) {
	if (!player)
		return box_bounds::null();

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return box_bounds::null();

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return box_bounds::null();


	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };


	const auto bone_transforms = player->model()->boneTransforms();
	if (!bone_transforms)
		return ret;

	for (auto j : valid_bones) {

		const auto bone = bone_transforms->m_Items[j];

		if (!bone)
			continue;

		auto transform = bone;
		if (IsAddressValid(transform)) {
			Vector2 sc;
			auto world_pos = transform->get_position();

			if (j == 48)
				world_pos.y += 0.2f;

			if (UnityEngine::WorldToScreen(world_pos, sc))
			{
				Vector2 bone_screen = sc;

				if (bone_screen.x < ret.left)
					ret.left = bone_screen.x;
				if (bone_screen.x > ret.right)
					ret.right = bone_screen.x;
				if (bone_screen.y < ret.top)
					ret.top = bone_screen.y;
				if (bone_screen.y > ret.bottom)
					ret.bottom = bone_screen.y;
			}
		}
	}

	if (ret.left == FLT_MAX)
		return box_bounds::null();
	if (ret.right == FLT_MIN)
		return box_bounds::null();
	if (ret.top == FLT_MAX)
		return box_bounds::null();
	if (ret.bottom == FLT_MIN)
		return box_bounds::null();

	ret.left -= expand;
	ret.right += expand;
	ret.top -= expand;
	ret.bottom += expand;

	return ret;
};

inline void DrawCornerBox(float x, float y, float x2, float y2, Color col)
{
	float box_width = x2 - x;
	float box_height = y2 - y;

	//top 
	UnityEngine::GL::Line(Vector2(x, y), Vector2(x + box_width / 4, y), col);
	UnityEngine::GL::Line(Vector2(x2, y), Vector2(x2 - box_width / 4, y), col);

	//left
	UnityEngine::GL::Line(Vector2(x, y), Vector2(x, y + box_height / 4), col);
	UnityEngine::GL::Line(Vector2(x, y2), Vector2(x, y2 - box_height / 4), col);

	//right
	UnityEngine::GL::Line(Vector2(x2, y), Vector2(x2, y + box_height / 4), col);
	UnityEngine::GL::Line(Vector2(x2, y2), Vector2(x2, y2 - box_height / 4), col);

	//bottom
	UnityEngine::GL::Line(Vector2(x, y2), Vector2(x + box_width / 4, y2), col);
	UnityEngine::GL::Line(Vector2(x2, y2), Vector2(x2 - box_width / 4, y2), col);

	return;
}

void Visuals::DrawPlayers()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
	if (!IsAddressValid(LocalPlayer))
		return;

	for (const auto EntityList : VisualsArray)
	{
		const auto BasePlayer = EntityList.BasePlayer;
		if (!IsAddressValid(BasePlayer))
			continue;

		float distance = LocalPlayer->get_transform()->get_position().Distance(BasePlayer->get_transform()->get_position());
		bool npc = false;

		if (BasePlayer->IsA(AssemblyCSharp::ScientistNPC::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::GingerbreadNPC::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::NPCPlayer::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::TunnelDweller::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::UnderwaterDweller::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::HTNPlayer::StaticClass()))
		{
			if (!m_settings::DrawNPC)
				continue;
			else if (m_settings::DrawNPC)
			{
				if (distance > m_settings::NPCDistance)
					continue;
			}

			npc = true;
		}

		if (BasePlayer->IsLocalPlayer())
			continue;

		if (BasePlayer->wasDead())
			continue;

		if (BasePlayer->IsDead())
		{
			if (!m_settings::DrawDead)
				continue;
		}

		if (BasePlayer->IsReceivingSnapshot())
			continue;

		if (BasePlayer->IsSleeper())
		{
			if (!m_settings::DrawSleepers)
				continue;
		}

		if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded && !m_settings::DrawWounded)
			continue;

		if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::SafeZone && !m_settings::DrawSafezone)
			continue;

		if (!IsAddressValid(BasePlayer->model()))
			continue;

		if (!IsAddressValid(BasePlayer->get_transform()))
			continue;


		const auto playerDistance = Features().LocalPlayer->get_transform()->get_position().Distance(BasePlayer->get_transform()->get_position());
		Vector2 RadarPoint;

		if (m_settings::Radar) {
			const auto bodyAngles = AssemblyCSharp::LocalPlayer::get_Entity()->input()->bodyAngles();
			const auto LocalPos = AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position();
			const auto PlayerPos = BasePlayer->get_transform()->get_position();

			RadarPoint = WorldToRadar(PlayerPos - LocalPos, Vector2(m_settings::RadarPosX, m_settings::RadarPosY), m_settings::RadarSize, bodyAngles.y);
		}

		if (playerDistance <= m_settings::PlayerESPDistance)
		{
			box_bounds bo = get_bounds(BasePlayer, 0.f);
			if (!bo.empty())
			{
				int yoffset = 8;
				int yoffsethead = 0;
				float box_width = bo.right - bo.left;
				float box_height = bo.bottom - bo.top;
				Vector2 footPos = { bo.left + (box_width / 2), bo.bottom };
				Vector2 headPos = { bo.left + (box_width / 2), bo.top - 9.54f };

				auto IsVisible = [&](Vector3 from) {
					Vector3 head_pos_ = BasePlayer->get_bone_transform(48)->get_position();

					for (auto bone : { 48, 2, 3, 4, 15, 14, 26, 57 }) {
						Vector3 TargetPosition;
						if (bone == 48) TargetPosition = head_pos_;
						else TargetPosition = BasePlayer->get_bone_transform(bone)->get_position();
						if (AssemblyCSharp::IsVisible(from, TargetPosition)) {
							return true;
						}
					}
					return false;
					};

				auto is_Visible = IsVisible(camera->get_positionz());
				bool IsWounded = BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded;
				auto VisibleColor = Color{ m_settings::VisCheck_Color[0], m_settings::VisCheck_Color[1], m_settings::VisCheck_Color[2], m_settings::VisCheck_Color[3] };
				auto DrawBox_Color = Color{ m_settings::DrawBox_Color[0], m_settings::DrawBox_Color[1], m_settings::DrawBox_Color[2], m_settings::DrawBox_Color[3] };
				auto VisCheckColor = is_Visible ? VisibleColor : DrawBox_Color;
				auto NameTag_Color = Color{ m_settings::DrawNameTag_Color[0], m_settings::DrawNameTag_Color[1], m_settings::DrawNameTag_Color[2], m_settings::DrawNameTag_Color[3] };
				auto Sleeper_Color = Color{ m_settings::Sleeper_Color[0], m_settings::Sleeper_Color[1], m_settings::Sleeper_Color[2], m_settings::Sleeper_Color[3] };
				auto Wounded_Color = Color{ m_settings::Wounded_Color[0], m_settings::Wounded_Color[1], m_settings::Wounded_Color[2], m_settings::Wounded_Color[3] };
				auto Scientist_Color = Color{ m_settings::Scientist_color[0], m_settings::Scientist_color[1], m_settings::Scientist_color[2], m_settings::Scientist_color[3] };
				auto Dead_Color = Color{ m_settings::Dead_Color[0], m_settings::Dead_Color[1], m_settings::Dead_Color[2], m_settings::Dead_Color[3] };
				auto Safezone_Color = Color{ m_settings::Safezone_Color[0], m_settings::Safezone_Color[1], m_settings::Safezone_Color[2], m_settings::Safezone_Color[3] };
				auto HeldItem_Color = Color{ m_settings::DrawHeldItem_Color[0], m_settings::DrawHeldItem_Color[1], m_settings::DrawHeldItem_Color[2], m_settings::DrawHeldItem_Color[3] };
				auto Friend_Color = Color{ m_settings::Friend_Color[0], m_settings::Friend_Color[1], m_settings::Friend_Color[2], m_settings::Friend_Color[3] };
				auto Target_Color = Color{ m_settings::Target_Color[0], m_settings::Target_Color[1], m_settings::Target_Color[2], m_settings::Target_Color[3] };

				bool isFriend = false;
				auto camera = UnityEngine::Camera::get_main();
				if (!IsAddressValid(camera))
					return;

				auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
				/*if (!IsAddressValid(m_target.m_player))
					return;*/

				Color BoxColor;

				if (isFriend)
					BoxColor = Friend_Color;
				else if (npc)
					BoxColor = Scientist_Color;
				else if (BasePlayer == m_target.m_player && m_settings::DrawTarget)
					BoxColor = Target_Color;
				else if (BasePlayer->IsSleeper() && m_settings::DrawSleepers)
					BoxColor = Sleeper_Color;
				else if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded && m_settings::DrawWounded)
					BoxColor = Wounded_Color;
				else if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::SafeZone && m_settings::DrawSafezone)
					BoxColor = Safezone_Color;
				else if (BasePlayer->IsDead() && m_settings::DrawDead)
					BoxColor = Dead_Color;
				else
					BoxColor = m_settings::EspVisCheck ? VisCheckColor : DrawBox_Color;

				if (m_settings::Radar)
				{
					UnityEngine::GL().CircleFilled(Vector2(RadarPoint), 3.f, BoxColor.GetUnityColor(), 25);
				}

				if (m_settings::SelectedBoxESP == 1)
				{
					UnityEngine::GL::Rectangle(Vector2(bo.left, bo.top), Vector2(bo.right, bo.bottom), BoxColor.GetUnityColor());
				}

				if (m_settings::SelectedBoxESP == 2)
				{
					DrawCornerBox(bo.left, bo.top, bo.right, bo.bottom, BoxColor.GetUnityColor());
				}

				if (m_settings::Target_Indicator)
				{
					if (BasePlayer == m_target.m_player)
					{
						UnityEngine::GL::TextCenter(Vector2(headPos.x, headPos.y - yoffsethead), XS("Target"), BoxColor, Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
						yoffsethead += 12.f;
					}
				}

				if (m_settings::Skeleton)
				{
					auto SkeletonColor = BoxColor.GetUnityColor();

					auto HeadBone = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
					auto NeckBone = BasePlayer->get_bone_transform(RustStructs::bones::neck)->get_position();
					auto Spine = BasePlayer->get_bone_transform(RustStructs::bones::spine1)->get_position();
					Vector2 HeadLoc;
					Vector2 NeckLoc;
					Vector2 SpineLoc;

					auto LShoulder = BasePlayer->get_bone_transform(RustStructs::bones::l_upperarm)->get_position();
					auto RShoulder = BasePlayer->get_bone_transform(RustStructs::bones::r_upperarm)->get_position();
					Vector2 LShoulderLoc;
					Vector2 RShoulderLoc;

					auto LElbow = BasePlayer->get_bone_transform(RustStructs::bones::l_forearm)->get_position();
					auto RElbow = BasePlayer->get_bone_transform(RustStructs::bones::r_forearm)->get_position();
					Vector2 LElbowLoc;
					Vector2 RElbowLoc;

					auto LWrist = BasePlayer->get_bone_transform(RustStructs::bones::l_hand)->get_position();
					auto RWrist = BasePlayer->get_bone_transform(RustStructs::bones::r_hand)->get_position();
					Vector2 LWristLoc;
					Vector2 RWristLoc;

					auto LHip = BasePlayer->get_bone_transform(RustStructs::bones::l_hip)->get_position();
					auto RHip = BasePlayer->get_bone_transform(RustStructs::bones::r_hip)->get_position();
					Vector2 LHipLoc;
					Vector2 RHipLoc;

					auto LKnee = BasePlayer->get_bone_transform(RustStructs::bones::l_knee)->get_position();
					auto RKnee = BasePlayer->get_bone_transform(RustStructs::bones::r_knee)->get_position();
					Vector2 LKneeLoc;
					Vector2 RKneeLoc;

					auto LAnkle = BasePlayer->get_bone_transform(RustStructs::bones::l_ankle_scale)->get_position();
					auto RAnkle = BasePlayer->get_bone_transform(RustStructs::bones::r_ankle_scale)->get_position();
					Vector2 LAnkleLoc;
					Vector2 RAnkleLoc;

					UnityEngine::WorldToScreen(HeadBone, HeadLoc);
					UnityEngine::WorldToScreen(NeckBone, NeckLoc);
					UnityEngine::WorldToScreen(Spine, SpineLoc);

					UnityEngine::WorldToScreen(LShoulder, LShoulderLoc);
					UnityEngine::WorldToScreen(RShoulder, RShoulderLoc);

					UnityEngine::WorldToScreen(LElbow, LElbowLoc);
					UnityEngine::WorldToScreen(RElbow, RElbowLoc);

					UnityEngine::WorldToScreen(LWrist, LWristLoc);
					UnityEngine::WorldToScreen(RWrist, RWristLoc);

					UnityEngine::WorldToScreen(LHip, LHipLoc);
					UnityEngine::WorldToScreen(RHip, RHipLoc);

					UnityEngine::WorldToScreen(LKnee, LKneeLoc);
					UnityEngine::WorldToScreen(RKnee, RKneeLoc);

					UnityEngine::WorldToScreen(LAnkle, LAnkleLoc);
					UnityEngine::WorldToScreen(RAnkle, RAnkleLoc);

					//Draw Skeleton
					if (!HeadLoc.IsZero() && !NeckLoc.IsZero() && !SpineLoc.IsZero() && !LShoulderLoc.IsZero() && !RShoulderLoc.IsZero() && !LElbowLoc.IsZero() && !RElbowLoc.IsZero() && !LWristLoc.IsZero() && !RWristLoc.IsZero() && !LHipLoc.IsZero() && !RHipLoc.IsZero() && !LKneeLoc.IsZero() && !RKneeLoc.IsZero() && !LAnkleLoc.IsZero() && !RAnkleLoc.IsZero()) {
						/* connector */
						UnityEngine::GL::Line(Vector2(HeadLoc.x, HeadLoc.y), Vector2(NeckLoc.x, NeckLoc.y), SkeletonColor);
						UnityEngine::GL::Line(Vector2(NeckLoc.x, NeckLoc.y), Vector2(SpineLoc.x, SpineLoc.y), SkeletonColor);

						/* upper left */
						/* upper spine -> left shoulder */
						UnityEngine::GL::Line(Vector2(NeckLoc.x, NeckLoc.y), Vector2(LShoulderLoc.x, LShoulderLoc.y), SkeletonColor);

						/* left shoulder -> left elbow */
						UnityEngine::GL::Line(Vector2(LShoulderLoc.x, LShoulderLoc.y), Vector2(LElbowLoc.x, LElbowLoc.y), SkeletonColor);

						/* left elbow -> left wrist*/
						UnityEngine::GL::Line(Vector2(LElbowLoc.x, LElbowLoc.y), Vector2(LWristLoc.x, LWristLoc.y), SkeletonColor);

						/* upper right */
						/* upper spine -> right shoulder */
						UnityEngine::GL::Line(Vector2(NeckLoc.x, NeckLoc.y), Vector2(RShoulderLoc.x, RShoulderLoc.y), SkeletonColor);

						/* right shoulder -> right elbow */
						UnityEngine::GL::Line(Vector2(RShoulderLoc.x, RShoulderLoc.y), Vector2(RElbowLoc.x, RElbowLoc.y), SkeletonColor);

						/* right elbow -> right wrist*/
						UnityEngine::GL::Line(Vector2(RElbowLoc.x, RElbowLoc.y), Vector2(RWristLoc.x, RWristLoc.y), SkeletonColor);

						/* lower left */
						/* lower spine -> left hip */
						UnityEngine::GL::Line(Vector2(SpineLoc.x, SpineLoc.y), Vector2(LHipLoc.x, LHipLoc.y), SkeletonColor);

						/* left hip -> left knee */
						UnityEngine::GL::Line(Vector2(LHipLoc.x, LHipLoc.y), Vector2(LKneeLoc.x, LKneeLoc.y), SkeletonColor);

						/* left knee -> left ankle */
						UnityEngine::GL::Line(Vector2(LKneeLoc.x, LKneeLoc.y), Vector2(LAnkleLoc.x, LAnkleLoc.y), SkeletonColor);

						/* lower right */
						/* lower spine -> right hip */
						UnityEngine::GL::Line(Vector2(SpineLoc.x, SpineLoc.y), Vector2(RHipLoc.x, RHipLoc.y), SkeletonColor);

						/* right hip -> right knee */
						UnityEngine::GL::Line(Vector2(RHipLoc.x, RHipLoc.y), Vector2(RKneeLoc.x, RKneeLoc.y), SkeletonColor);

						/* right knee -> right ankle */
						UnityEngine::GL::Line(Vector2(RKneeLoc.x, RKneeLoc.y), Vector2(RAnkleLoc.x, RAnkleLoc.y), SkeletonColor);
					}
				}

				if (m_settings::SelectedHealthBar == 1)
				{
					float bar_health = 0;
					auto health = BasePlayer->_health();
					//auto max_health = base_player->_maxHealth();
					float max_health = 100.f;
					float draw_health = health;

					if (health > max_health)
					{
						draw_health = max_health;
					}

					const auto bar_width = 30;
					bar_health = (bar_width / max_health) * draw_health;

					auto bar_color = Color::Green();
					if (health > 50.f)
					{
						bar_color = Color::Green();
					}
					else if (health > 20.f && health < 40.f)
					{
						bar_color = Color::Orange();
					}
					else if (health < 20.f)
					{
						bar_color = Color::Red();
					}

					UnityEngine::GL::RectangleFilled(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2(footPos.x + (bar_width / 2), bo.bottom + yoffset + 3.f), Color::Black());
					UnityEngine::GL::RectangleFilled(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2((footPos.x - (bar_width / 2)) + bar_health, bo.bottom + yoffset + 3.f), bar_color);
					UnityEngine::GL::Rectangle(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2(footPos.x + (bar_width / 2), bo.bottom + yoffset + 4.f), Color::Black());
					yoffset += 13;
				}

				if (m_settings::SelectedHealthBar == 2) {
					float bar_health = 0;
					auto health = BasePlayer->_health();
					//auto max_health = base_player->_maxHealth();
					float max_health = 100.f;
					float draw_health = health;

					if (health > max_health)
					{
						draw_health = max_health;
					}

					bar_health = (box_height / max_health) * draw_health;

					auto bar_color = Color::Green();
					if (health > 50.f)
					{
						bar_color = Color::Green();
					}
					else if (health > 20.f && health < 40.f)
					{
						bar_color = Color::Orange();
					}
					else if (health < 20.f)
					{
						bar_color = Color::Red();
					}

					//fill_box_({ bo.left - 5.0f, bo.top , 2.f, box_height }, Color::Black());
					//fill_box_({ bo.left - 5.0f, bo.bottom , 2.f, -current_health_y }, Color::Green());

					int width = 2.f;
					UnityEngine::GL::RectangleFilled(Vector2(bo.left - 5.0f, bo.top), Vector2(bo.left - 5.0f + width, bo.top + box_height), Color::Black());
					UnityEngine::GL::RectangleFilled(Vector2(bo.left - 5.0f, bo.bottom), Vector2(bo.left - 5.0f + width, bo.bottom + -bar_health), bar_color);
					UnityEngine::GL::Rectangle(Vector2(bo.left - 5.0f, bo.top), Vector2(bo.left - 5.0f + width, bo.top + box_height), Color::Black());
				}

				if (m_settings::nameEsp)
				{
					if (m_settings::TagsVisCheck)
					{
						if (npc)
						{
							std::string player_name = XS("Scientist");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;

							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), BoxColor.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
						}
						else
						{
							if (IsAddressValid(BasePlayer->get_displayName())) //decrypted
							{
								std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), BoxColor.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							}

						}
						yoffset += 13;
					}
					else
					{
						if (npc)
						{
							std::string player_name = XS("Scientist");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;

							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), NameTag_Color.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
						}
						else
						{
							if (IsAddressValid(BasePlayer->get_displayName())) //decrypted
							{
								std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), NameTag_Color.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							}
						}

						yoffset += 13;
					}
				}

				if (m_settings::ShowAlerts)
				{
					auto playerpos = BasePlayer->get_bone_transform(48)->get_position();
					auto localpos = LocalPlayer->get_bone_transform(48)->get_position();
					auto distance = playerpos.Distance(localpos);
					auto fwd = playerpos + (BasePlayer->eyes()->BodyForward() * distance);

					auto dist = fwd.Distance(localpos);
					auto r = (distance / 50.f); r = (r < 1.f ? 1.f : r);
					if (dist < r)
					{
						std::string name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
						std::string player_name = XS("");
						char str[256];
						sprintf(str, XS("[Warning] %s is looking at you!"), name);
						player_name = player_name + " " + str;
						float center_x = (float)(UnityEngine::screen_size.x) / 2, center_y = (float)(UnityEngine::screen_size.y) / 2;
						UnityEngine::GL().TextCenter(Vector2(center_x, center_y - 415), player_name.c_str(), Color::Red(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

					}
				}

				if (m_settings::HeldItemType == 1 || m_settings::HeldItemType == 3)
				{

					const auto item = BasePlayer->ActiveItem();
					if (IsAddressValid(item))
					{
						auto info = item->info();

						if (IsAddressValid(info))
						{
							auto display_name = info->GetDisplayName(item);
							if (IsAddressValid(display_name))
							{
								auto held_item = utf16_to_utf8(display_name->c_str());

								if (m_settings::TagsVisCheck)
								{
									UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), BoxColor.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
									yoffset += 13;
								}
								else
								{
									UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), HeldItem_Color.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
									yoffset += 13;
								}
							}
						}
					}
				}

				if (m_settings::ammoESP) {
					const auto item = BasePlayer->ActiveItem();
					if (IsAddressValid(item))
					{
						auto info = item->info();

						if (IsAddressValid(info))
						{
							auto display_name = info->GetDisplayName(item);
							if (IsAddressValid(display_name))
							{
								auto BaseProjectile = BasePlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
								if (IsAddressValid(BaseProjectile))
								{
									auto Magazine = BaseProjectile->primaryMagazine();
									if (IsAddressValid(Magazine))
									{
										std::string AmmoType;
										auto ammoType = Magazine->ammoType();
										auto AmmoID = ammoType->itemid();

										if (Magazine->contents() <= 0)
											AmmoType = XS("Empty");
										else if (AmmoID == -1211166256)
											AmmoType = XS("5.56 Ammo");
										else if (AmmoID == -1321651331)
											AmmoType = XS("Explosive 5.56 Ammo");
										else if (AmmoID == 1712070256)
											AmmoType = XS("HV 5.56 Ammo");
										else if (AmmoID == 605467368)
											AmmoType = XS("Incendiary 5.56 Ammo");
										else if (AmmoID == 785728077)
											AmmoType = XS("Pistol Bullet");
										else if (AmmoID == -1691396643)
											AmmoType = XS("HV Pistol Bullet");
										else if (AmmoID == 51984655)
											AmmoType = XS("Incendiary Pistol Bullet");
										else if (AmmoID == -2097376851)
											AmmoType = XS("Nailgun Nails");
										else if (AmmoID == 550753330)
											AmmoType = XS("SnowBalls");
										else if (AmmoID == -1685290200)
											AmmoType = XS("12 Gauge Buckshot");
										else if (AmmoID == -1036635990)
											AmmoType = XS("12 Gauge Incendiary Shell");
										else if (AmmoID == -727717969)
											AmmoType = XS("12 Gauge Slug");
										else if (AmmoID == 588596902)
											AmmoType = XS("Handmade Shell");
										else if (AmmoID == 1055319033)
											AmmoType = XS("40mm Shotgun Round");
										else if (AmmoID == 349762871)
											AmmoType = XS("40mm HE Grenade");
										else if (AmmoID == 915408809)
											AmmoType = XS("40mm Smoke Grenade");
										else if (AmmoID == -1841918730)
											AmmoType = XS("High Velocity Rocket");
										else if (AmmoID == 1296788329)
											AmmoType = XS("Homing Missile");
										else if (AmmoID == -17123659)
											AmmoType = XS("Smoke Rocket WIP!!!!");
										else if (AmmoID == 1638322904)
											AmmoType = XS("Incendiary Rocket");
										else if (AmmoID == -1843426638)
											AmmoType = XS("MLRS Rocket");
										else if (AmmoID == -742865266)
											AmmoType = XS("Rocket");
										else if (AmmoID == -384243979)
											AmmoType = XS("SAM Ammo");
										else
											AmmoType = XS("Unknown");

										UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), AmmoType.c_str(), HeldItem_Color.GetUnityColor(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
										yoffset += 13;
									}
								}
							}
						}
					}
				}

				if (m_settings::ShowOutside || m_settings::ShowInside)
				{
					Vector3 position = BasePlayer->get_bone_transform(47)->get_position() + Vector3(0.f, 500.f, 0.f);
					UnityEngine::RaycastHit hitInfo;
					if (AssemblyCSharp::GamePhysics::Trace(UnityEngine::Ray(BasePlayer->get_bone_transform(47)->get_position(), position), 0.f, hitInfo, 500.f, 2097152, RustStructs::QueryTriggerInteraction::Ignore, nullptr))
					{
						if (m_settings::ShowInside) {
							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), XS("Inside"), Color::Red(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							yoffset += 13;
						}
					}
					else
					{
						if (m_settings::ShowOutside) {
							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), XS("Outside"), Color::Green(), Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							yoffset += 13;
						}
					}
				}

				if (m_settings::HeldItemType == 2 || m_settings::HeldItemType == 3)
				{

					const auto item = BasePlayer->ActiveItem();
					if (IsAddressValid(item))
					{
						auto info = item->info();

						if (IsAddressValid(info))
						{
							auto IconSprite = info->FindIconSprite(info->itemid());

							if (IconSprite) {
								auto IconTexture = IconSprite->get_texture();

								yoffset += 4;
								UnityEngine::GL().DrawIcon(Vector2(footPos.x - 12, footPos.y + yoffset - 12), Vector2(24, 24), IconTexture, Color::White());
								yoffset += 24;
							}
						}
					}
				}

			if (m_settings::PlayerChams)
			{
				auto playerModel = BasePlayer->playerModel();
				if (IsAddressValid(playerModel))
				{
					auto _multiMesh = playerModel->_multiMesh();
					if (IsAddressValid(_multiMesh))
					{
						auto Renderers = _multiMesh->get_Renderers();
						if (IsAddressValid(Renderers))
						{
							auto Renderers_Items = Renderers->_items;
							if (Renderers_Items)
							{
								auto Renderers_Size = Renderers->_size;
								if (Renderers_Size) {
									for (int i = 0; i < Renderers_Size; i++) {
										auto MainRenderer = Renderers_Items->m_Items[i];

										if (IsAddressValid(MainRenderer))
										{
											auto material = MainRenderer->material();

											if (!IsAddressValid(material))
												continue;

											int selectedChams = m_settings::SelectedChams;

											switch (selectedChams) {
											case 1:
												if (FireBundleA) {
													if (!FireShaderA) //Blue Fire
														FireShaderA = FireBundleA->LoadAsset<UnityEngine::Shader>(XS("new amplifyshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!FireMaterialA)
														FireMaterialA = FireBundleA->LoadAsset<UnityEngine::Material>(XS("fire.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != FireShaderA)
													{
														MainRenderer->set_material(FireMaterialA);
														FireMaterialA->set_shader(FireShaderA);
													}
												}
												break;
											case 2:
												if (FireBundleB) {
													if (!FireShaderB) //Red Fire
														FireShaderB = FireBundleB->LoadAsset<UnityEngine::Shader>(XS("new amplifyshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!FireMaterialB)
														FireMaterialB = FireBundleB->LoadAsset<UnityEngine::Material>(XS("fire2.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != FireShaderB)
													{
														MainRenderer->set_material(FireMaterialB);
														FireMaterialB->set_shader(FireShaderB);
													}
												}
												break;
											case 3:
												if (LightningBundle) {
													if (!LightningShader) //Lightning
														LightningShader = LightningBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!LightningMaterial)
														LightningMaterial = LightningBundle->LoadAsset<UnityEngine::Material>(XS("lightning.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != LightningShader)
													{
														MainRenderer->set_material(LightningMaterial);
														LightningMaterial->set_shader(LightningShader);
													}
												}
												break;
											case 4:
												if (GeometricBundle) {
													if (!GeometricShader) //Geometric Disolve
														GeometricShader = GeometricBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro geometric dissolve.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!GeometricMaterial)
														GeometricMaterial = GeometricBundle->LoadAsset<UnityEngine::Material>(XS("galaxy.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != GeometricShader)
													{
														MainRenderer->set_material(GeometricMaterial);
														GeometricMaterial->set_shader(GeometricShader);
													}
												}
												break;
											case 5:
												if (GalaxyBundle) {
													if (!GalaxyShader) //Galaxy
														GalaxyShader = GalaxyBundle->LoadAsset<UnityEngine::Shader>(XS("galaxymaterial.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!GalaxyMaterial)
														GalaxyMaterial = GalaxyBundle->LoadAsset<UnityEngine::Material>(XS("galaxymaterial_12.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != GalaxyShader)
													{
														MainRenderer->set_material(GalaxyMaterial);
														GalaxyMaterial->set_shader(GalaxyShader);
													}
												}
												break;
											case 6:
												if (WireFrameBundle) {
													if (!WireFrameShader) //Galaxy
														WireFrameShader = WireFrameBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro wireframe.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!WireFrameMaterial)
														WireFrameMaterial = WireFrameBundle->LoadAsset<UnityEngine::Material>(XS("wireframe.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != WireFrameShader)
													{
														MainRenderer->set_material(WireFrameMaterial);
														WireFrameMaterial->set_shader(WireFrameShader);
														//WireFrameMaterial->SetColor("_Color", Color::Red());
													}
												}
												break;
											case 7:
												if (ColorBundle) {
													if (!ColorShader) //Galaxy
														ColorShader = ColorBundle->LoadAsset<UnityEngine::Shader>(XS("chams.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (material->shader() != ColorShader)
													{
														material->set_shader(ColorShader);
														material->SetColor(XS("_ColorVisible"), VisibleColor.GetUnityColor());
														material->SetColor(XS("_ColorBehind"), BoxColor.GetUnityColor());

														if (npc)
														{
															material->SetColor(XS("_ColorVisible"), BoxColor.GetUnityColor());
															material->SetColor(XS("_ColorBehind"), BoxColor.GetUnityColor());
														}
													}
												}
												break;
											case 8:
												if (RPBGalaxyBundle) {
													if (!RPBGalaxyShader) //Galaxy
														RPBGalaxyShader = RPBGalaxyBundle->LoadAsset<UnityEngine::Shader>(XS("galaxymaterial.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

													if (!RPBGalaxyMaterial)
														RPBGalaxyMaterial = RPBGalaxyBundle->LoadAsset<UnityEngine::Material>(XS("galaxymaterial_03.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

													if (material->shader() != RPBGalaxyShader)
													{
														MainRenderer->set_material(RPBGalaxyMaterial);
														RPBGalaxyMaterial->set_shader(RPBGalaxyShader);
													}
												}
												break;
											}
										}
									}
										
									}
								}
							}
						}
					}
				}
			}
		}
		
	}
}


inline void DoMeleeAttack(AssemblyCSharp::BasePlayer* target, AssemblyCSharp::BaseMelee* baseprojectile, bool is_player = false) {
	if (!IsAddressValid(target))
		return;

	Vector3 local_position = UnityEngine::Camera::get_main()->get_positionz();

	if (baseprojectile->nextAttackTime() <= UnityEngine::Time::get_time())
	{
		if (baseprojectile->timeSinceDeploy() > baseprojectile->deployDelay())
		{
			auto g_hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
			auto g_hit_test = CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);

			if (IsAddressValid(g_hit_test))
			{
				auto hit_test = (AssemblyCSharp::HitTest*)g_hit_test;
				if (IsAddressValid(hit_test))
				{
					UnityEngine::Ray ray = UnityEngine::Ray(local_position, (target->get_bone_transform(47)->get_position() - local_position).Normalized());

					UnityEngine::Transform* trans = is_player ? target->get_bone_transform(47) : target->get_transform();
					if (!trans)
						return;

					hit_test->MaxDistance() = 1000;
					hit_test->HitTransform() = trans;
					hit_test->AttackRay() = ray;
					hit_test->DidHit() = true;
					hit_test->HitEntity() = target;
					hit_test->HitPoint() = trans->InverseTransformPoint(target->get_bone_transform(47)->get_position());
					hit_test->HitNormal() = Vector3(0, 0, 0);
					hit_test->damageProperties() = baseprojectile->damageProperties();

					baseprojectile->StartAttackCooldown(baseprojectile->repeatDelay());
					return baseprojectile->ProcessAttack(hit_test);
				}
			}

		}
	}
};

void Visuals::CachePlayers()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!this->VisiblePlayerList)
		this->VisiblePlayerList = AssemblyCSharp::BasePlayer::visiblePlayerList();

	auto Vals = VisiblePlayerList->vals;
	auto size = Vals->count;
	auto buffer = Vals->buffer;
	

	for (std::int32_t index = 0; index < size; index++)
	{
		auto BasePlayer = buffer->m_Items[index];
		if (!IsAddressValid(BasePlayer))
			continue;

		if (BasePlayer->IsLocalPlayer())
			continue;

		if (m_settings::SilentMelee)
		{
			auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();

			if (IsAddressValid(BaseProjectile))
			{


				if (BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass())
					|| BaseProjectile->IsA(AssemblyCSharp::JackHammer::StaticClass())
					&& !BaseProjectile->IsA(AssemblyCSharp::Planner::StaticClass()))
				{
					
					if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position(), BasePlayer->get_bone_transform(48)->get_position()))
					{
						auto world_position = BasePlayer->get_bone_transform(48)->get_position();
						auto local = AssemblyCSharp::LocalPlayer::get_Entity()->ClosestPoint(world_position);
						auto camera = AssemblyCSharp::LocalPlayer::get_Entity()->get_bone_transform(48)->get_position();

						if (camera.get_3d_dist(world_position) <= 4.5f)
						{
							DoMeleeAttack(BasePlayer, (AssemblyCSharp::BaseMelee*)BaseProjectile, true);
						}
					}
				}
			}
		}
	
		VisualsArrayTemp.push_back(VisualsVector(BasePlayer));
	}

	VisualsArray = VisualsArrayTemp;
	VisualsArrayTemp.clear();
}



bool ComputeBox(AssemblyCSharp::BasePlayer* base_player, Vector4& box)
{

	const auto transform = base_player->get_transform();

	if (!IsAddressValid(transform))
	{
		return false;
	}

	const auto& bounds = base_player->bounds();

	const auto center = bounds.m_Center;
	const auto extents = bounds.m_Extents;

	const auto mins = -extents;
	const auto maxs = extents;

	Vector3 corners[8] =
	{
		{ mins[0], mins[1], mins[2] },
		{ mins[0], maxs[1], mins[2] },
		{ maxs[0], maxs[1], mins[2] },
		{ maxs[0], mins[1], mins[2] },
		{ maxs[0], maxs[1], maxs[2] },
		{ mins[0], maxs[1], maxs[2] },
		{ mins[0], mins[1], maxs[2] },
		{ maxs[0], mins[1], maxs[2] },
	};

	const auto position = transform->get_position();
	const auto angles = transform->get_eulerAngles();

	box.x = UnityEngine::Screen::get_width();
	box.y = UnityEngine::Screen::get_height();
	box.z = -1.f;
	box.w = -1.f;

	const auto yaw = UnityEngine::ToRadians(angles[1]);

	const auto sine = -Math::sinf(yaw);
	const auto cosine = Math::cosf(yaw);

	for (const auto& corner : corners)
	{
		Vector3 world =
		{
			(position[0] + center[0] + (corner[0] * cosine - corner[2] * sine)),
			(position[1] + center[1] + (corner[1])),
			(position[2] + center[2] + (corner[0] * sine + corner[2] * cosine)),
		};

		Vector3 screen = { };

		if (UnityEngine::WorldToScreen2(world, screen))
		{
			box.x = minm(box.x, screen.x);
			box.y = minm(box.y, screen.y);
			box.z = maxx(box.z, screen.x);
			box.w = maxx(box.w, screen.y);
		}
	}

	return true;
}

void Visuals::RenderEntities()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	for (auto CachedEntity : PrefabVectorList)
	{
		auto BaseEntity = CachedEntity.CachedEntity;
		if (!BaseEntity)
			continue;

		const auto prefab_name = BaseEntity->get_ShortPrefabName();

		Vector2 screen = { };

		if (!IsAddressValid(prefab_name))
			continue;


		auto name = prefab_name->c_str();

		if (UnityEngine::WorldToScreen(BaseEntity->get_positionz(), screen))
		{
			auto test_plr = static_cast<AssemblyCSharp::BasePlayer*>(BaseEntity);

			Vector2 render_pad(0.f, 0.f);
			Vector4 box = { };
			if (ComputeBox(test_plr, box))
			{
				if (box.z < 180.f || box.z < -180.f)
					continue;

				//Vector2 screen(box.x, box.y);
				Vector2 ScreenBox(box.x, box.y);

				const auto width = box.z - box.x;
				const auto height = box.w - box.y;

				float half = (box.z - box.x) / 2;

				auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(BaseEntity->get_transform()->get_position());
				//float distance = 500;

				if (distance <= m_settings::MaxDroppedDistance)
				{
					if (m_settings::DroppedItems)
					{
						if (BaseEntity->IsA(AssemblyCSharp::WorldItem::StaticClass()))
						{
							auto world_item = static_cast<AssemblyCSharp::WorldItem*>(BaseEntity);

							if (world_item)
							{
								auto item = world_item->item();
								if (item)
								{
									auto name = item->GetItemName();

									if (name->c_str())
									{
										auto DroppedColor = Color{ m_settings::DroppedItemColor[0], m_settings::DroppedItemColor[1], m_settings::DroppedItemColor[2], m_settings::DroppedItemColor[3] };
										std::string player_name = utf16_to_utf8(name->c_str());
										char str[256];
										sprintf(str, XS("[%dm]"), (int)distance);
										player_name = player_name + " " + str;

										UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DroppedColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

										if (m_settings::DroppedItemsChams) {
											auto ChamsColor = Color{ 168, 166, 50, 255.f };
											auto g_render = BaseEntity->GetComponentsInChildren(FPSystem::Type::Renderer());
											if (IsAddressValid(g_render))
											{
												auto size = g_render->max_length;
												for (int i = 0; i < size; i++)
												{
													auto main_renderer = g_render->m_Items[i];
													if (!(main_renderer))
														continue;

													auto material = main_renderer->material();

													if (!IsAddressValid(material))
														continue;

													auto g_shader = UnityEngine::Shader::Find(XS("Hidden/Internal-Colored"));

													if (!IsAddressValid(g_shader))
														continue;

													if (g_shader != material->shader())
													{
														material->set_shader(g_shader);
													}
													material->SetInt(XS("_ZTest"), 8);
													material->SetColor(XS("_Color"), ChamsColor.GetUnityColor());

												}
											}
										}
									}
								}
							}
						}
					}
				}
		
				if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
				{
					if (distance <= m_settings::MaxCollectableDistance)
					{
						if (m_settings::Hemp)
						{
							if (HASH("hemp-collectable") == Hash(name, false))
							{

								auto HempColor = Color{ m_settings::HempColor[0], m_settings::HempColor[1], m_settings::HempColor[2], m_settings::HempColor[3] };

								std::string player_name = XS("Hemp");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), HempColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

								if (m_settings::CollectablesIcon)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("clone.hemp.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (HASH("diesel_collectable") == Hash(name, false))
						{
							if (m_settings::DieselBarrel)
							{
								auto DieselColor = Color{ m_settings::DieselColor[0], m_settings::DieselColor[1], m_settings::DieselColor[2], m_settings::DieselColor[3] };
								std::string player_name = XS("Diesel");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DieselColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

								if (m_settings::CollectablesIcon)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("diesel_barrel.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}
					}
				}

				if (m_settings::cupboard)
				{
					float half = (box.z - box.x) / 2;
					if (BaseEntity->IsA(AssemblyCSharp::BuildingPrivlidge::StaticClass()))
					{
						auto building_priv = reinterpret_cast<AssemblyCSharp::BuildingPrivlidge*>(BaseEntity);

						if (IsAddressValid(building_priv))
						{
							float yoffset = 0;

							auto DeployableColor = Color{ m_settings::DeployableColor[0], m_settings::DeployableColor[1], m_settings::DeployableColor[2], m_settings::DeployableColor[3] };

							int cachedUpkeepPeriodMinutes = building_priv->UpKeep();
							int days = cachedUpkeepPeriodMinutes / 1440;
							int hours = cachedUpkeepPeriodMinutes / 60;

							auto _health = reinterpret_cast<AssemblyCSharp::BaseCombatEntity*>(building_priv)->_health();
							auto _maxhealth = reinterpret_cast<AssemblyCSharp::BaseCombatEntity*>(building_priv)->_maxHealth();

							std::string player_name = XS("Tool Cupboard");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;

							UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), DeployableColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							yoffset += 12.f;

							if (m_settings::TC_Upkeep) {
								std::string upkeep = XS("Upkeep: ");
								char str2[256];
								sprintf(str2, XS("[%dh]"), (int)hours);
								upkeep = upkeep + " " + str2;

								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), upkeep.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12;
							}
							if (m_settings::TC_Health)
							{
								float draw_health = _health;
								float yoffsethealth = 7.f;
								if (_health > _maxhealth) {
									draw_health = _maxhealth;
								}

								const auto bar_width = 30;
								const auto bar_health = (bar_width / _maxhealth) * draw_health;
								auto bar_color = Color::Green();

								if (_health > 50.f) {
									bar_color = Color::Green();
								}
								else if (_health > 20.f && _health < 40.f) {
									bar_color = Color::Orange();
								}
								else if (_health < 20.f) {
									bar_color = Color::Red();
								}


								UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
								UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffsethealth + 4.f), bar_color);
								UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
								yoffset += 8.f;
							}

							if (m_settings::AuthorizedPlayers)
							{
								const auto authorized_players = building_priv->authorizedPlayers();
								if (IsAddressValid(authorized_players))
								{
									for (auto it = 0; it < authorized_players->_size; it++)
									{
										const auto current = authorized_players->_items->m_Items[it];
										if (IsAddressValid(current))
										{
											const auto str = current->username();
											if (IsAddressValid(str))
											{
												auto camera = UnityEngine::Camera::get_main();

												if (IsAddressValid(camera))
												{
													auto distance = camera->get_positionz().get_3d_dist(BaseEntity->get_positionz());

													if (distance <= m_settings::AuthorizedPlayersDistance)
													{
														char retstr[256];
														sprintf(retstr, XS("%s"), str->string_safe().c_str());

														UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), retstr, Color::Turquoise(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
														yoffset += 12.f;
													}
												}

											}
										}
									}
								}
							}
						}

					}
				}

				if (distance <= m_settings::MaxCrateDistance)
				{
					if (m_settings::BasicCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_basic") == Hash(name, false))
							{
								std::string player_name = XS("Basic Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}

					if (m_settings::NormalCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_normal_2") == Hash(name, false) || HASH("crate_normal_2_food") == Hash(name, false) || HASH("crate_normal_2_medical") == Hash(name, false))
							{
								std::string player_name = XS("Normal Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}

					if (m_settings::MilitaryCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_normal") == Hash(name, false))
							{
								std::string player_name = XS("Military Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}

					if (m_settings::EliteCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_elite") == Hash(name, false))
							{
								std::string player_name = XS("Elite Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}
				
				if (distance <= m_settings::MaxSupplyDropDistance)
				{
					if (m_settings::SupplyDrop)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("supply_drop") == Hash(name, false))
							{
								std::string player_name = XS("Airdrop");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
				{
					if (distance <= m_settings::MaxFoodDistance)
					{
						if (m_settings::Mushroom)
						{
							if (HASH("mushroom-cluster-6") == Hash(name, false) || HASH("mushroom-cluster-5") == Hash(name, false))
							{
								auto FoodColor = Color{ m_settings::MushRoomColor[0], m_settings::MushRoomColor[1], m_settings::MushRoomColor[2], m_settings::MushRoomColor[3] };
								std::string player_name = XS("Mushroom");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

								if (m_settings::FoodIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("mushroom.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (m_settings::Pumpkin)
						{
							float half = (box.z - box.x) / 2;
							if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
							{
								if (HASH("pumpkin-collectable") == Hash(name, false))
								{
									auto FoodColor = Color{ m_settings::PumpkinColor[0], m_settings::PumpkinColor[1], m_settings::PumpkinColor[2], m_settings::PumpkinColor[3] };
									std::string player_name = XS("Pumpkin");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

									if (m_settings::FoodIcons)
									{
										UnityEngine::Texture2D* texture = nullptr;
										if (!texture)
										{
											texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("pumpkin.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
										}

										UnityEngine::GUI::SetColor(Color::White());
										UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
									}
								}
							}
						}
						
						if (m_settings::Corn)
						{
							float half = (box.z - box.x) / 2;
							if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
							{
								if (HASH("corn-collectable") == Hash(name, false))
								{
									auto FoodColor = Color{ m_settings::CornColor[0], m_settings::CornColor[1], m_settings::CornColor[2], m_settings::CornColor[3] };
									std::string player_name = XS("Corn");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

									if (m_settings::FoodIcons)
									{
										UnityEngine::Texture2D* texture = nullptr;
										if (!texture)
										{
											texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("corn.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
										}

										UnityEngine::GUI::SetColor(Color::White());
										UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
									}
								}
							}
						}

						if (m_settings::Potato)
						{
							float half = (box.z - box.x) / 2;
							if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
							{
								if (HASH("potato-collectable") == Hash(name, false))
								{
									auto FoodColor = Color{ m_settings::PotatoColor[0], m_settings::PotatoColor[1], m_settings::PotatoColor[2], m_settings::PotatoColor[3] };

									std::string player_name = XS("Potato");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;
									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

									if (m_settings::FoodIcons)
									{
										UnityEngine::Texture2D* texture = nullptr;
										if (!texture)
										{
											texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("potato.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
										}

										UnityEngine::GUI::SetColor(Color::White());
										UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
									}
								}
							}
						}
					}

					if (distance <= m_settings::MaxCollectableDistance) {

						if (m_settings::StoneCollectable)
						{
							if (HASH("stone-collectable") == Hash(name, false))
							{
								auto StoneColor = Color{ m_settings::StoneColor[0], m_settings::StoneColor[1], m_settings::StoneColor[2], m_settings::StoneColor[3] };

								std::string player_name = XS("Stone Collectable");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), StoneColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::MetalCollectable)
						{
							if (HASH("metal-collectable") == Hash(name, false))
							{
								auto MetalColor = Color{ m_settings::MetalColor[0], m_settings::MetalColor[1], m_settings::MetalColor[2], m_settings::MetalColor[3] };
								std::string player_name = XS("Metal Collectable");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), MetalColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

							}
						}

						if (m_settings::SulfurCollectable)
						{
							if (HASH("sulfur-collectable") == Hash(name, false))
							{
								auto SulfurColor = Color{ m_settings::SulfurColor[0], m_settings::SulfurColor[1], m_settings::SulfurColor[2], m_settings::SulfurColor[3] };
								std::string player_name = XS("SulfurOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), SulfurColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::ResourceEntity::StaticClass()))
				{
					if (distance <= m_settings::MaxOreDistance)
					{
						if (m_settings::StoneOre)
						{
							if (HASH("stone-ore") == Hash(name, false) || HASH("ore_stone") == Hash(name, false))
							{
								auto StoneColor = Color{ m_settings::StoneColor[0], m_settings::StoneColor[1], m_settings::StoneColor[2], m_settings::StoneColor[3] };

								std::string player_name = XS("StoneOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), StoneColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								if (m_settings::OreIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("stones.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale - 2, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (m_settings::MetalOre)
						{
							if (HASH("metal-ore") == Hash(name, false) || HASH("ore_metal") == Hash(name, false))
							{
								auto MetalColor = Color{ m_settings::MetalColor[0], m_settings::MetalColor[1], m_settings::MetalColor[2], m_settings::MetalColor[3] };
								std::string player_name = XS("MetalOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), MetalColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								if (m_settings::OreIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("metal.ore.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale - 2, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (m_settings::SulfurOre)
						{
							if (HASH("sulfur-ore") == Hash(name, false) || HASH("ore_sulfur") == Hash(name, false))
							{
								auto SulfurColor = Color{ m_settings::SulfurColor[0], m_settings::SulfurColor[1], m_settings::SulfurColor[2], m_settings::SulfurColor[3] };
								std::string player_name = XS("SulfurOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), SulfurColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								if (m_settings::OreIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("sulfur.ore.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale - 2, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::DroppedItemContainer::StaticClass()) || BaseEntity->IsA(AssemblyCSharp::PlayerCorpse::StaticClass()))
				{
					if (distance <= m_settings::MaxPlayerDropsDistance)
					{
						if (m_settings::BackPack)
						{
							if (HASH("item_drop_backpack") == Hash(name, false))
							{
								auto BackpackColor = Color{ m_settings::BackPackColor[0], m_settings::BackPackColor[1], m_settings::BackPackColor[2], m_settings::BackPackColor[3] };
								std::string player_name = XS("Backpack");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), BackpackColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Corpse)
						{
							if (HASH("player_corpse") == Hash(name, false))
							{
								auto CorpseColor = Color{ m_settings::CorpseColor[0], m_settings::CorpseColor[1], m_settings::CorpseColor[2], m_settings::CorpseColor[3] };
								std::string player_name = XS("Corpse");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), CorpseColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::StashContainer::StaticClass()))
				{
					if (distance <= m_settings::MaxCollectableDistance) {
						if (m_settings::Stash)
						{
							auto entity = static_cast<AssemblyCSharp::BaseEntity*>(BaseEntity);
							{
								auto flags = entity->flags();

								if (flags & 2048)
								{
									std::string player_name = XS("Stash");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::AutoTurret::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::AutoTurret)
						{
							if (HASH("autoturret_deployed") == Hash(name, false))
							{
								float yoffset = 0;
								auto turret_entity = static_cast<AssemblyCSharp::AutoTurret*>(BaseEntity);
								auto turret_baseentity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

								auto TurretColor = Color{ m_settings::TurretColor[0], m_settings::TurretColor[1], m_settings::TurretColor[2], m_settings::TurretColor[3] };
								auto flags = turret_entity->flags();
								/*if (flags & 2) {
									TurretColor = Color{ m_settings::TurretColor[0], m_settings::TurretColor[1], m_settings::TurretColor[2], m_settings::TurretColor[3] };
								}
								else
								{
									TurretColor = Color(0, 255, 0, 255.f);
								}*/
								
								
								std::string player_name = XS("Turret");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), TurretColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								auto aimDir = turret_entity->aimDir();
								auto muzzlePos = turret_entity->muzzlePos()->get_position();
								auto sightRange = turret_entity->sightRange();
								auto authorizedPlayers = turret_entity->authorizedPlayers();
								

								auto _health = turret_baseentity->_health();
								auto _maxhealth = turret_baseentity->_maxHealth();

								Vector2 W2SmuzzlePos;
								Vector2 W2SairDir;

								if (m_settings::TurretHealth) {
									float draw_health = _health;
									float yoffsethealth = 7.f;
									if (_health > _maxhealth) {
										draw_health = _maxhealth;
									}

									const auto bar_width = 30;
									const auto bar_health = (bar_width / _maxhealth) * draw_health;
									auto bar_color = Color::Green();

									if (_health > 50.f) {
										bar_color = Color::Green();
									}
									else if (_health > 20.f && _health < 40.f) {
										bar_color = Color::Orange();
									}
									else if (_health < 20.f) {
										bar_color = Color::Red();
									}


									UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
									UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffsethealth + 4.f), bar_color);
									UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
									yoffset += 8.f;
								}

								if (m_settings::TurretEquippedFlags) {
									if (flags & 512) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Equipped"), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::TurretOnFlags)
								{
									if (flags & 2) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("ON"), Color::Red(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
									else
									{
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("OFF"), Color::Green(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::TurretTurningFlag) {
									if (turret_entity->wasTurning()) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Turning"), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::TurretRange) {
									std::string player_name = XS("Range:");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
									yoffset += 12.f;
									UnityEngine::DDraw().Line(muzzlePos, Vector3(muzzlePos + (aimDir * sightRange)), Color::Red(), 0.2f, true, false);
								}

								if (m_settings::TurretAuthorizedPlayers) {
									if (authorizedPlayers) {
										for (auto i = 0; i < authorizedPlayers->_size; i++) {
											const auto current = authorizedPlayers->_items->m_Items[i];
											if (current) {
												const auto str = current->username();
												if (str) {


													char retstr[256];
													sprintf(retstr, XS("%s [%dm]"), str->string_safe().c_str(), (int)distance);


													//if (UnityEngine::Input::GetKey(RustStructs::F))
													//{
													//	char stringstr[256];
													//	sprintf(stringstr, XS("client.reportplayer %llu"), current->userid());
													//	AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), stringstr, nullptr);
													//}

													/*std::string player_name = str->string_safe();
													char str[128];
													sprintf(str, XS("[%dm]"), (int)distance);
													player_name = player_name + " " + str;*/
													UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), retstr, Color::Turquoise(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
													yoffset += 12.f;
												}
											}
										}
									}
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::BearTrap::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::BearTrap)
						{
							if (HASH("beartrap") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("BearTrap");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::GunTrap::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::ShotgunTrap)
						{
							if (HASH("guntrap.deployed") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("Shotgun Trap");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Barricade::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::SpikesTrap)
						{
							if (HASH("spikes.floor") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("Spikes Trap");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::FlameTurret::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::FlameTurret)
						{
							if (HASH("flameturret.deployed") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("FlameTurret");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Landmine::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::LandMine)
						{
							if (HASH("landmine") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("LandMine");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::SamSite::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::SamSite)
						{
							if (HASH("sam_site_turret_deployed") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("Samsite");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::HackableLockedCrate::StaticClass()))
				{
					if (distance <= m_settings::MaxCrateDistance)
					{
						if (m_settings::HackableCrate)
						{
							auto hackablecrate = reinterpret_cast<AssemblyCSharp::HackableLockedCrate*>(BaseEntity);
							auto hackablecrate_entity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

							if (HASH("codelockedhackablecrate") == Hash(name, false) || HASH("codelockedhackablecrate_oilrig") == Hash(name, false))
							{
								float yoffset = 0;
								auto CrateColor = Color{ m_settings::CrateColor[0], m_settings::CrateColor[1], m_settings::CrateColor[2], m_settings::CrateColor[3] };
								std::string player_name = XS("HackableCrate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								auto flags = hackablecrate_entity->flags();
								auto hackSeconds = hackablecrate->hackSeconds();
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), CrateColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								if (m_settings::HackableCrateFlags) {
									if (flags & 256) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Hacked"), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
									else if (flags & 128) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Hacking.."), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::HackableCrateTimer) {
									auto TimeRemaining = 900 - (int)hackSeconds;
									std::string player_name = XS("Timer");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									if (flags & 256) {}
									else {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
				{
					if (distance <= m_settings::MaxCrateDistance)
					{
						if (m_settings::BradleyCrate)
						{
							auto crate_entity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

							if (HASH("bradley_crate") == Hash(name, false))
							{
								float yoffset = 0;
								auto CrateColor = Color{ m_settings::CrateColor[0], m_settings::CrateColor[1], m_settings::CrateColor[2], m_settings::CrateColor[3] };
								std::string player_name = XS("BradleyCrate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								auto flags = crate_entity->flags();
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), CrateColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;
								if (flags & 4)
									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("OnFire"), Color::Red(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

							}
						}

						if (m_settings::HeliCrate)
						{
							auto crate_entity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

							if (HASH("heli_crate") == Hash(name, false))
							{
								float yoffset = 0;
								auto CrateColor = Color{ m_settings::CrateColor[0], m_settings::CrateColor[1], m_settings::CrateColor[2], m_settings::CrateColor[3] };
								std::string player_name = XS("HeliCrate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								auto flags = crate_entity->flags();
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), CrateColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;
								if (flags & 4)
									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("OnFire"), Color::Red(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Tugboat::StaticClass()))
				{
					if (m_settings::TugBoat)
					{
						if (distance <= m_settings::MaxVehicleDistance)
						{
							auto thugboat = reinterpret_cast<AssemblyCSharp::Tugboat*>(BaseEntity);

							if (thugboat)
							{
								auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
								float yoffset = 0;
								std::string player_name = XS("TugBoat");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								float draw_health = thugboat->_health();
								float yoffsethealth = 7.f;
								if (thugboat->_health() > thugboat->_maxHealth()) {
									draw_health = thugboat->_maxHealth();
								}

								const auto bar_width = 30;
								const auto bar_health = (bar_width / thugboat->_maxHealth()) * draw_health;
								auto bar_color = Color::Green();

								if (thugboat->_health() > 50.f) {
									bar_color = Color::Green();
								}
								else if (thugboat->_health() > 20.f && thugboat->_health() < 40.f) {
									bar_color = Color::Orange();
								}
								else if (thugboat->_health() < 20.f) {
									bar_color = Color::Red();
								}


								UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
								UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffsethealth + 4.f), bar_color);
								UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
								yoffset += 8.f;
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::BaseVehicle::StaticClass()))
				{
					if (distance <= m_settings::MaxVehicleDistance)
					{
						if (m_settings::Minicopter)
						{
							if (HASH("minicopter.entity") == Hash(name, false))
							{
								auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
								std::string player_name = XS("Minicopter");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::ScrapHeli)
						{
							if (HASH("scraptransporthelicopter") == Hash(name, false))
							{
								auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
								std::string player_name = XS("ScrapHeli");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						//if (m_settings::AttackHeli)
						//{
						//	if (HASH("attackhelicopter") == Hash(name, false))
						//	{
						//		auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
						//		std::string player_name = XS("AttackHeli");
						//		char str[256];
						//		sprintf(str, XS("[%dm]"), (int)distance);
						//		player_name = player_name + " " + str;
						//		UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
						//	}
						//}

						if (m_settings::Rowboat)
						{
							if (HASH("rowboat") == Hash(name, false))
							{
								auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
								std::string player_name = XS("RowBoat");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Rhib)
						{
							if (HASH("RHIB") == Hash(name, false))
							{
								auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
								std::string player_name = XS("RHIB");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Workbench::StaticClass()))
				{
					if (distance <= m_settings::MaxDeployableDistance)
					{
						if (m_settings::T1Workbench)
						{
							if (HASH("workbench1.deployed") == Hash(name, false))
							{
								auto DeployableColor = Color{ m_settings::DeployableColor[0], m_settings::DeployableColor[1], m_settings::DeployableColor[2], m_settings::DeployableColor[3] };
								std::string player_name = XS("T1 Workbench");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::T2Workbench)
						{
							if (HASH("workbench2.deployed") == Hash(name, false))
							{
								auto DeployableColor = Color{ m_settings::DeployableColor[0], m_settings::DeployableColor[1], m_settings::DeployableColor[2], m_settings::DeployableColor[3] };
								std::string player_name = XS("T2 Workbench");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::T3Workbench)
						{
							if (HASH("workbench3.deployed") == Hash(name, false))
							{
								auto DeployableColor = Color{ m_settings::DeployableColor[0], m_settings::DeployableColor[1], m_settings::DeployableColor[2], m_settings::DeployableColor[3] };
								std::string player_name = XS("T3 Workbench");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}
				if (m_settings::BradleyAPC)
				{
					if (BaseEntity->IsA(AssemblyCSharp::BradleyAPC::StaticClass()))
					{
						if (distance <= m_settings::MaxAPCDistance)
						{
							auto base_heli = reinterpret_cast<AssemblyCSharp::BradleyAPC*>(BaseEntity);
							if (base_heli)
							{
								float yoffset = 0;
								auto HeliColor = Color{ m_settings::BradleyColor[0], m_settings::BradleyColor[1], m_settings::BradleyColor[2], m_settings::BradleyColor[3] };
								std::string player_name = XS("Bradley");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), HeliColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								//if (m_settings::BradleyhealthBar)
								//{
								//	float bar_health = 0;
								//	auto health = base_heli->_health();
								//	//auto max_health = base_player->_maxHealth();
								//	float max_health = 100.f;
								//	float draw_health = health;

								//	if (health > max_health)
								//	{
								//		draw_health = max_health;
								//	}

								//	const auto bar_width = 30;
								//	bar_health = (bar_width / max_health) * draw_health;

								//	auto bar_color = Color::Green();
								//	if (health > 50.f)
								//	{
								//		bar_color = Color::Green();
								//	}
								//	else if (health > 20.f && health < 40.f)
								//	{
								//		bar_color = Color::Orange();
								//	}
								//	else if (health < 20.f)
								//	{
								//		bar_color = Color::Red();
								//	}

								//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());
								//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_health, 4.f }, bar_color);
								//	//UnityEngine::GL::Rectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());

								//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 3.f), Color::Black());
								//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffset + 3.f), bar_color);
								//	UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 4.f), Color::Black());
								//	yoffset += 13;
								//}
							}

						}

					}
				}
				if (m_settings::PatrolHelicopter)
				{
					if (BaseEntity->IsA(AssemblyCSharp::PatrolHelicopter::StaticClass()))
					{
						if (distance <= m_settings::MaxAPCDistance)
						{
							//if (m_settings::PatrolHelicopter)
							{
								auto base_heli = reinterpret_cast<AssemblyCSharp::PatrolHelicopter*>(BaseEntity);
								if (base_heli)
								{
									float yoffset = 0;
									auto HeliColor = Color{ m_settings::HeliColor[0], m_settings::HeliColor[1], m_settings::HeliColor[2], m_settings::HeliColor[3] };
									std::string player_name = XS("Patrol Helicopter");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;
									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), HeliColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
									yoffset += 12.f;

									//if (m_settings::healthBar)
									//{
									//	float bar_health = 0;
									//	auto health = base_heli->_health();
									//	//auto max_health = base_player->_maxHealth();
									//	float max_health = 100.f;
									//	float draw_health = health;

									//	if (health > max_health)
									//	{
									//		draw_health = max_health;
									//	}

									//	const auto bar_width = 30;
									//	bar_health = (bar_width / max_health) * draw_health;

									//	auto bar_color = Color::Green();
									//	if (health > 50.f)
									//	{
									//		bar_color = Color::Green();
									//	}
									//	else if (health > 20.f && health < 40.f)
									//	{
									//		bar_color = Color::Orange();
									//	}
									//	else if (health < 20.f)
									//	{
									//		bar_color = Color::Red();
									//	}

									//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());
									//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_health, 4.f }, bar_color);
									//	//UnityEngine::GL::Rectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());

									//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 3.f), Color::Black());
									//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffset + 3.f), bar_color);
									//	UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 4.f), Color::Black());
									//	yoffset += 13;
									//}
								}
							}
						}
					}
				}
			}
		}
	}
}


void Visuals::CacheEntities()
{
	if (!InGame)
		return;

	if (const auto ClientEntites = AssemblyCSharp::BaseNetworkable::clientEntities())
	{
		if (const auto entityList = ClientEntites->entityList())
		{
			if (const auto EntityListVals = entityList->vals)
			{
				if (const auto EntityListBuffer = EntityListVals->buffer)
				{
					for (std::int32_t index = 0; index < EntityListVals->count; index++)
					{
						auto BaseEntity = EntityListBuffer->m_Items[index];

						if (IsAddressValid(BaseEntity))
						{

							if (!BaseEntity->net())
								continue;

							const auto EntityID = BaseEntity->prefabID();
							const auto StashID = 2568831788;
							const auto boarID = 502341109;
							const auto stagID = 1378621008;
							const auto wolfID = 2144238755;
							const auto bearID = 1799741974;
							const auto HempCollectable = 3006540952;
							const auto CornID = 3019211920;
							const auto PumpkinID = 2251957318;
							const auto PotatoID = 726972295;
							const auto mushRoomID1 = 2697239269;
							const auto mushRoomID2 = 178882626;
							const auto dieselCollectable = 1388355532;

							const auto MetalCollectable = 4060169083;
							const auto MetalOre = 3774647716;
							const auto MetalOre2 = 4225479497;
							const auto MetalOre3 = 3345228353;
							const auto OreMetal = 3327726152;

							const auto StoneCollectable = 2422310333;
							const auto StoneOre = 4124824587;
							const auto StoneOre2 = 266547145;
							const auto StoneOre3 = 723721358;
							const auto OreStone = 960501790;

							const auto SulfurCollectable = 2972237931;
							const auto SulfurOre = 3058967796;
							const auto SulfurOre2 = 1227527004;
							const auto SulfurOre3 = 2204178116;
							const auto OreSulfur = 152562243;

							const auto player_corpse = 2604534927;
							const auto player_backpack = 1519640547;

							const auto autoturret_deployed = 3312510084;

							const auto bradley_crate = 1737870479;
							const auto heli_crate = 1314849795;

							const auto patrol_heli = 3029415845;
							const auto bradley_apc = 1456850188;

							const auto cupboard_deployed = 2476970476;
							const auto crate_basic = 1603759333;
							const auto crate_normal_2 = 1546200557;
							const auto crate_normal_2_food = 2066926276;
							const auto crate_normal_2_medical = 1791916628;
							const auto crate_normal = 2857304752;
							const auto crate_elite = 3286607235;
							const auto supply_drop = 3632568684;
							const auto loot_barrel = 966676416;
							const auto oil_barrel = 3438187947;
							const auto horse = 2421623959;
							const auto thugboat = 7995600;

							const auto BearTrap = 922529517;
							const auto GunTrap = 1348746224;
							const auto FlameTurret = 4075317686;
							const auto FloorSpikes = 976279966;
							const auto LandMine = 1463807579;
							const auto SamSite = 2059775839;

							const auto Minicopter = 2278499844;
							const auto ScrapHeli = 3484163637;
							const auto RHIB = 2226588638;
							const auto Rowboat = 1283317166;

							const auto t1workbench = 2561955800;
							const auto t2workbench = 601265145;
							const auto t3workbench = 2764275075;
							//const auto Minicopter = 2278499844;

							//const auto timedexplosive = 1915331115;
							//const auto timedexplosive_deployed = 3898309212;

							//if (EntityID == timedexplosive || EntityID == timedexplosive_deployed)
							//{
							//	PrefabListTemp.push_back(PrefabList(BaseEntity));
							//}

							///*if (EntityID == horse && m_settings::horseEsp)
							//{
							//	PrefabListTemp.push_back(PrefabList(BaseEntity));
							//}

							//else if (EntityID == oil_barrel && m_settings::OilBarrel)
							//{
							//	PrefabListTemp.push_back(PrefabList(BaseEntity));
							//*/}
							if (BaseEntity->IsA(AssemblyCSharp::Tugboat::StaticClass()) && m_settings::TugBoat)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == t1workbench && m_settings::T1Workbench)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == t2workbench && m_settings::T2Workbench)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == t3workbench && m_settings::T3Workbench)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == Minicopter && m_settings::Minicopter)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == ScrapHeli && m_settings::ScrapHeli)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == RHIB && m_settings::Rhib)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == Rowboat && m_settings::Rowboat)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							//else if (BaseEntity->IsA(AssemblyCSharp::AttackHeli::StaticClass()) && m_settings::AttackHeli)
							//{
							//	PrefabListTemp.push_back(PrefabList(BaseEntity));
							//}
							else if (EntityID == BearTrap && m_settings::BearTrap)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == GunTrap && m_settings::ShotgunTrap)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == FlameTurret && m_settings::FlameTurret)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == FloorSpikes && m_settings::SpikesTrap)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == LandMine && m_settings::LandMine)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == SamSite && m_settings::SamSite)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_basic && m_settings::BasicCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_normal_2 || EntityID == crate_normal_2_medical || EntityID == crate_normal_2_food && m_settings::NormalCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_normal && m_settings::NormalCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_elite && m_settings::EliteCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == supply_drop && m_settings::SupplyDrop)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_normal && m_settings::NormalCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
	/*						else if (EntityID == loot_barrel && m_settings::LootBarrel)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}*/
							else if (BaseEntity->IsA(AssemblyCSharp::PatrolHelicopter::StaticClass()) && m_settings::PatrolHelicopter)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == heli_crate && m_settings::HeliCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == bradley_apc && m_settings::BradleyAPC)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == bradley_crate && m_settings::BradleyCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (BaseEntity->IsA(AssemblyCSharp::HackableLockedCrate::StaticClass()) && m_settings::HackableCrate)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == autoturret_deployed && m_settings::AutoTurret)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == player_corpse && m_settings::Corpse)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == player_backpack && m_settings::BackPack)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == StoneOre || EntityID == StoneOre2 || EntityID == StoneOre3 || EntityID == OreStone && m_settings::StoneOre)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == MetalOre || EntityID == MetalOre2 || EntityID == MetalOre3 || EntityID == OreMetal && m_settings::MetalOre)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == SulfurOre || EntityID == SulfurOre2 || EntityID == SulfurOre3 || EntityID == OreSulfur && m_settings::SulfurOre)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == StoneCollectable && m_settings::StoneCollectable)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == MetalCollectable && m_settings::MetalCollectable)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == SulfurCollectable && m_settings::SulfurCollectable)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == dieselCollectable && m_settings::DieselBarrel)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == HempCollectable && m_settings::Hemp)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == StashID && m_settings::Stash)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == mushRoomID1 || EntityID == mushRoomID2 && m_settings::Mushroom)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == PumpkinID && m_settings::Pumpkin)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == PotatoID && m_settings::Potato)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == CornID && m_settings::Corn)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (BaseEntity->IsA(AssemblyCSharp::WorldItem::StaticClass()) && m_settings::DroppedItems)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == cupboard_deployed && m_settings::cupboard)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else
							{
								if (m_settings::DoorSpammer)
								{
									if (BaseEntity->IsA(AssemblyCSharp::Door::StaticClass()))
									{
										auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(BaseEntity->get_transform()->get_position());

										auto ent = reinterpret_cast<AssemblyCSharp::Door*>(BaseEntity);

										if (IsAddressValid(ent) && distance <= 3.f)
										{
											if (RPC_Counter.Calculate() <= 5)
											{
												ent->KnockDoor(Features().LocalPlayer);
												RPC_Counter.Increment();
											}
										}

									}
								}

								if (m_settings::AutoUpgrade)
								{
									if (BaseEntity->IsA(AssemblyCSharp::BuildingBlock::StaticClass()))
									{
										auto block = reinterpret_cast<AssemblyCSharp::BuildingBlock*>(BaseEntity);

										if (block)
										{
											auto entity_pos = block->get_positionz();

											if (RPC_Counter.Calculate() >= 5)
											{
												continue;
											}


											Vector3 local = Features().LocalPlayer->ClosestPoint(entity_pos);
											if (local.get_3d_dist(entity_pos) <= 5.5f)
											{
												float LastGrade = 0.f;
												auto BuildingGrade = m_settings::BuildingGrade + 1;
												if (Features().LocalPlayer->lastSentTickTime() > LastGrade + 0.35f
													&& block->CanAffordUpgrade((RustStructs::BuildingGrade)BuildingGrade, 0, Features().LocalPlayer)
													&& block->CanChangeToGrade((RustStructs::BuildingGrade)BuildingGrade, 0, Features().LocalPlayer)
													&& !block->IsUpgradeBlocked()) {
													block->UpgradeToGrade((RustStructs::BuildingGrade)BuildingGrade, 0, Features().LocalPlayer);
													RPC_Counter.Increment();
													LastGrade = Features().LocalPlayer->lastSentTickTime();
												}
											}

										}
									}
								}
								continue;
							}
						}
					}

					PrefabVectorList = PrefabListTemp;
					PrefabListTemp.clear();
				}

			}

		}

	}

}


AssemblyCSharp::BasePlayer::Target Visuals::GetAimbotTargetSafe(Vector3 Source, float MaxDist)
{
	if (!InGame)
		return {};

	if (!VisiblePlayerList)
		VisiblePlayerList = AssemblyCSharp::BasePlayer::visiblePlayerList();

	auto Vals = VisiblePlayerList->vals;
	auto size = Vals->count;
	auto buffer = Vals->buffer;
	AssemblyCSharp::BasePlayer::Target best_target = AssemblyCSharp::BasePlayer::Target();

	for (std::int32_t index = 0; index < size; index++)
	{
		auto BasePlayer = buffer->m_Items[index];
		if (!IsAddressValid(BasePlayer))
			continue;

		if(!IsAddressValid(BasePlayer->net()))
			continue;

		if (!IsAddressValid(BasePlayer->playerModel()) || !IsAddressValid(BasePlayer->model()))
			continue;

		if (BasePlayer->IsDead() || BasePlayer->IsLocalPlayer() ||
			BasePlayer->playerFlags() & RustStructs::PlayerFlags::Sleeping || BasePlayer->wasDead() ||
			BasePlayer->_health() <= 0.f)
			continue;

		auto isWounded = BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded;
		if (isWounded && !m_settings::TargetWounded)
			continue;

		bool isNpc = false;
		if (BasePlayer->playerModel()->get_IsNpc()) {
			if (!m_settings::AimbotNPC)
				continue;
			isNpc = true;
		}

		AssemblyCSharp::BasePlayer::Target target;
		target.m_player = BasePlayer;

		if (target.m_player != nullptr)
		{
			if (target.m_player != BasePlayer)
			{
				target.m_player = BasePlayer;
			}
		}


		auto velocity = BasePlayer->playerModel()->newVelocity();
		target.m_velocity = velocity;

		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		int selectedAimbone = m_settings::SelectedAimbone;
		int bone = 47;
		switch (selectedAimbone) {
		case 0: // Head
			pos = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
			bone = RustStructs::bones::head;
			break;
		case 1: // neck
			pos = BasePlayer->get_bone_transform(RustStructs::bones::neck)->get_position();
			bone = RustStructs::bones::neck;
			break;
		case 2: // spine1
			pos = BasePlayer->get_bone_transform(RustStructs::bones::spine1)->get_position();
			bone = RustStructs::bones::spine1;
			break;
		case 3: // Random bone selection
			switch (my_rand() % 9) {
			case 0: // Head
				pos = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
				bone = RustStructs::bones::head;
				break;
			case 1: // pelvis
				pos = BasePlayer->get_bone_transform(RustStructs::bones::pelvis)->get_position();
				bone = RustStructs::bones::pelvis;
				break;
			case 2: // r_hip
				pos = BasePlayer->get_bone_transform(RustStructs::bones::r_hip)->get_position();
				bone = RustStructs::bones::r_hip;
				break;
			case 3: // r_foot
				pos = BasePlayer->get_bone_transform(RustStructs::bones::r_foot)->get_position();
				bone = RustStructs::bones::r_foot;
				break;
			case 4: // spine1
				pos = BasePlayer->get_bone_transform(RustStructs::bones::spine1)->get_position();
				bone = RustStructs::bones::spine1;
				break;
			case 5: // l_hand
				pos = BasePlayer->get_bone_transform(RustStructs::bones::l_hand)->get_position();
				bone = RustStructs::bones::l_hand;
				break;
			case 6: // r_upperarm
				pos = BasePlayer->get_bone_transform(RustStructs::bones::r_upperarm)->get_position();
				bone = RustStructs::bones::r_upperarm;
				break;
			case 7: // l_knee
				pos = BasePlayer->get_bone_transform(RustStructs::bones::l_knee)->get_position();
				bone = RustStructs::bones::l_knee;
				break;
			case 8: // spine4
				pos = BasePlayer->get_bone_transform(RustStructs::bones::spine4)->get_position();
				bone = RustStructs::bones::spine4;
				break;
			}
			break;
		case 4:
			bone = AssemblyCSharp::BasePlayer::ClosesestToCrosshair(ToAddress(BasePlayer));
			pos = BasePlayer->get_bone_transform(bone)->get_position();
			break;
		}

		target.m_position = pos;
		target.m_bone = bone;
		target.m_npc = isNpc;
		target.m_heli = false;

		auto distance = Source.get_3d_dist(pos);
		target.m_distance = distance;
		if (distance > MaxDist)
			continue;

		auto fov = AssemblyCSharp::get_fov(pos);
		target.m_fov = fov;

		if (target < best_target)
			best_target = target;
	}
	return best_target;
}