#pragma once
//
#ifndef _SHARED_H
#define _SHARED_H
// This header is used by most or all GameEngine components.

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <glew/glew.h>
#include <glew/wglew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>


using namespace glm;

using namespace std; // I know, really stupid idea....

#include "Error.h"
#include <iostream>

// All of this to speed up output. Removing outstream flushes and setup for auto UTF text
#define NEWLINE					 "\n"
#define WIDE_NEWLINE			L"\n"
#define CARRIAGE_RETURN			 "\r"
#define WIDE_CARRIAGE_RETURN	L"\r"

inline wostream& nl(wostream& o) { return o << WIDE_NEWLINE; }
inline ostream& nl(ostream& o) { return o << NEWLINE; }

#endif