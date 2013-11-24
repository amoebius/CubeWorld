//-----------------------------
// James Payor - Evolution RTS
// Created 05/03/13
//-----------------------------
//
//-----------------
// Net_Socket.cpp |
//-------------------------------------------
// Implements the Net::Socket class, to allow
// easy use of the underlying UDP routines in
// networking code.
//-------------------------------------------

// Required headers:
#include <../Headers/Net_Socket.hpp>
#include <../Headers/Net_Message.hpp>
#include <../Headers/Net_UDP.hpp>
#include <../Headers/Net_Exception.hpp>


namespace Net {

	// Open a socket on the given port:
	Socket::Socket(int port) throw(Exception::InitialisationError) {
		this->port = port;
		socket = UDP::open(port);
		// Raise an error if the socket couldn't be opened:
		if(socket == -1) throw Exception::InitialisationError();
	}

	// Close the socket as the object is destroyed:
	Socket::~Socket() {
		UDP::close(socket);
	}

	// Sends a message to a specified IP, the return value indicating success or failure:
	bool Socket::send(Message& msg, int ip) const {
		UDP::send(socket, msg.bytes(), msg.length(), ip, port);
	}
	// Overloads send to allow a pointer to be passed:
	bool Socket::send(Message *msg, int ip) const {
		this->send(*msg, ip);
	}

	// Receives a pending message, returning a NULL pointer if there is none.
	Message* Socket::recv() {
		int len = UDP::available(socket);
		if(len) return new Message(UDP::received(), len);
		return NULL;
	}

}
