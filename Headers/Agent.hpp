//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//------------
// Agent.hpp |
//-------------------------------------------
// Declares the virtual Agent::Agent class,
// which is the base class for all agents in
// the game.
//-------------------------------------------

#ifndef AGENT_H
#define AGENT_H


// Required headers:
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Functional.hpp>
using namespace Math;


namespace Agent {

	class Agent {

	protected:
		// Agent state variables:
		vec3 loc, vel;
		double size, coll1, coll2;
		// NB: coll1 and coll2 are arbitrary collision constants.

	public:
		Agent(const vec3& loc, double size, const vec3& vel = vec3::zero(), double coll1 = 1.34, double coll2 = 0.94) :
			loc(loc), vel(vel), size(size), coll1(coll1), coll2(coll2) {}

		// Updates the agent, performing movement and collisions:
		void update(const Heightmap& hmap, double timestep);

		// Functions to get current position and velocity:
		const vec3& getLoc() const {
			return loc;
		}
		const vec3& getVel() const {
			return vel;
		}
	};
}

#endif
