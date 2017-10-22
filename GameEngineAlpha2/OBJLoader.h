#pragma once
#include "SharedIncludes.h"
#include "ModelMesh.h"
#include <glm\glm.hpp>
#include <vector>
#include <fstream>
#include "Loader.h"

using namespace glm;

class OBJLoader
{
private:
	static string default_model_filename;
	static ModelMesh * default_model;
	static ModelMesh * getDefaultModel(Loader *loader);

public:
	OBJLoader();
	~OBJLoader();

	static ModelMesh * loadOBJ
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

