//-----------------------------
// James Payor - Evolution RTS
// Created 30/05/13
//-----------------------------
//
//-------------------
// GLB_Interface.hpp |
//-------------------------------------------
// Implements functions and procedures used
// for interaction with GLBasic's libraries,
// primarily to aid input and ouput.
//-------------------------------------------


// IGNORE - THIS WASN'T DEVELOPED ENOUGH TO BE USEFUL

#include <../Headers/GLB_Interface.hpp>
#include <../Headers/Macro.hpp>
#include "glb.h"

namespace GLB {

	bool Key::keyDown[NUM_VK_CODES];
	void Key::update() {
		fo(i,NUM_VK_CODES) Key::keyDown[i] = KEY(i);
	}

	namespace Mouse {
		int x, y, z;
		bool lb, rb, mb;

		void update() {
			DGNat _x,_y,b1,b2;
			MOUSESTATE(_x,_y,b1,b2);
			x = (int)_x;
			y = (int)_y;
			lb = b1;
			rb = b2;

			mb = (bool)MOUSEAXIS(5);
			z = (int)MOUSEAXIS(2);
		};
	}

	void stepFrame() {
		SHOWSCREEN();
		Key::update();
		Mouse::update();
	}
}
