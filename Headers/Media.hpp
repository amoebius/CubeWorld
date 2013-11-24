//-----------------------------
// James Payor - Evolution RTS
// Created 16/07/13
//-----------------------------
//
//------------
// Media.hpp |
//-------------------------------------------
// Defines global constants for dealing with
// media items, and declares methods for
// loading game media.
//-------------------------------------------

#ifndef MEDIA_H
#define MEDIA_H

namespace Media {

	namespace Texture {
		const int TerrainChilled = 1, Enemy = 2;
	}
	namespace Image {
		const int RedMask = 3, Moire = 4;
	}

	void Load();


}

#endif
