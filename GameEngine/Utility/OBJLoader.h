#pragma once

#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glm\glm.hpp>
#include <vector>
#include <fstream>
#include "..\Utility\common.hpp"
#include "..\Model\ModelMesh.h"
#include "..\Utility\Loader.h"

using namespace glm;

namespace GameEngine
{
	using namespace ModelM;

	namespace UtilityM
	{
		class OBJLoader
		{
		public:
			static OBJLoader& getInstance()
			{
				static OBJLoader _inst_; // Create first time only....natural feature of static init;
				return _inst_; // return value.
			}

		private:
			OBJLoader() {};

			string default_model_filename = "default";
			ModelMesh * default_model = nullptr;
			ModelMesh * getDefaultModel();

		public:
			~OBJLoader();

			OBJLoader(OBJLoader const&) = delete;
			void operator=(OBJLoader const&) = delete;

			ModelMesh * loadOBJ(string path);

			void OBJLoader::processVertex
			(
				ivec3 vertex,
				vector<GLint>* ind,
				vector<vec2>* tex,
				vector<vec3>* norm,
				vector<GLfloat>* texArray,
				vector<GLfloat>* normArray
			);
		};
		static OBJLoader& objLoader = OBJLoader::getInstance();
	}
}
#endif /* OBJ_LOADER_H */