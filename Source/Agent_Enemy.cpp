//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//------------------
// Agent_Enemy.cpp |
//-------------------------------------------
// Implements the Agent::Enemy class, which
// represents a hostile agent.
//-------------------------------------------


// Required headers:
#include <../Headers/Agent.hpp>
#include <../Headers/Agent_Player.hpp>
#include <../Headers/Agent_Enemy.hpp>
#include <../Headers/Random.hpp>
#include <cmath>
#include <cstdlib>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Functional.hpp>
#include <../Headers/Graphics_GL.hpp>
#include <../Headers/Media.hpp>
#include <../Headers/Macro.hpp>
#include "glb.h"
#include "glb3D.h"
using namespace Math;

// Speed constant:
static const double enemySpeed = 0.064;

namespace Agent {

	// Constructor, which builds an enemy at a random nearby location:
	Enemy::Enemy(const Player& player, double terrain_size) :
		Agent(vec3(player.getLoc().x+Random::Double(-terrain_size,terrain_size), terrain_size*0.8, player.getLoc().z+Random::Double(-terrain_size,terrain_size)), 200), frame(rand()%94) {}

	// Updates the enemy's position and velocity:
	void Enemy::update(const Heightmap& hmap, const Player& player, double timestep) {
		vel += (player.getLoc()-loc).norm() * enemySpeed * timestep + vec3(Random::Double(-1,1),Random::Double(-1,1),Random::Double(-1,1))*0.1*timestep;
		vel *= pow(0.87, timestep * 0.001);
		frame = (frame+1)%94;
		// Superclass update:
		Agent::update(hmap, timestep);
	}

	// Renders the enemy:
	// 1./12 1./4
	void Enemy::render() const {
		X_SETTEXTURE(Media::Texture::Enemy,-1);
		glEnable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glBlendFunc(GL_ONE, GL_ONE);
		glPushMatrix();
		Graphics::GL::translate(loc);

		float modelview[16];
		glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
		fo(i,3) fo(j,3) modelview[i*4+j] = 90*(i==j);
		glLoadMatrixf(modelview);


		glBegin(GL_QUADS);

		// Back
		glNormal3d(0,0,1);
		tex(1,0);
		glVertex3d(1,0,1);
		tex(1,1);
		glVertex3d(1,1,1);
		tex(0,1);
		glVertex3d(0,1,1);
		tex(0,0);
		glVertex3d(0,0,1);

		glEnd();

		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	}

	void Enemy::tex(float s, float t) const {
		float frame_s, frame_t;
		if(frame>=48) {
			frame_s = 11-((frame+1)%12);
			frame_t = 3-((frame+1)/12);
		} else {
			frame_s = frame%12;
			frame_t = frame/12;
		}
		glTexCoord2f((frame_s+s)/16.,(frame_t+t)/4.);
	}
}
