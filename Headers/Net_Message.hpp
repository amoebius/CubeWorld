//-----------------------------
// James Payor - Evolution RTS
// Created 05/03/13
//-----------------------------
//
//------------------
// Net_Message.hpp |
//-------------------------------------------
// Declares the Net::Message class, used to
// store and represent binary data for use in
// networking.
//-------------------------------------------

#ifndef NET_MESSAGE_H
#define NET_MESSAGE_H


// Include the exceptions library:
#include <../Headers/Net_Exception.hpp>

namespace Net {

	// Stores the data comprising a message:
	class Message {

	public:
		// Construct a message from a buffer:
		Message(const void *source, int length) throw(Exception::InitialisationError);
		// Construct a message from a cstring:
		Message(const char *source) throw(Exception::InitialisationError);
		// Free the data on destruction:
		~Message();

		// Get the length of the message:
		int length() const;
		// Get a pointer to the message's data:
		const void *bytes() const;

	private:
		void *data;
		int len;

	};

}


#endif
