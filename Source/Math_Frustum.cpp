//-----------------------------
// James Payor - Evolution RTS
// Created 03/05/13
//-----------------------------
//
//-------------------
// Math_Frustum.cpp |
//-------------------------------------------
// Implements the Math::Frustum class, used
// to represent a viewing frustum for
// purposes such as culling surfaces from
// rendering that are out of sight.
//-------------------------------------------


// Required headers:
#include <cmath>
#include <../Headers/Macro.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Plane.hpp>
#include <../Headers/Math_Frustum.hpp>


namespace Math {

	// Default constructor does nothing:
	Frustum::Frustum() {}

	// Initialise a frustum from camera parameters:
	Frustum::Frustum(const vec3f& location, const vec3f& up, const vec3f& right, float near, float far, float ratio, float FOV) :
		location(location), far(far) {

		// Setup near:
		vec3f ahead = up.cross(right).norm();
		bounds[NEAR] = plane(location + near*ahead, ahead);

		// Get the ratio of y to z:
		float tanFOV = tan(FOV * M_PI / 360.0);

		// Setup top and bottom bounds:
		bounds[UP] = plane(location, -right.cross(up * tanFOV + ahead));
		bounds[DOWN] = plane(location, right.cross(-up * tanFOV + ahead));

		// Convert to left-right ratio, and setup left and right bounds:
		tanFOV = ratio * tanFOV;
		bounds[RIGHT] = plane(location, up.cross(right * tanFOV + ahead));
		bounds[LEFT] = plane(location, -up.cross(-right * tanFOV + ahead));
	}

}
