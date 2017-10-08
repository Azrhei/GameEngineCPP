#pragma once
#include "SharedIncludes.h"
#include "RawModel.h"
#include <glm\glm.hpp>
#include <vector>
#include <fstream>
#include "Loader.h"

using namespace glm;

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	static RawModel * loadOBJ
		(
		string path,
		Loader * loader
		);
	static void OBJLoader::processVertex
		(
		ivec3 vertex,
		vector<GLint>* ind,
		vector<vec2>* tex,
		vector<vec3>* norm,
		vector<GLfloat>* texArray,
		vector<GLfloat>* normArray
		);
private:
};

