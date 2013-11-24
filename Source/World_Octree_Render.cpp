//-----------------------------
// James Payor - Evolution RTS
// Created 03/05/13
//-----------------------------
//
//--------------------------
// World_Octree_Render.cpp |
//-------------------------------------------
// Implements the render() method of the
// World::Octree class that draws the faces
// of the cube represented by the current
// node in the tree.
//-------------------------------------------

// Required header files:
#include <../Headers/Macro.hpp>
#include <../Headers/World_Octree.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Graphics_GL.hpp>
#include "glb.h"
#include <cmath>
#include <vector>
using namespace Math;
using namespace Graphics;

// Iteration constants and macro:
static const int d1[] = {0, 1, 1, 0}, d2[] = {0, 0, 1, 1};
#define iter(x,y) for(int i=0,x=0,y=0; i<4; ++i,x=d1[i],y=d2[i])

// Dynamic arrays of normals, vertices, and texture coordinates:
vec3f *norms, *points;
float *tex_coords;
// The current sizes and allocated sizes of the arrays:
int norms_size, points_size, norms_msize, points_msize, tex_coords_size, tex_coords_msize;

// Pushes a normal onto the arrays:
inline void push_norms(const vec3f& vec) {
	// If out of space, allocate more and copy the old across:
	if(norms_size == norms_msize) {
		vec3f *old = norms;
		(norms_msize *= 2) += 64;
		norms = new vec3f[norms_msize];
		fo(i,norms_size) norms[i] = old[i];
		delete[] old;
	}
	norms[norms_size++] = vec;
}

// Pushes a vertex onto the arrays:
inline void push_points(const vec3f& vec) {
	// If out of space, allocate more and copy the old across:
	if(points_size == points_msize) {
		vec3f *old = points;
		(points_msize *= 2) += 64;
		points = new vec3f[points_msize];
		fo(i,points_size) points[i] = old[i];
		delete[] old;
	}
	points[points_size++] = vec;
}

// Pushes texture coordinates onto the arrays:
inline void push_tex(float s, float t) {
	// If out of space allocate more and copy the old across:
	if(tex_coords_size == tex_coords_msize) {
		float *old = tex_coords;
		(tex_coords_msize *= 2) += 64;
		tex_coords = new float[tex_coords_msize];
		fo(i,tex_coords_size) tex_coords[i] = old[i];
		delete[] old;
	}
	tex_coords[tex_coords_size++] = s;
	tex_coords[tex_coords_size++] = t;
}

// Helper definitions:
inline void vertex(float x, float y, float z) {
	push_points(vec3f(x,y,z));
}
inline void normal(const vec3f& vec) {
	push_norms(vec);
}


namespace World {

	float Octree::coef;

	// Renders the octree with given cube size, returning the number of cubes rendered:
	void Octree::render(float size, const vec3f& center, const Frustum& frustum) const {
		if(!this || !frustum.inside(center, size)) return;
		if(!isLeaf() && Octree::coef*frustum.dist(center) < size) {
			size *= 0.5;
			fo(x,2) fo(y,2) fo(z,2) getChild(x,y,z)->render(size, vec3f(center.x+(x-0.5)*size,center.y+(y-0.5)*size,center.z+(z-0.5)*size), frustum);
		} else if(facemask) render(center, size);
	}


	// Renders cube faces with a size of 1.0:
	void Octree::render(const vec3f& center, float size) const {

		float _x(center.x-size*0.5), _y(center.y-size*0.5), _z(center.z-size*0.5);

		// Left
		if(facemask & GL::Face::Left) {
			iter(z,y) {
				push_tex(z,y);
				normal(getNorm(0,y,z));
				vertex(_x,_y+y*size,_z+z*size);
			}
		}


		// Right
		if(facemask & GL::Face::Right) {
			iter(y,z) {
				push_tex(y,z);
				normal(getNorm(1,y,z));
				vertex(_x+size,_y+y*size,_z+z*size);
			}
		}

		// Front
		if(facemask & GL::Face::Front) {
			iter(y,x) {
				push_tex(y,x);
				normal(getNorm(x,y,0));
				vertex(_x+x*size,_y+y*size,_z);
			}
		}

		// Back
		if(facemask & GL::Face::Back) {
			iter(x,y) {
				push_tex(x,y);
				normal(getNorm(x,y,1));
				vertex(_x+x*size,_y+y*size,_z+size);
			}
		}

		// Top
		if(facemask & GL::Face::Top) {
			iter(z,x) {
				push_tex(z,x);
				normal(getNorm(x,1,z));
				vertex(_x+x*size,_y+size,_z+z*size);
			}
		}

		// Bottom
		if(facemask & GL::Face::Bottom) {
			iter(x,z) {
				push_tex(x,z);
				normal(getNorm(x,0,z));
				vertex(_x+x*size,_y,_z+z*size);
			}
		}

	}
}
