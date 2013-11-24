//-----------------------------
// James Payor - Evolution RTS
// Created 15/07/13
//-----------------------------
//
//-------------
// Random.hpp |
//-------------------------------------------
// Defines several standard, useful random
// number generation functions.
//-------------------------------------------

#ifndef RANDOM_H
#define RANDOM_H

// Required headers:
#include <cstdlib>
#include <ctime>

namespace Random {

	// Seeds the generator:
	inline void Seed() {
		srand(time(NULL));
	}

	// Return doubles in the given ranges:
	inline double Double(double high) {
		return rand()*high/RAND_MAX;
	}
	inline double Double(double low, double high) {
		return low+Double(high-low);
	}

	// Return integers in the given ranges:
	inline int Integer(int high) {
		return (int)Double(high);
	}
	inline int Integer(int low, int high) {
		return low+Integer(high-low);
	}

	// Return floats in the given ranges:
	inline float Float(float high) {
		return rand()*high/RAND_MAX;
	}
	inline float Float(float low, float high) {
		return low+Float(high-low);
	}

}

#endif
