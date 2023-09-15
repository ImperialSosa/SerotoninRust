#include "Visuals.hpp"
#include "../../Hooking/Hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"

#include <array>
#include <algorithm>
inline std::array<int, 20> valid_bones = {
		1, 2, 3, 5, 6, 14, 15, 17, 18, 21, 23, 24, 25, 26, 27, 48, 55, 56, 57, 76
};

box_bounds Visuals::get_bounds(AssemblyCSharp::BasePlayer* player, float expand) {
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
			auto VisCheckColor = is_Visible ? Color{ m_settings::VisCheck_Color[0], m_settings::VisCheck_Color[1], m_settings::VisCheck_Color[2], m_settings::VisCheck_Color[3] } : Color{ m_settings::DrawBox_Color[0], m_settings::DrawBox_Color[1], m_settings::DrawBox_Color[2], m_settings::DrawBox_Color[3] };
			auto DrawBox_Color = Color{ m_settings::DrawBox_Color[0], m_settings::DrawBox_Color[1], m_settings::DrawBox_Color[2], m_settings::DrawBox_Color[3] };
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

			auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget();
			if (!m_target.m_player)
				return;

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
			else if (BasePlayer->IsDead() && m_settings::DrawDead)
				BoxColor = Dead_Color;
			else if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::SafeZone && m_settings::DrawSafezone)
				BoxColor = Safezone_Color;
			else
				BoxColor = m_settings::EspVisCheck ? VisCheckColor : DrawBox_Color;

			if (m_settings::BoxEsp)
			{
				UnityEngine::GL::Rectangle(Vector2(bo.left, bo.top), Vector2(bo.right, bo.bottom), BoxColor.GetUnityColor());
			}

			if (m_settings::CornerBox)
			{
				DrawCornerBox(bo.left, bo.top, bo.right, bo.bottom, BoxColor.GetUnityColor());
			}

			if (m_settings::Target_Indicator)
			{
				if (BasePlayer == m_target.m_player)
				{
					UnityEngine::GL::TextCenter(Vector2(headPos.x, headPos.y - yoffsethead), XS("Target"), BoxColor, Color::Black(), m_settings::fontsize);
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

			if (m_settings::healthBar)
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

				//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());
				//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_health, 4.f }, bar_color);
				//UnityEngine::GL::Rectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());

				UnityEngine::GL::RectangleFilled(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2(footPos.x + (bar_width / 2), bo.bottom + yoffset + 4.f), Color::Black());
				UnityEngine::GL::RectangleFilled(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2((footPos.x - (bar_width / 2)) + bar_health, bo.bottom + yoffset + 4.f), bar_color);
				UnityEngine::GL::Rectangle(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2(footPos.x + (bar_width / 2), bo.bottom + yoffset + 4.f), Color::Black());
				yoffset += 13;
			}

			if (m_settings::nameEsp)
			{
				if (m_settings::TagsVisCheck)
				{
					if (npc)
					{
						std::string player_name = "Scientist";
						char str[128];
						sprintf(str, XS("[%dm]"), (int)distance);
						player_name = player_name + " " + str;

						UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), BoxColor.GetUnityColor(), Color::Black(), m_settings::fontsize);
					}
					else
					{
						if (IsAddressValid(BasePlayer->get_displayName())) //decrypted
						{
							std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
							char str[128];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;

							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), BoxColor.GetUnityColor(), Color::Black(), m_settings::fontsize);
						}

					}
					yoffset += 13;
				}
				else
				{
					if (npc)
					{
						std::string player_name = "Scientist";
						char str[128];
						sprintf(str, XS("[%dm]"), (int)distance);
						player_name = player_name + " " + str;
		
						UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), NameTag_Color.GetUnityColor(), Color::Black(), m_settings::fontsize);
					}
					else
					{
						if (IsAddressValid(BasePlayer->get_displayName())) //decrypted
						{
							std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
							char str[128];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;
							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), NameTag_Color.GetUnityColor(), Color::Black(), m_settings::fontsize);
						}
					}

					yoffset += 13;
				}
			}

			if (m_settings::helditem)
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
								UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), BoxColor.GetUnityColor(), Color::Black(), m_settings::fontsize);
								yoffset += 13;
							}
							else
							{
								UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), HeldItem_Color.GetUnityColor(), Color::Black(), m_settings::fontsize);
								yoffset += 13;
							}
						}
					}
				}
			}

			if (m_settings::BaseCheck)
			{
				Vector3 position = BasePlayer->get_bone_transform(47)->get_position() + Vector3(0.f, 500.f, 0.f);
				UnityEngine::RaycastHit hitInfo;
				if (AssemblyCSharp::GamePhysics::Trace(UnityEngine::Ray(BasePlayer->get_bone_transform(47)->get_position(), position), 0.f, hitInfo, 500.f, 2097152, RustStructs::QueryTriggerInteraction::Ignore, nullptr))
				{
					UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), XS("Inside"), Color::Red(), Color::Black(), m_settings::fontsize);
					yoffset += 13;
				}
				else
				{
					UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), XS("Outside"), Color::Green(), Color::Black(), m_settings::fontsize);
					yoffset += 13;
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
											case 0:
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
											case 1:
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
											case 2:
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
											case 3:
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
											case 4:
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

void Visuals::CachePlayers()
{
	if (!InGame)
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
	
		VisualsArrayTemp.push_back(VisualsVector(BasePlayer));
	}

	VisualsArray = VisualsArrayTemp;
	VisualsArrayTemp.clear();
}