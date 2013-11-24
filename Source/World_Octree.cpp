//-----------------------------
// James Payor - Evolution RTS
// Created 16/03/13
//-----------------------------
//
//-------------------
// World_Octree.cpp |
//-------------------------------------------
// Implements the World::Octree class, the
// data structure used to represent terrain.
//-------------------------------------------

// Required header files:
#include <cstddef>
#include <GL/gl.h>
#include <../Headers/Macro.hpp>
#include <../Headers/World_Octree.hpp>
#include <../Headers/Graphics_GL.hpp>
#include <../Headers/Math_Functional.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Atomic.hpp>

using namespace Math;
using namespace Graphics::GL;

namespace World {

	// Useful static variables for communicating with the octree during generation:
	int Octree::threadCap, Octree::progressLevel;
	atomic<int> Octree::threadsRunning, Octree::nodeCount;
	Octree* Octree::OctreeNULL = NULL;

	// Creates and initialises a new node:
	Octree::Octree(bool solid, const vec3f& normal) {
		children = NULL;
		setSolid(solid);
		// If a normal is supplied apply this to the corners, otherwise use normals pointing outwards from the center:
		if(normal.abs2()) fo(i,8) getNorm(i) = normal;
		else fo(x,2) fo(y,2) fo(z,2) getNorm(x,y,z) = vec3(x-.5,y-.5,z-.5).norm();
	}

	// Functor class to instantiate an octree:
	class Instantiate : virtual Thread {
	private:
		const Heightmap &hmap;
		int subdivisions;
		vec3f center;
		float size;

	public:
		Instantiate(const Heightmap& hmap, int subdivisions, const vec3f& center, float size) :
			hmap(hmap), subdivisions(subdivisions), center(center), size(size) {}

		// Simply call the octree constructor:
		inline Octree* operator()() {
			return new Octree(hmap, subdivisions, center, size);
		}
	};


