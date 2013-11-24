//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//------------------
// Agent_Enemy.hpp |
//-------------------------------------------
// Declares the Agent::Enemy class, which
// represents a hostile agent.
//-------------------------------------------

#ifndef AGENT_ENEMY_H
#define AGENT_ENEMY_H

// Required headers:
#include <../Headers/Agent.hpp>
#include <../Headers/Agent_Player.hpp>
#include <../Headers/Math_Functional.hpp>
using namespace Math;

namespace Agent {

	class Player;

	class Enemy : public Agent {

	public:
		Enemy(const Player& player, double terrain_size);
		void update(const Heightmap& hmap, const Player& player, double timestep);
		void render() const;

	private:
		void tex(float s, float t) const;
		int frame;
	};
}


#endif
