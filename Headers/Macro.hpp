//-----------------------------
// James Payor - Evolution RTS
// Created 20/03/13
//-----------------------------
//
//------------
// Macro.hpp |
//-------------------------------------------
// Declares commonly used macros.
//-------------------------------------------

#ifndef MACRO_H
#define MACRO_H


// For loop macro to loop 'i' over the range [0,n) :
#define fo(i,n) for(int i=0, _n=(n); i<_n; i++)

// For loop macro to loop 'i' over the range [a,b) :
#define range(i,a,b) for(int i=(a), _b=(b); i<_b; i++)

// That's all folks!

#endif
