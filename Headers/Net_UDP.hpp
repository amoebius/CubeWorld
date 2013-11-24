//-----------------------------
// James Payor - Evolution RTS
// Created 29/11/12
//-----------------------------
//
//--------------
// Net_UDP.hpp |
//-------------------------------------------
// Declares routines for sending and
// receiving UDP messages.
//-------------------------------------------

#ifndef NET_UDP_H
#define NET_UDP_H


// Namespace Net::UDP
namespace Net {
namespace UDP {

	// Initialises networking, able to be called several times, returning a value that indicates success or failure:
	bool init();
	// Closes all sockets and ends networking:
	void end();

	// Opens a UDP socket on the given port, returning an integer label, or -1 to indicate failure:
	int open(int port);
	// Closes a socket, returning a value that indicates success or failure:
	bool close(int socket);

	// Sends a UDP message using the given socket to the given ip address and port:
	bool send(int socket, const void* msg, int length, int ip, int port);

	// Returns the number of bytes available to read (0 if there are no queued messages):
	int available(int socket);
	// Returns a pointer to the data received:
	const void *received();

}
}


#endif
