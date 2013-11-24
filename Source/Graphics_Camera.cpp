//-----------------------------
// James Payor - Evolution RTS
// Created 27/03/13
//-----------------------------
//
//-------------
// Camera.cpp |
//-------------------------------------------
// Implements the Graphics::Camera class,
// responsible for applying the
// tranformations required for movement
// around a 3D scene.
//-------------------------------------------


// Required headers:
#include <../Headers/Graphics_Camera.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Frustum.hpp>
using namespace Math;

#include <../Headers/Graphics_GL.hpp>
#include <cmath>
#include "glb.h"
#include "glb3D.h"


// Useful macro definitions:
#define REVOLUTION 360.0
#define PI M_PI
#define degrees(x) (x / (2*PI) * REVOLUTION)
#define radians(x) (x / REVOLUTION * (2*PI))


typedef double scalar;

namespace Graphics {

	// Initialise a camera from different parameters:
	Camera::Camera(const vec3& loc, double pitch, double yaw,  double near, double far, double ratio, double FOV) :
		location(loc), pitch(pitch), yaw(yaw), near(near), far(far), ratio(ratio), FOV(FOV) {}

	Camera::Camera(const vec3& loc, const vec3& view, double near, double far, double ratio, double FOV) :
		location(loc), near(near), far(far), ratio(ratio), FOV(FOV) {
		this->setView(view);
	}


	// Translate the camera in space:
	void Camera::translate(const vec3& amt) {
		location += amt;
	}

	void Camera::translate(scalar x, scalar y, scalar z) {
		location += vec3(x,y,z);
	}


	// Rotate the camera:
	void Camera::rotate(double pitch, double yaw) {
		this->pitch += pitch;
		this->yaw += yaw;
		// Keep angles in the range [0,REVOLUTION)
		this->pitch = fmod(this->pitch, REVOLUTION);
		this->yaw = fmod(this->yaw, REVOLUTION);
		if(this->pitch < 0) this->pitch += REVOLUTION;
		if(this->yaw < 0) this->yaw += REVOLUTION;
	}

	// Set location:
	void Camera::setLoc(const vec3& loc) {
		location = loc;
	}

	// Set viewing direction:
	void Camera::setView(const vec3& view) {
		pitch = degrees(asin(view.y / view.abs()));
		yaw = degrees(atan2(view.z, view.x));
	}

	// Set rotation:
	void Camera::setRotation(double pitch, double yaw) {
		this->pitch = pitch;
		this->yaw = yaw;
	}

	// Set pitch:
	void Camera::setPitch(double pitch) {
		this->pitch = pitch;
	}

	// Set yaw:
	void Camera::setYaw(double yaw) {
		this->yaw = yaw;
	}

	// Update camera's field-of-view based off current speed:
	void Camera::updateFOV(double speed) {
		// The ranges speed and FOV span:
		const double lowFOV = 108, highFOV = 135, lowSpeed = 4, highSpeed = 30;

		// Clamped linear interpolation:
		if(speed < lowSpeed) FOV = (lowFOV+FOV*9)*0.1;
		else if(speed > highSpeed) FOV = (highFOV+FOV*9)*0.1;
		else FOV = (lowFOV + (highFOV-lowFOV) * (speed - lowSpeed) / (highSpeed-lowSpeed) + FOV*9)*0.1;
	}


	// Get pitch:
	double Camera::getPitch() const {
		return pitch;
	}

	// Get yaw:
	double Camera::getYaw() const {
		return yaw;
	}

	// Get the 'ahead' unit vector:
	vec3 Camera::ahead() const {
		return up().cross(right());
	}

	// Get the 'up' unit vector:
	vec3 Camera::up() const {
		return vec3(sin(radians(pitch))*sin(radians(yaw)), cos(radians(pitch)), sin(radians(pitch))*cos(radians(yaw))).norm();
	}

	// Get the 'right' unit vector:
	vec3 Camera::right() const {
		return vec3(cos(radians(yaw)), 0, -sin(radians(yaw))).norm();
	}

	// Get location:
	vec3 Camera::getLoc() const {
		return location;
	}


	// Apply the camera's transformations to the world:
	void Camera::applyTransform() {

		// Move world to match camera:
		GL::rotatePitch(-pitch);
		GL::rotateYaw(-yaw);
		GL::translate(-location);

		// Setup lighting:
		vec3 a = ahead(), l = location-40.*a-50.*vec3::Y(); a-=vec3(0,a.y*0.2,0);
		X_SPOT_LT(1, RGB(240,240,200), l.x, l.y, l.z, a.x, a.y*0.5, a.z, 57);
		X_SPOT_LT(2, RGB(40,50,60), l.x, l.y, l.z, a.x, a.y*0.5, a.z, 70);
		X_FOG(RGB(0,0,0), true, 0.00045, 0);
	}

	// Set the world transformation to the camera's setup:
	void Camera::setTransform() {

		// Initialise 3D:
		X_MAKE3D(near, far+3, FOV);
		GL::identity();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_NORMALIZE);

		// Apply transformation:
		this->applyTransform();
	}

	// Get the viewing frustum of this camera:
	Frustum Camera::getFrustum() const {
		return Frustum(location, up(), right(), near, far, ratio, FOV);
	}

}
