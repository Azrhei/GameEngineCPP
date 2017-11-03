#pragma once
#ifndef _SHARED_H
#define _SHARED_H

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

#include <iostream>
#include <string>
#include <fstream>

#include "Error.h"

//#define DEBUG 1

//#define nl std::endl
#define NEWLINE					 "\n"
#define WIDE_NEWLINE			L"\n"
#define CARRIAGE_RETURN			 "\r"
#define WIDE_CARRIAGE_RETURN	L"\r"

inline wostream& nl(wostream& o) { return o << WIDE_NEWLINE; }
inline ostream& nl(ostream& o) { return o << NEWLINE; }

#endif