#pragma once

#include "../../CRT/memory.hpp"
#include <vector>
#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

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

class Visuals {
public:
	static auto Instance() -> Visuals*
	{
		Visuals obj;
		return &obj;
	}
public:
	void CachePlayers();
	void DrawPlayers();
	using List = FPSystem::ListDictionary< uint64_t, AssemblyCSharp::BasePlayer* >;
	List* VisiblePlayerList ;
};