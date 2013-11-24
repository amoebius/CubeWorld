//-----------------------------
// James Payor - Evolution RTS
// Created 29/11/12
//-----------------------------
//
//--------------
// Net_UDP.cpp |
//-------------------------------------------
// Defines routines for sending and receiving
// UDP messages, interacting with GLBasic.
//-------------------------------------------


#include <cstring>
#include "glb.h"
#include "../Headers/Net_UDP.hpp"


// Namespace Net::UDP
namespace Net {
namespace UDP {

	// Remember the state of initialisation:
	bool isInitialised = false;

	// Initialises networking, returning a value that indicates success or failure:
	bool init() {
		if(isInitialised) return true; // Don't initialise multiple times.
		return isInitialised = SOCK_INIT();
	};
	// Closes all sockets and ends networking:
	void end() {
		SOCK_SHUTDOWN();
		isInitialised = false;
	};

	// Opens a UDP socket on the given port, returning an integer label, or -1 to indicate failure:
	int open(int port) {
		if (!init()) return false; // Ensure networking is initialised.
		return SOCK_UDPOPEN(port);
	};
	// Closes a socket, returning a value that indicates success or failure:
	bool close(int socket) {
		return SOCK_CLOSE(socket);
	}

	// GLBasic strings used for sending data, and receiving a message:
	DGStr data, msg;

	// Sends a UDP message using the given socket to the given ip address and port:
	bool send(int socket, const void* msg, int length, int ip, int port) {
		// Allocate the memory:
		data.alloc(length, false);
		data.setlength(length);
		// Copy the data:
		memcpy((void *)data.c_str(), msg, length);
		// Send the data:
		SOCK_UDPSEND(socket, data, ip, port);
	}

	// Returns the number of bytes available to read (0 if there are no queued messages):
	int available(int socket) {
		int rv = SOCK_RECV(socket, msg, 2048);
		// If rv is <= 0, return 0 to indicate failure, otherwise return rv to indicate the bytes available:
		return (rv > 0) ? rv : 0;
	}
	// Returns a pointer to the data received:
	const void *received() {
		return (const void *)msg.c_str();
	}

}
}
