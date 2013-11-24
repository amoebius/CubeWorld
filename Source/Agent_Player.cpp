//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//------------------
// Agent_Player.cpp |
//-------------------------------------------
// Implements the Agent::Player class, which
// represents the human player.
//-------------------------------------------


// Required headers:
#include "glb.h"
#include <../Headers/Agent.hpp>
#include <../Headers/Agent_Player.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Functional.hpp>
#include <../Headers/Graphics_Camera.hpp>
using namespace Math;

// Player movement constants:
static const double walkTolerance = 10, stillTolerance = 1;

namespace Agent {

	// Updates a player based on user input:
	void Player::update(const Heightmap& hmap, const Graphics::Camera& cam, double timestep) {
		double height = hmap.getHeight(loc)+size;
		vel -= vec3::Y()*0.008*timestep;

		// If we can walk:
		if(loc.y-walkTolerance < height) {

			// Apply motion along cardinal directions if any of the keys are pressed, or else have them stand still:
			if(KEY(17)||KEY(30)||KEY(31)||KEY(32)) {
				vec3 snorm = hmap.getNormal(loc);
				vel += cam.right().cross(snorm).norm() * (0.6*KEY(31) - KEY(17)) * 0.06*timestep;
				vel += cam.ahead().cross(snorm).norm() * (KEY(32) - KEY(30)) * 0.05*timestep;
			} else if(vel.abs2()<3) vel = vec3::zero();

		} else if(loc.y-stillTolerance < height && vel.abs2()<3) {
			vel = vec3::zero();
		}

		// Jetpack and gravity:
		vel += cam.up()*KEY(57)*0.07*timestep - vec3::Y()*timestep*0.03;
		// Resistance to motion:
		vel *= pow(0.7, 0.001*timestep);
		// Superclass update:
		Agent::update(hmap, timestep);
	}

	double Player::update(const Enemy& enemy) {
		vec3 el = enemy.getLoc();
		vel += (el-loc).norm() * 6000 / (pow((el-loc).abs(),1.83)+80);

		if((el-loc).abs() < 250) return 0.005;
		return 0;
	}

};
