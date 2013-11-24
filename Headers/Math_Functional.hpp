//-----------------------------
// James Payor - Evolution RTS
// Created 03/04/13
//-----------------------------
//
//----------------------
// Math_Functional.hpp |
//-------------------------------------------
// Declares abstract functional classes for
// use in passing callable objects around.
//-------------------------------------------

#ifndef MATH_FUNCTIONAL_H
#define MATH_FUNCTIONAL_H

// Required headers:
#include <../Headers/Math_Vector.hpp>
#include <cmath>

namespace Math {

	// Templated base class takes in parameters for the type it maps from and the type it maps to:
	template <class Domain, class Range>
	class Functional {
	public:
		// Declare that the call operator is overloaded with a pure virtual function (that must be
		// implemented by subclasses of Functional<Domain, Range>):
		virtual Range operator() (Domain) const = 0;
	};

	typedef Functional<const vec2&, double> ScalarField2;
	typedef Functional<const vec2f&, float> ScalarField2f;
	typedef Functional<const vec2&, vec3> VectorField2;
	typedef Functional<const vec2f&, vec3f> VectorField2f;

	// Class that groups a height+normal map for use in terrain generation:
	class Heightmap {
	public:
		Heightmap() {}
		virtual float getHeight(const vec2f& location) const = 0;
		virtual vec3f getNormal(const vec2f& location) const = 0;
	};

	// Class that implements a heightmap through an explicit scalar field and vector field:
	class ScalarVectorHeightmap : public Heightmap {
	private:
		const ScalarField2f &height;
		const VectorField2f &normal;

	public:
		// Initialise the fields from the passed references:
		template <class ScalarField, class VectorField>
		ScalarVectorHeightmap(const ScalarField& height, const VectorField& normal) :
			height(dynamic_cast<const ScalarField2f&>(height)), normal(dynamic_cast<const VectorField2f&>(normal)) {}

		// Query fields for heights and normals:
		inline float getHeight(const vec2f& location) const {
			return height(location);
		}
		inline vec3f getNormal(const vec2f& location) const {
			return normal(location);
		}
	};


	// Class that scales another heightmap by the specified factor:
	class ScaledHeightmap : public Heightmap {

	private:
		const Heightmap& hmap;
		float scale;

	public:
		// Initialise from another heightmap and a scaling factor:
		ScaledHeightmap(const Heightmap& hmap, float scale) : hmap(hmap), scale(scale) {}
		ScaledHeightmap(const Heightmap* _hmap, float scale) : hmap(*_hmap), scale(scale) {}

		// Hide the scaling factor from the other heightmap and query it for heights and normals:
		inline float getHeight(const vec2f& location) const {
			return scale * hmap.getHeight(location / scale);
		}
		inline vec3f getNormal(const vec2f& location) const {
			return hmap.getNormal(location / scale);
		}

	};


	// Class that tiles another heightmap indefinitely in the plane:
	class TiledHeightmap : public Heightmap {

	private:
		const Heightmap& hmap;
		float size;

	public:
		// Initialise from another heightmap and a tiling size:
		TiledHeightmap(const Heightmap& hmap, float size): hmap(hmap), size(size) {}
		TiledHeightmap(const Heightmap* _hmap, float size): hmap(*_hmap), size(size) {}

		// Convert the coordinates to those within the tiling range, then query the heightmap for heights and normals:
		inline float getHeight(const vec2f& location) const {
			vec2f loc(fmod(location.x,size),fmod(location.z,size));
			if(loc.x<0) loc.x+=size;
			if(loc.z<0) loc.z+=size;
			return hmap.getHeight(loc);
		}
		inline vec3f getNormal(const vec2f& location) const {
			vec2f loc(fmod(location.x,size),fmod(location.z,size));
			if(loc.x<0) loc.x+=size;
			if(loc.z<0) loc.z+=size;
			return hmap.getNormal(loc);
		}

	};

}

#endif
