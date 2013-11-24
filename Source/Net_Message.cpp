//-----------------------------
// James Payor - Evolution RTS
// Created 05/03/13
//-----------------------------
//
//------------------
// Net_Message.cpp |
//-------------------------------------------
// Implements the Net::Message class, used to
// store and represent binary data for use in
// networking.
//-------------------------------------------


// Required standard headers:
#include <cstdlib>
#include <cstring>

// Required Net headers:
#include <../Headers/Net_Message.hpp>
#include <../Headers/Net_Exception.hpp>


namespace Net {

	// Construct a message, copying the data pointed to by the parameters:
	Message::Message(const void *source, int length) throw(Exception::InitialisationError) {
		len = length;
		data = malloc(len);
		if(!data) throw Exception::InitialisationError();
		memcpy(data, source, len);
	}

	// Construct a message, copying the cstring given:
	Message::Message(const char *source) throw(Exception::InitialisationError) {
		len = strlen(source);
		data = malloc(len);
		if(!data) throw Exception::InitialisationError();
		memcpy(data, source, len);
	}

	// Free the memory as the message is destroyed:
	Message::~Message() {
		free(data);
	}

	// Return the length:
	int Message::length() const {
		return len;
	}

	// Return a pointer to the data:
	const void *Message::bytes() const {
		return data;
	}

}
