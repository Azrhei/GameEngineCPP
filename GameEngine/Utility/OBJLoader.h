#pragma once

#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "..\Utility\SharedIncludes.h"
#include "..\Model\ModelMesh.h"
#include "..\Utility\Loader.h"

#include <vector>
#include <fstream>

namespace UtilityM
{
	class OBJLoader
	{
	private:
		static string default_model_filename;
		static ModelM::ModelMesh * default_model;
		static ModelM::ModelMesh * getDefaultModel();

	protected:

	public:
		OBJLoader();
		~OBJLoader();

		static ModelM::ModelMesh * loadOBJ
		(string path	);

		static void OBJLoader::processVertex
		(
			ivec3 vertex,
			vector<GLint>* ind,
			vector<vec2>* tex,
			vector<vec3>* norm,
			vector<GLfloat>* texArray,
			vector<GLfloat>* normArray
		);
	};
}
#endif /* OBJLOADER_H */