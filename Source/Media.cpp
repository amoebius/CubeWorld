//-----------------------------
// James Payor - Evolution RTS
// Created 16/07/13
//-----------------------------
//
//------------
// Media.cpp |
//-------------------------------------------
// Implements methods for loading game media.
//-------------------------------------------


// Required headers:
#include <../Headers/Media.hpp>
#include "glb.h"

namespace Media {

	void Load() {

		LOADSPRITE("TerrainChilled.png", Texture::TerrainChilled);
		LOADSPRITE("EnemyAnim.png", Texture::Enemy);
		LOADSPRITE("Mask.png", Image::RedMask);
		LOADSPRITE("BG Moire.png", Image::Moire);

	}

}
