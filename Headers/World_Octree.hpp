//-----------------------------
// James Payor - Evolution RTS
// Created 16/03/13
//-----------------------------
//
//-------------------
// World_Octree.hpp |
//-------------------------------------------
// Declares the World::Octree class, the
// data structure used to represent terrain.
//-------------------------------------------

#ifndef WORLD_OCTREE_H
#define WORLD_OCTREE_H

// Required headers:
#include <cstddef>
#include <GL/gl.h>
#include <../Headers/Math_Functional.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_Frustum.hpp>
#include <../Headers/Atomic.hpp>
using namespace Math;

// For clarity only, define a 'byte' type:
typedef char byte;

namespace World {

	// Represents a node in the octree that
	class Octree {

	public:

		static float coef;

		// Creates and initialises a new node:
		Octree(bool solid = true, const vec3f& normal = vec3f::zero());
		// Destroys a node and its children:
		~Octree();

		// Returns whether the block is solid:
		inline bool isSolid() const {
			return this && data;
		}
		// Returns whether the node is a leaf:
		inline bool isLeaf() const {
			return !this || children == NULL;
		}
		// Sets the block to be solid:
		void setSolid(bool solid = true);

		// Intstantiates 8 children to subdivide the block:
		void spawnChildren(bool instantiate = true);

		// Frees the node's children:
		void freeChildren();

		static Octree* OctreeNULL;
		// Gets the child at the specified subdivision (x,y,z = {0,1}):
		inline Octree*& getChild(int x, int y, int z) const {
			return children ? children[x+y*2+z*4] : OctreeNULL;
		}
		// Gets the child at the specified index, i = [0,8):
		inline Octree*& getChild(int i) const {
			return children ? children[i] : OctreeNULL;
		}
		inline void freeChild(int i) {
			delete children[i];
			children[i] = NULL;
		}
		inline void freeChild(int x, int y, int z) {
			delete children[x+y*2+z*4];
			children[x+y*2+z*4] = NULL;
		}


		// Gets the normal at the specified index:
		inline vec3f& getNorm(int i) const {
			return (vec3f&)norm[i];
		}
		// Gets the normal for the specified corner:
		inline vec3f& getNorm(int x, int y, int z) const {
			return (vec3f&)norm[x+y*2+z*4];
		}


		// Renders the octree with given cube size, returning the number of cubes rendered:
		void render(float size, const vec3f& center, const Frustum& frustum) const;
		// Renders cube faces with a size of 1.0:
		void render(const vec3f& center, float size) const;

		inline void render(float size, const Frustum& frustum) const {
			return render(size, vec3f::diag(size*0.5), frustum);
		}


		// Builds an octree from a given heightmap, a functional that maps an (x,z) location to a height:
		// hmap:        the heightmap that describes the height and surface normal at each point
		// subdivisons: the number of times to subdivide this octree
		// center:      a vector specifying the lower center of the cube
		// size:        the size of the cube
		static int threadCap, progressLevel;
		static atomic<int> threadsRunning, nodeCount;
		Octree(const Heightmap &hmap, int subdivisions, const vec3f& center, float size);

		// Sets up the normals from a given heightmap, location, and size:
		void setupNorms(const Heightmap &hmap, const vec3f& center, float size);

		// Optimises the rendered faces, culling interior surfaces:
		void cullFaces(byte face, Octree* neighbour);
		// Indicates whether the specified face is completely covered by solid nodes:
		bool faceCovered(byte face) const;


		// Helper function to count the number of nodes contained in the octree:
		int countNodes() const;


	private:
		// Data and cube face bitmask:
		byte data;
		byte facemask;
		// Normals:
		vec3f norm[8];
		// Children:
		Octree **children;

	};
}


#endif
