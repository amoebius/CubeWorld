//-----------------------------
// James Payor - Evolution RTS
// Created 05/03/13
//-----------------------------
//
//-----------------
// Net_Socket.hpp |
//-------------------------------------------
// Declares the Net::Socket class, which will
// allow easy use of the underlying UDP
// routines in networking code.
//-------------------------------------------

#ifndef NET_SOCKET_H
#define NET_SOCKET_H


// Include the exceptions library:
#include <../Headers/Net_Exception.hpp>
#include <../Headers/Net_Message.hpp>

namespace Net {

	// The class responsible for sending and receiving data:
	class Socket {

	public:
		// Construct a socket from a port:
		Socket(int port) throw(Exception::InitialisationError);
		// Closes the socket on destruction:
		~Socket();

		// Send a message to a specified IP address, return value indicating success or failure:
		bool send(Message &msg, int ip) const;
		bool send(Message *msg, int ip) const;

		// Receives a pending message, returning a NULL pointer if there is none.
		Message* recv();

	private:
		int socket, port;

	};

}

#endif
