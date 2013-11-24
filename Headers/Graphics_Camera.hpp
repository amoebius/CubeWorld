//-----------------------------
// James Payor - Evolution RTS
// Created 27/03/13
//-----------------------------
//
//-------------
// Camera.hpp |
//-------------------------------------------
// Declares the Graphics::Camera class,
// responsible for applying the
// tranformations required for movement
// around a 3D scene.
//-------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

// Required headers:
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Frustum.hpp>
using namespace Math;


namespace Graphics {

	class Camera {

	public:
		// Constructors:
		Camera(const vec3& loc, double pitch, double yaw, double near, double far, double ratio, double FOV);
		Camera(const vec3& loc, const vec3& view, double near, double far, double ratio, double FOV);

		// Relative movement:
		void translate(const vec3& amt);
		void translate(double x, double y, double z);
		void rotate(double pitch, double yaw);

		// Absolute movement:
		void setLoc(const vec3& loc);
		void setView(const vec3& view);
		void setRotation(double pitch, double yaw);
		void setPitch(double pitch);
		void setYaw(double yaw);

		// Special FX - field of view tweening:
		void updateFOV(double speed);

		// Getters for camera information:
		double getPitch() const;
		double getYaw() const;
		vec3 getLoc() const;
		vec3 ahead() const;
		vec3 up() const;
		vec3 right() const;

		// Methods to apply camera transformations:
		void applyTransform();
		void setTransform();

		// Gets the viewing frustum for the camera:
		Frustum getFrustum() const;


	private:
		// Camera state variables:
		vec3 location;
		double pitch, yaw, near, far, ratio, FOV;
	};
}


#endif
