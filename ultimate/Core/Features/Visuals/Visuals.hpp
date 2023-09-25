#pragma once

#include "../../CRT/memory.hpp"
#include <vector>
#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

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

inline UnityEngine::AssetBundle* GeometricBundle;
inline UnityEngine::Shader* GeometricShader;
inline UnityEngine::Material* GeometricMaterial;

inline UnityEngine::AssetBundle* LightningBundle;
inline UnityEngine::Shader* LightningShader;
inline UnityEngine::Material* LightningMaterial;

inline UnityEngine::AssetBundle* WireFrameBundle;
inline UnityEngine::Shader* WireFrameShader;
inline UnityEngine::Material* WireFrameMaterial;

static UnityEngine::AssetBundle* AmongUsAsset = nullptr;
static UnityEngine::AssetBundle* HerbetAsset = nullptr;
inline UnityEngine::AssetBundle* ExplosionAsset = nullptr;
inline UnityEngine::AssetBundle* GhostAsset = nullptr;
inline UnityEngine::AssetBundle* TestAsset = nullptr;

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


inline UnityEngine::GameObject* ExplosionPrefab = nullptr;
inline UnityEngine::GameObject* GhostPrefab = nullptr;
inline UnityEngine::GameObject* AmongusPrefab = nullptr;
inline UnityEngine::GameObject* HerbertPrefab = nullptr;
inline UnityEngine::GameObject* TestPrefab = nullptr;

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
};