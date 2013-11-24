//-----------------------------
// James Payor - Evolution RTS
// Created 14/03/12
//-----------------------------
//
//--------------------
// Net_Exception.hpp |
//-------------------------------------------
// Declares standard networking exceptions,
// to allow error handling in the networking
// library.
//-------------------------------------------

// Include guard:
#ifndef NET_EXCEPTION_H
#define NET_EXCEPTION_H


// Include relevant standard libraries:
#include <exception>
#include <string>


// Namespace Net::Exception:
namespace Net {
namespace Exception {

	class NetException : public std::exception {};

	// Error on initialisation:
	class InitialisationError : public NetException {};

}
}


#endif
