//-----------------------------
// James Payor - Evolution RTS
// Created 18/03/13
//-----------------------------
//
//----------------
// World_Map.hpp |
//-------------------------------------------
// Declares the World::Map class which holds
// all the information pertaining to a
// specific map (including an Octree
// representation of terrain, and all data
// other than units).
//-------------------------------------------


// IGNORE!!!

#ifndef WORLD_MAP_H
#define WORLD_MAP_H


namespace World {

	class Map {

	public:
		Map();
		~Map();


	private:
		int width, height, depth;
		Octree terrain;



	};
}


#endif
