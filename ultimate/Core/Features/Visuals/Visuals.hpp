#pragma once

#include "../../CRT/memory.hpp"
#include <vector>
#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../Features/Features.hpp"

inline UnityEngine::AssetBundle* font_bundle;

inline UnityEngine::AssetBundle* FireBundleA;
inline UnityEngine::Shader* FireShaderA;
inline UnityEngine::Material* FireMaterialA;

inline UnityEngine::AssetBundle* FireBundleB;
inline UnityEngine::Shader* FireShaderB;
inline UnityEngine::Material* FireMaterialB;

inline UnityEngine::AssetBundle* ColorBundle;
inline UnityEngine::Shader* ColorShader;
inline UnityEngine::Material* ColorMaterial;

inline UnityEngine::AssetBundle* GalaxyBundle;
inline UnityEngine::Shader* GalaxyShader;
inline UnityEngine::Material* GalaxyMaterial;
static UnityEngine::AssetBundle* AmongUsAsset = nullptr;
static UnityEngine::AssetBundle* HerbetAsset = nullptr;
inline UnityEngine::AssetBundle* GeometricBundle;
inline UnityEngine::Shader* GeometricShader;
inline UnityEngine::Material* GeometricMaterial;

inline UnityEngine::AssetBundle* LightningBundle;
inline UnityEngine::Shader* LightningShader;
inline UnityEngine::Material* LightningMaterial;

inline UnityEngine::AssetBundle* WireFrameBundle;
inline UnityEngine::Shader* WireFrameShader;
inline UnityEngine::Material* WireFrameMaterial;

class VisualsVector {
public:
	VisualsVector(AssemblyCSharp::BasePlayer* player)
	{
		this->BasePlayer = player;
	}
public:
	AssemblyCSharp::BasePlayer* BasePlayer;
};


inline std::vector< VisualsVector> VisualsArray;
inline std::vector< VisualsVector> VisualsArrayTemp;


inline UnityEngine::GameObject* ExplosionAsset = nullptr;
inline UnityEngine::GameObject* AmongusPrefab = nullptr;
inline UnityEngine::GameObject* HerbertPrefab = nullptr;

class PrefabList {
public:
	PrefabList(AssemblyCSharp::BaseNetworkable* _This)
	{
		if ((_This))
		{
			this->CachedEntity = _This;
		}
	}

	AssemblyCSharp::BaseNetworkable* CachedEntity;

	// Equality comparison operator
	bool operator==(const PrefabList& other) const {
		// Define your comparison logic here
		return (CachedEntity == other.CachedEntity);
	}
};

inline std::vector< PrefabList> PrefabVectorList;
inline std::vector< PrefabList> PrefabListTemp;


inline float timee = 120.f;

struct Explosion {
public:
	std::string name;
	float timeSince;
	Vector3 position;
};

class LogSystem {
public:
	static inline int max_entries = 10;

	static inline std::vector<Explosion> loggedExplosions = std::vector<Explosion>();

	static inline void LogExplosion(std::string type, Vector3 pos) {
		if (!InGame)
			return;

		bool explosionCollision = false;
		std::vector<Explosion>::iterator it;
		for (it = loggedExplosions.begin(); it != loggedExplosions.end(); it++) {
			Vector2 explPos;
			if (it->position.Distance(pos) <= 25.0f) {
				explosionCollision = true;
				break;
			}
		}
		if (!explosionCollision) {
			Explosion explosion = Explosion();
			char str[256];
			sprintf(str, XS("%s Raid"), type.c_str());
			explosion.name = str;
			explosion.position = pos;
			explosion.timeSince = UnityEngine::Time::get_realtimeSinceStartup();
			loggedExplosions.push_back(explosion);
		}
	}

	static inline void RenderExplosions() {
		if (!InGame)
			return;

		if (!IsAddressValid(Features().LocalPlayer))
			return;

		for (int i = 0; i < LogSystem::loggedExplosions.size(); i++) {
			if ((UnityEngine::Time::get_realtimeSinceStartup() - LogSystem::loggedExplosions[i].timeSince) >= m_settings::MaxRaidTimer) {
				LogSystem::loggedExplosions.erase(LogSystem::loggedExplosions.begin() + i);
				continue;
			}
			Explosion explosion = LogSystem::loggedExplosions.at(i);

			Vector2 explPos;

			if (explosion.position.Distance(Features().LocalPlayer->get_transform()->get_position()) <= m_settings::MaxExplosionDistance)
			{
				if (UnityEngine::WorldToScreen(explosion.position, explPos))
				{
					std::string string;
					char str[256];
					sprintf(str, XS("%s [%1.0fm] [%d]"), explosion.name.c_str(), explosion.position.get_3d_dist(Features().LocalPlayer->get_transform()->get_position()), (int)(m_settings::MaxRaidTimer - (UnityEngine::Time::get_realtimeSinceStartup() - LogSystem::loggedExplosions[i].timeSince)));
					string += str;
					UnityEngine::GL().TextCenter(explPos, string.c_str(), Color::White(), Color::Black(), m_settings::fontsize);
				}
			}
		
		}
	}
};
class Visuals {
public:
	static auto Instance() -> Visuals*
	{
		Visuals obj;
		return &obj;
	}
	box_bounds get_bounds(AssemblyCSharp::BasePlayer* player, float expand = 0);
public:
	void CachePlayers();
	void DrawPlayers();
	using List = FPSystem::ListDictionary< uint64_t, AssemblyCSharp::BasePlayer* >;
	List* VisiblePlayerList ;

	void CacheEntities();
	void RenderEntities();

public:
	AssemblyCSharp::BasePlayer::Target GetAimbotTargetSafe(Vector3 Source, float MaxDist = 500);
};