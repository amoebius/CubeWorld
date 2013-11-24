//-----------------------------
// James Payor - Evolution RTS
// Created 03/04/13
//-----------------------------
//
//-----------------------
// Math_PerlinNoise.hpp |
//-------------------------------------------
// Declares the PerlinNoise functional that
// maps a 2D position to an intensity value,
// for use in terrain generation.
//-------------------------------------------

#ifndef MATH_PERLINNOISE_H
#define MATH_PERLINNOISE_H

#include <../Headers/Math_Functional.hpp>
#include <../Headers/Math_Vector.hpp>
#include <climits>

// Must be (preferably) prime with current hashing setup:
#define PERLIN_NOISE_BANK 523

namespace Math {

	// Implements Perlin noise - here a mapping from 2D space to a scalar value:
	class PerlinNoise : public ScalarField2f {
		friend class PerlinNormal;

	private:
		// The number of fractal subdivisions:
		int subdivisions;
		// The bank of random gradients:
		float norms[PERLIN_NOISE_BANK][2];
		// A pinch of salt (for randomness):
		int salt;

		// Fast, yet psuedorandom hashing function:
		static inline int hash(int x, int z, const int seed, const int subdivisions){
			// Wrap around:
			x %= 1<<subdivisions; z %= 1<<subdivisions;
			// Hash the coordinates into some index into the gradient bank:
			return ((((36969*(x*seed & 65535) + (x >> 16)) << 16) + 18001*(z & 65535) + (z*seed >> 16))&INT_MAX) % PERLIN_NOISE_BANK;
		}

	public:
		// Default constructor parameters:
		PerlinNoise(int subdivisions = 5, int seed = 0);

		// Helper function:
		inline int size() const {
			return 1 << subdivisions;
		}

		// Gets the intensity at a point:
		float noise(float x, float y) const;
		// Wrapper to conform to the ScalarField2f specification as a functor:
		inline float operator () (const vec2f& loc) const {
			return this->noise(loc.x, loc.z);
		}
	};

	// Provides normals at each point on a Perlin noise heightmap:
	class PerlinNormal : public VectorField2f {
	private:
		// Reference to the noise:
		const PerlinNoise &noise;

	public:
		// Constructed from a PerlinNoise object:
		PerlinNormal(const PerlinNoise &noise) : noise(noise) {}
		PerlinNormal(const PerlinNoise *noise) : noise(*noise) {}

		// Gets the normal at a point:
		vec3f normal(float x, float y) const;
		// Wrapper to conform to the VectorField2f functor specification:
		inline vec3f operator () (const vec2f& loc) const {
			return this->normal(loc.x, loc.z);
		}
	};

}

#endif
