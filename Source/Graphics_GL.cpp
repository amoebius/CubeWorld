//-----------------------------
// James Payor - Evolution RTS
// Created 28/03/13
//-----------------------------
//
//------------------
// Graphics_GL.cpp |
//-------------------------------------------
// Implements methods that wrap the OpenGL
// API for easier use with vectors.
//-------------------------------------------


// Required headers:
#include <GL/gl.h>
#include <../Headers/Graphics_GL.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Macro.hpp>
using namespace Math;


namespace Graphics {
namespace GL {

	// Draws a cube from (0,0,0) to (1,1,1), drawing the faces specified by facemask with face normals.
	// The six least significant bits of facemask represent [in order of increasing significance]:
	//   Left  Right  Front  Back  Top  Bottom
	unsigned int cubeNormalDisplayLists = 0;
	bool cubeNormalDisplayListsInstantiated = false;
	void drawCubeWithNormals(char facemask) {
		glCallList(cubeNormalDisplayLists+facemask);
	}

	// Initialise display lists:
	void initDisplayLists() {
		initNormalCubeDisplayLists();
	}

	// Create each possible cube display list:
	void initNormalCubeDisplayLists() {

		if(!cubeNormalDisplayListsInstantiated) {
			cubeNormalDisplayListsInstantiated = true;
			cubeNormalDisplayLists = glGenLists(1<<6);

			fo(facemask,1<<6) {
				glNewList(cubeNormalDisplayLists+facemask, GL_COMPILE);

				glEnable(GL_NORMALIZE);
				glBegin(GL_QUADS);

				// Left
				if(facemask & Face::Left) {
					glNormal3d(-1,0,0);
					glVertex3d(0,0,1);
					glVertex3d(0,1,1);
					glVertex3d(0,1,0);
					glVertex3d(0,0,0);
				}


				// Right
				if(facemask & Face::Right) {
					glNormal3d(1,0,0);
					glVertex3d(1,0,0);
					glVertex3d(1,1,0);
					glVertex3d(1,1,1);
					glVertex3d(1,0,1);
				}

				// Front
				if(facemask & Face::Front) {
					glNormal3d(0,0,-1);
					glVertex3d(0,0,0);
					glVertex3d(0,1,0);
					glVertex3d(1,1,0);
					glVertex3d(1,0,0);
				}

				// Back
				if(facemask & Face::Back) {
					glNormal3d(0,0,1);
					glVertex3d(1,0,1);
					glVertex3d(1,1,1);
					glVertex3d(0,1,1);
					glVertex3d(0,0,1);
				}

				// Top
				if(facemask & Face::Top) {
					glNormal3d(0,1,0);
					glVertex3d(0,1,1);
					glVertex3d(1,1,1);
					glVertex3d(1,1,0);
					glVertex3d(0,1,0);
				}

				// Bottom
				if(facemask & Face::Bottom) {
					glNormal3d(0,-1,0);
					glVertex3d(0,0,0);
					glVertex3d(1,0,0);
					glVertex3d(1,0,1);
					glVertex3d(0,0,1);
				}

				glEnd();

				glEndList();
			}
		}
	}

}
}
