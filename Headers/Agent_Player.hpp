//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//------------------
// Agent_Player.hpp |
//-------------------------------------------
// Declares the Agent::Player class, which
// represents the human player.
//-------------------------------------------

#ifndef AGENT_PLAYER_H
#define AGENT_PLAYER_H

// Required headers:
#include <../Headers/Agent.hpp>
#include <../Headers/Agent_Enemy.hpp>
#include <../Headers/Math_Functional.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Graphics_Camera.hpp>
using namespace Math;

namespace Agent {

	class Player : public Agent {
	public:
		Player(const vec3& loc = vec3::zero()) : Agent(loc, 150) {}
		void update(const Heightmap& hmap, const Graphics::Camera& cam, double timestep);
		double update(const Enemy& enemy);
	};

}


#endif
