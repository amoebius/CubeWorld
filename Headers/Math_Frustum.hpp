//-----------------------------
// James Payor - Evolution RTS
// Created 03/05/13
//-----------------------------
//
//-------------------
// Math_Frustum.hpp |
//-------------------------------------------
// Declares the Math::Frustum class, used to
// represent a viewing frustum for purposes
// such as culling surfaces from rendering
// that are out of sight.
//-------------------------------------------


#ifndef MATH_FRUSTUM_H
#define MATH_FRUSTUM_H

// Required headers:
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Plane.hpp>
#include <../Headers/Macro.hpp>

namespace Math {

	class Frustum {

	private:
		// Constants:
		static const int NUM_PLANES = 5, NEAR = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4;
		// Frustum-specifying parameters - location, far distance, and clipping planes:
		vec3f location;
		float far;
		plane bounds[NUM_PLANES];

	public:
		// Constructors:
		Frustum();
		Frustum(const vec3f& location, const vec3f& up, const vec3f& right, float near, float far, float ratio, float FOV);

		// A simple inside check - if point is within radius and the shape defined by clipping planes:
		inline bool Frustum::inside(const vec3f& point, float radius) const {
			if(dist(point) - radius > far) return false;
			fo(i,NUM_PLANES) if(!bounds[i].above(point, radius)) return false;
			return true;
		}

		// Gets the distance to a point:
		inline float Frustum::dist(const vec3f& point) const {
			return (point-location).abs();
		}

		// Gets the squared distance to a point:
		inline float Frustum::dist2(const vec3f& point) const {
			return (point-location).abs2();
		}

	};

}


#endif
