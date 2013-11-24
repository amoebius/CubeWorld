//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//------------
// Agent.cpp |
//-------------------------------------------
// Implements the virtual Agent::Agent class,
// which is the base class for all agents in
// the game.
//-------------------------------------------


// Required headers:
#include <../Headers/Agent.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Functional.hpp>
using namespace Math;


namespace Agent {

	// Moves the agent by its velocity, and handles collisions:
	void Agent::update(const Heightmap& hmap, double timestep) {
		double ny = hmap.getHeight(loc)+size;
		loc += vel*timestep*0.03;

		// If below the surface, perform a collision using the surface normal to resolve the velocity into
		// reflected and ignored components:
		if(loc.y<=ny) {
			loc.y = ny;
			vec3 normal = hmap.getNormal(loc);
			vec3 coll = normal * (normal * vel);

			if(coll.y < 0) {
				vel -= coll1 * coll, vel *= coll2;
			}
		}
	}

}
