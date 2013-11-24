//-----------------------------
// James Payor - Evolution RTS
// Created 03/04/13
//-----------------------------
//
//-----------------------
// Math_PerlinNoise.hpp |
//-------------------------------------------
// Implements the PerlinNoise functional that
// maps a 2D position to an intensity value,
// for use in terrain generation.
//-------------------------------------------


// Required headers:
#include <../Headers/Math_PerlinNoise.hpp>
#include <../Headers/Macro.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

// 2D iteration constants and macro:
static const int D1[] = {-1,1,-1,1}, D2[] = {1,1,-1,-1};
#define iter(i,x,y) for(int i=0,x=D1[0],y=D2[0]; i<4; ++i,x=D1[i],y=D2[i])


namespace Math {

	// Initialise the PerlinNoise instance:
	PerlinNoise::PerlinNoise(int subdivisions, int seed) : subdivisions(subdivisions) {
		// Seed the random number generator:
		srand(seed ? seed : time(NULL));
		// Get a "salt" value:
		salt = rand();
		// Generate random gradient vectors (stored in an Nx2 dimensioned array):
		fo(i,PERLIN_NOISE_BANK) fo(j,2) norms[i][j] = (((float)rand() / (float)RAND_MAX) - 0.5) * 0.8;//0.9;
	}

	// A local function to perform Perlin's sigmoid-curve interpolation:
	inline float interpolate(float t) {
		return t*t*t*(t*(t*6 - 15) + 10);
	}
	// The derivative of the interpolation curve:
	inline float interpolated(float t) {
		return t*t*(t*(t*30-60) + 30);
	}
	// Simple linear interpolation:
	inline float linear(float t, float a, float b) {
		return a + (b-a)*t;
	}

	// Calculates the intensity value at a given (x,z) position:
	float PerlinNoise::noise(float x, float z) const {

		// Initialise size to be in the middle:
		float h(size()*0.5);
		// Integers of x and z coordinates:
		int ix(x),iz(z);

		// For each level of subdivision:
		fo(division,subdivisions+1) {

			// Get the spacing of the grid at this level:
			int space(1<<(subdivisions-division));
			// Find the grid coordinates, and set up the "salt" value:
			int gx(ix / space), gz(iz / space), csalt(salt*(division+1));

			// Find the relative offsets from the (gx,gz) and (gx+1,gz+1) points in the grid:
			float nx(x - gx*space), nz(z - gz*space), nx2(nx-space), nz2(nz-space);
			// Get the interpolation values:
			float u(interpolate(nx/space)), v(interpolate(nz/space));

			// Get the different gradient vectors involved:
			const float  *v00(norms[hash(gx,gz  ,csalt,division)]), *v10(norms[hash(gx+1,gz  ,csalt,division)]),
				         *v01(norms[hash(gx,gz+1,csalt,division)]), *v11(norms[hash(gx+1,gz+1,csalt,division)]);

			// Add the interpolated values to the height at this point:
			h += linear(v, linear(u, v00[0]*nx + v00[1]*nz,  v10[0]*nx2 + v10[1]*nz),
						   linear(u, v01[0]*nx + v01[1]*nz2, v11[0]*nx2 + v11[1]*nz2));
		}
		return h;
	}

	vec3f PerlinNormal::normal(float x, float z) const {
		// Partial derivatives:
		float dhdx(0), dhdz(0);
		// Integer coordinates:
		int ix(x),iz(z);

		// For each subdivided grid:
		fo(division,noise.subdivisions+1) {
			// Mostly as before, just with more magic long lines that I figured out through math and later
			// compressing the code to optimise it.  Just accept that we end up with the partial derivatives
			// dh/dx and dh/dz and all will be happy, I promise!
			int space(1<<(noise.subdivisions-division));
			int gx(ix / space), gz(iz / space), csalt(noise.salt*(division+1));

			float nx(x - gx*space), nz(z - gz*space), nx2(nx-space), nz2(nz-space);
			float u(interpolate(nx/space)), v(interpolate(nz/space)), dudx(interpolated(nx/space)/space);

			const float  *v00(noise.norms[PerlinNoise::hash(gx,gz  ,csalt,division)]), *v10(noise.norms[PerlinNoise::hash(gx+1,gz  ,csalt,division)]),
				         *v01(noise.norms[PerlinNoise::hash(gx,gz+1,csalt,division)]), *v11(noise.norms[PerlinNoise::hash(gx+1,gz+1,csalt,division)]);

			dhdx += linear(v,linear(u,v00[0],v10[0]) + dudx*(v10[0]*nx2 + v10[1]*nz - v00[0]*nx - v00[1]*nz),linear(u,v01[0],v11[0]) + dudx*(v11[0]*nx2 + v11[1]*nz2 - v01[0]*nx - v01[1]*nz2));
			dhdz += linear(v,linear(u,v00[1],v10[1]),linear(u,v01[1],v11[1])) + linear(u, v01[0]*nx + v01[1]*nz2 - v00[0]*nx - v00[1]*nz, v11[0]*nx2 + v11[1]*nz2 - v10[0]*nx2 - v10[1]*nz)*(interpolated(nz/space)/space);
		}

		// Taking the cross product of the derivatives involving these yields the following surface normal vector:
		return vec3f(-dhdx,1,-dhdz).norm();
	}

}