	// Builds an octree from a given heightmap, a functional that maps an (x,z) location to a height:
	// hmap:        the heightmap that describes the height and surface normal at each point
	// subdivisons: the number of times to subdivide this octree
	// center:      a vector specifying the lower center of the cube
	// size:        the size of the cube
	//
	// NB:  See algorithm for a good explanation of this, don't judge my internal documentation here!!
	Octree::Octree(const Heightmap& hmap, int subdivisions, const vec3f& center, float size) {
		children = NULL;
		setSolid(false);

		size *= 0.5;
		if(subdivisions) {
			spawnChildren(false);
			int childCount = 0;

			if(hmap.getHeight(center) > center.y) {

				// Try instantiating top nodes first:
				if(Octree::threadsRunning.resget() < Octree::threadCap) {
					Octree::threadsRunning += 4;
					Threading::Threaded<Instantiate> *threads[4];
					fo(x,2) fo(z,2) threads[x+2*z] = new Threading::Threaded<Instantiate>(Instantiate(hmap, subdivisions-1, vec3f(center.x+(x*2-1)*size, center.y+size, center.z+(z*2-1)*size), size));
					fo(x,2) fo(z,2) {
						getChild(x,1,z) = threads[x+2*z]->join(), delete threads[x+2*z];
						if(getChild(x,1,z)->isSolid()) childCount++;
					}
					Octree::threadsRunning -= 4;
				} else {
					Octree::threadsRunning.release();
					fo(x,2) fo(z,2) {
						getChild(x,1,z) = new Octree(hmap, subdivisions-1, vec3f(center.x+(x*2-1)*size, center.y+size, center.z+(z*2-1)*size), size);
						if(getChild(x,1,z)->isSolid()) childCount++;
					}
				}

				if(childCount==4) {
					childCount = 8;
					if(subdivisions>progressLevel) nodeCount+=1<<(subdivisions-progressLevel-1)*3+2;
				} else {
					childCount = 0;
					fo(x,2) fo(z,2) {
						if(getChild(x,1,z)->isSolid()) {
							getChild(x,0,z) = new Octree(true);
							if(subdivisions>progressLevel) nodeCount+=1<<(subdivisions-progressLevel-1)*3;
						} else {
							getChild(x,0,z) = new Octree(hmap, subdivisions-1, vec3f(center.x+(x*2-1)*size, center.y-size, center.z+(z*2-1)*size), size);
							if(!getChild(x,0,z)->isSolid() && getChild(x,0,z)->isLeaf()) freeChild(x,0,z), childCount--;
							if(getChild(x,1,z)->isLeaf()) freeChild(x,1,z), childCount--;
						}
					}
				}

			} else {
				// Try instantiating bottom nodes first:
				if(Octree::threadsRunning.resget() < Octree::threadCap) {
					Octree::threadsRunning += 4;
					Threading::Threaded<Instantiate> *threads[4];
					fo(x,2) fo(z,2) threads[x+2*z] = new Threading::Threaded<Instantiate>(Instantiate(hmap, subdivisions-1, vec3f(center.x+(x*2-1)*size, center.y-size, center.z+(z*2-1)*size), size));
					fo(x,2) fo(z,2) {
						getChild(x,0,z) = threads[x+2*z]->join(), delete threads[x+2*z];
						if(!getChild(x,0,z)->isSolid() && getChild(x,0,z)->isLeaf()) childCount++, freeChild(x,0,z);
					}
					Octree::threadsRunning -= 4;
				} else {
					Octree::threadsRunning.release();
					fo(x,2) fo(z,2) {
						getChild(x,0,z) = new Octree(hmap, subdivisions-1, vec3f(center.x+(x*2-1)*size, center.y-size, center.z+(z*2-1)*size), size);
						if(!getChild(x,0,z)->isSolid() && getChild(x,0,z)->isLeaf()) childCount++, freeChild(x,0,z);
					}
				}

				if(childCount==4) {
					childCount = -8;
					if(subdivisions>progressLevel) nodeCount+=1<<(subdivisions-progressLevel-1)*3+2;
				} else {
					childCount = 0;
					fo(x,2) fo(z,2) {
						if(!getChild(x,0,z)->isSolid() && getChild(x,0,z)->isLeaf()) {
							if(subdivisions>progressLevel) nodeCount+=1<<(subdivisions-progressLevel-1)*3;
						} else {
							if(getChild(x,0,z)->isSolid()) childCount++;
							getChild(x,1,z) = new Octree(hmap, subdivisions-1, vec3f(center.x+(x*2-1)*size, center.y+size, center.z+(z*2-1)*size), size);
							if(getChild(x,1,z)->isSolid()) childCount++;
							else if(getChild(x,1,z)->isLeaf()) freeChild(x,1,z);
						}
					}
				}

			}

			if(childCount==8) {
				setSolid(true);
				freeChildren();
			} else if(childCount==-8) {
				setSolid(false);
				freeChildren();
			} else {
				// Optimise the faces that are rendered:
				fo(x,2) fo(z,2) getChild(x,0,z)->cullFaces(Face::Top, getChild(x,1,z)), getChild(x,1,z)->cullFaces(Face::Bottom, getChild(x,0,z));
				fo(x,2) fo(y,2) getChild(x,y,0)->cullFaces(Face::Back, getChild(x,y,1)), getChild(x,y,1)->cullFaces(Face::Front, getChild(x,y,0));
				fo(y,2) fo(z,2) getChild(0,y,z)->cullFaces(Face::Right, getChild(1,y,z)), getChild(1,y,z)->cullFaces(Face::Left, getChild(0,y,z));

				// Setup normals:
				fo(x,2) fo(y,2) fo(z,2) {
					Octree* ch = getChild(x,y,z);
					if(ch->isSolid() || !ch->isLeaf()) ch->setupNorms(hmap,vec3f(center.x+(x*2-1)*size, center.y+(y*2-1)*size, center.z+(z*2-1)*size),size);
				}
			}

		} else {
			// Set to solid if the center lies below the height at this point:
			setSolid(hmap.getHeight(center) > center.y);
		}

		if(!isLeaf()) facemask = 63;
		if(subdivisions==progressLevel) nodeCount+=1;
	}


	void Octree::setupNorms(const Heightmap &hmap, const vec3f& center, float size) {
		fo(x,2) fo(y,2) fo(z,2) {
			vec3f corner(center.x+size*(x*2-1),center.y+size*(y*2-1),center.z+size*(z*2-1));
			getNorm(x,y,z) = hmap.getNormal(corner - center.project(corner-center));
		}
	}

