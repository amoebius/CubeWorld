//-----------------------------
// James Payor - Evolution RTS
// Created 28/03/13
//-----------------------------
//
//------------------
// Graphics_GL.hpp |
//-------------------------------------------
// Declares methods that wrap the OpenGL API
// for easier use with vectors.
//-------------------------------------------


#ifndef GRAPHICS_GL_H
#define GRAPHICS_GL_H

// Required headers:
#include <GL/gl.h>
#include <../Headers/Math_Vector.hpp>
using namespace Math;

namespace Graphics {
namespace GL {

	// Translates the world by a 3D vector:
	inline void translate(const vec3& vec) {
		glTranslated(vec.x, vec.y, vec.z);
	}

	// Rotates the world by the specified angle around the specified vector (by the right-hand rule):
	inline void rotate(double angle, const vec3& vec) {
		glRotated(angle, vec.x, vec.y, vec.z);
	}

	// Rotates along the x-axis:
	inline void rotatePitch(double angle) {
		glRotated(angle, 1, 0, 0);
	}

	// Rotates along the y-axis:
	inline void rotateYaw(double angle) {
		glRotated(angle, 0, 1, 0);
	}

	// Rotates along the z-axis:
	inline void rotateRoll(double angle) {
		glRotated(angle, 0, 0, 1);
	}

	// Restores the identity matrix:
	inline void identity() {
		glLoadIdentity();
	}

	// Sets the vertex normal:
	inline void normal(const vec3& vec) {
		glNormal3d(vec.x, vec.y, vec.z);
	}
	inline void normal(const vec3f& vec) {
		glNormal3f(vec.x, vec.y, vec.z);
	}

	// Specifies a vertex:
	inline void vertex(const vec3& vec) {
		glVertex3d(vec.x, vec.y, vec.z);
	}
	inline void vertex(const vec3f& vec) {
		glVertex3f(vec.x, vec.y, vec.z);
	}

	// Sets a monochrome color:
	inline void color1d(double intensity) {
		glColor3d(intensity, intensity, intensity);
	}

	// Defines constants pertaining to cube face masks:
	namespace Face {
		const char Left = 1, Right = 32, Front = 2, Back = 16, Top = 4, Bottom = 8, FaceMax = 32;
		inline char opposite(char face) {
			return FaceMax / face;
		}
	}

	// Draws a cube from (0,0,0) to (1,1,1), drawing the faces specified by facemask
	// The six least significant bits of facemask represent [in order of increasing significance]:
	//   Left  Right  Front  Back  Top  Bottom
	void drawCube(char facemask = 63);
	// Draws a cube with face normals:
	void drawCubeWithNormals(char facemask = 63);

	// Initialises required display lists:
	void initDisplayLists();

	// Initialises display lists for rendering cubes:
	void initCubeDisplayLists();
	void initNormalCubeDisplayLists();

}
}

#endif
