#pragma once
//
#ifndef _SHARED_H
#define _SHARED_H
// This header is used by most or all GameEngine components.

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Error.h"

#define NEWLINE					 "\n"
#define WIDE_NEWLINE			L"\n"
#define CARRIAGE_RETURN			 "\r"
#define WIDE_CARRIAGE_RETURN	L"\r"

inline wostream& nl(wostream& o) { return o << WIDE_NEWLINE; }
inline ostream& nl(ostream& o) { return o << NEWLINE; }

#define UM	UtiltyM
#define GM	GameM
#define DM	DisplayM
#define EM	EntityM
#define TM	TerrainM
#define MM	ModelM
#define RM	RenderM
#define SM	ShaderM

#endif