	// Optimises the rendered faces, culling interior surfaces:
	void Octree::cullFaces(byte face, Octree* neighbour) {
		if(!this || !neighbour) return;
		if(neighbour->isSolid() || neighbour->faceCovered(Face::opposite(face))) facemask &= ~face;
		if(neighbour->isLeaf()) {
			if(!isLeaf()) {
				if(face == Face::Left) {
					fo(y,2) fo(z,2) if(getChild(0,y,z)) getChild(0,y,z)->cullFaces(face, neighbour);
				} else if(face == Face::Right) {
					fo(y,2) fo(z,2) if(getChild(1,y,z)) getChild(1,y,z)->cullFaces(face, neighbour);
				} else if(face == Face::Front) {
					fo(x,2) fo(y,2) if(getChild(x,y,0)) getChild(x,y,0)->cullFaces(face, neighbour);
				} else if(face == Face::Back) {
					fo(x,2) fo(y,2) if(getChild(x,y,1)) getChild(x,y,1)->cullFaces(face, neighbour);
				} else if(face == Face::Top) {
					fo(x,2) fo(z,2) if(getChild(x,1,z)) getChild(x,1,z)->cullFaces(face, neighbour);
				} else if(face == Face::Bottom) {
					fo(x,2) fo(z,2) if(getChild(x,0,z)) getChild(x,0,z)->cullFaces(face, neighbour);
				}
			}
		} else if(!isSolid()) {
			if(face == Face::Left) {
				fo(y,2) fo(z,2) getChild(0,y,z)->cullFaces(face, neighbour->getChild(1,y,z));
			} else if(face == Face::Right) {
				fo(y,2) fo(z,2) getChild(1,y,z)->cullFaces(face, neighbour->getChild(0,y,z));
			} else if(face == Face::Front) {
				fo(x,2) fo(y,2) getChild(x,y,0)->cullFaces(face, neighbour->getChild(x,y,1));
			} else if(face == Face::Back) {
				fo(x,2) fo(y,2) getChild(x,y,1)->cullFaces(face, neighbour->getChild(x,y,0));
			} else if(face == Face::Top) {
				fo(x,2) fo(z,2) getChild(x,1,z)->cullFaces(face, neighbour->getChild(x,0,z));
			} else if(face == Face::Bottom) {
				fo(x,2) fo(z,2) getChild(x,0,z)->cullFaces(face, neighbour->getChild(x,1,z));
			}
		}
	}

	// Indicates whether the specified face is completely covered by solid nodes:
	bool Octree::faceCovered(byte face) const {
		if(isLeaf()) return isSolid();
		if(face == Face::Left) {
			fo(y,2) fo(z,2) if(!getChild(0,y,z)->faceCovered(face)) return false;
		} else if(face == Face::Right) {
			fo(y,2) fo(z,2) if(!getChild(1,y,z)->faceCovered(face)) return false;
		} else if(face == Face::Front) {
			fo(x,2) fo(y,2) if(!getChild(x,y,0)->faceCovered(face)) return false;
		} else if(face == Face::Back) {
			fo(x,2) fo(y,2) if(!getChild(x,y,1)->faceCovered(face)) return false;
		} else if(face == Face::Top) {
			fo(x,2) fo(z,2) if(!getChild(x,1,z)->faceCovered(face)) return false;
		} else if(face == Face::Bottom) {
			fo(x,2) fo(z,2) if(!getChild(x,0,z)->faceCovered(face)) return false;
		}
		return true;
	}



	// Destroys a node and its children:
	Octree::~Octree() {
		freeChildren();
	}

	// Sets the block to be solid:
	void Octree::setSolid(bool solid) {
		data = solid;
		facemask = 63;
	}

	// Intstantiates 8 children to subdivide the block:
	void Octree::spawnChildren(bool instantiate) {

		bool exists = children;

		// Create an array of pointers to 8 children:
		if(!exists) {
			children = new Octree*[8];
			fo(i,8) getChild(i) = NULL;
		}

		if(instantiate) {
			// Create the children:
			fo(i,8) if(!getChild(i)) getChild(i) = new Octree(isSolid());
		}
	}

	// Frees the node's children:
	void Octree::freeChildren() {
		// If the node has children:
		if(children) {
			// Free them:
			fo(i,8) if(getChild(i)) delete getChild(i);
			// Free the array of pointers:
			delete[] children;
			children = NULL;
		}
	}

	// Helper function to count the number of nodes contained in the octree:
	int Octree::countNodes() const {
		if(!this) return 0;
		int total = 1;
		if(!isLeaf()) fo(i,8) total += getChild(i)->countNodes();
		return total;
	}

}
