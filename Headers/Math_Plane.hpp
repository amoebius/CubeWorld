//-----------------------------
// James Payor - Evolution RTS
// Created 03/05/13
//-----------------------------
//
//-------------------
// Math_Plane.hpp |
//-------------------------------------------
// Declares the Math::plane class, used to
// represent a plane in 3D space.  Supports
// 'side checking' of points for partioning
// space.
//-------------------------------------------


#ifndef MATH_PLANE_H
#define MATH_PLANE_H

// Required headers:
#include <../Headers/Math_Vector.hpp>

namespace Math {

	// Implements a simple plane:
	class plane {
	public:
		// Constructors:
		plane() : point(), normal() {}
		plane(const vec3f& point, const vec3f& normal) : point(point), normal(normal.norm()) {}

		// Determines if the specified location is above the plane, within a specified margin:
		inline bool plane::above(const vec3f& loc, float margin) const {
			return (loc-point) * normal > -margin;
		}

		// Returns the distance from the plane to a point:
		inline float plane::dist(const vec3f& loc) const {
			return (loc-point) * normal;
		}

		// Plane state data - a point on the plane and normal to the plane:
		vec3f point, normal;
	};

}


#endif
