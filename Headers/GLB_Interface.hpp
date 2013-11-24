//-----------------------------
// James Payor - Evolution RTS
// Created 30/05/13
//-----------------------------
//
//-------------------
// GLB_Interface.hpp |
//-------------------------------------------
// Declares functions and procedures used for
// interaction with GLBasic's libraries,
// primarily to aid input and ouput.
//-------------------------------------------


// IGNORE!!  THIS WASN'T COMPLETED AND ABLE TO BE OF USE...

#ifndef GLB_INTERFACE_H
#define GLB_INTERFACE_H

#include "glb.h"
#include <../Headers/GLB_Keycodes.hpp>

#define NUM_VK_CODES 255

namespace GLB {

	class Key {

	private:
		static bool keyDown[NUM_VK_CODES];
		int keycode;

	public:
		static void update();
		static inline char get() {
			return INKEY_Str().c_str()[0];
		}
		static inline bool down(int keycode) {
			return keyDown[keycode];
		}
		inline bool down() const {
			return keyDown[keycode];
		}
		inline int code() const {
			return keycode;
		}
		inline const char* label() const {
			return vk_label[keycode];
		}

	};

	namespace Mouse {
		extern int x, y, z;
		extern bool lb, rb, mb;
		void update();
	};

	void stepFrame();
}


#endif
