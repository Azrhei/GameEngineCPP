#pragma once

#ifndef LOADER_H
#define LOADER_H

#include "..\Utility\common.hpp"
#include "..\Model\ModelMesh.h"

#include <vector>
#include <soil.h>

using namespace std;

namespace GameEngine {
	using namespace ModelM;

	namespace UtilityM {
		class Loader
		{
		public:
			static Loader& getIntance()
			{
				static Loader _inst_;
				return _inst_;
			}
		private:
			string Loader::default_texture_filename = "default";
			GLint Loader::default_texture = 0;

			vector<GLuint>* _vaos = new vector<GLuint>();
			vector<GLuint>* _vbos = new vector<GLuint>(); 
			vector<GLuint>* _textures = new vector<GLuint>();

			GLint getDefaultTexture();
			GLuint createVAO();
			void storeDataInAttribList(GLint attribNumber, GLint coordinateSize, vector<GLfloat>* data);
			void unbindVAO();
			void bindIndicesVBO(vector<GLint>* indices);

		public:
			Loader() {};
			Loader(Loader const&) = delete;
			void operator=(Loader const&) = delete;

			~Loader();
			GLint loadTexture(string fileName);
			ModelMesh * loadToVao
			(
				vector<GLfloat>* positions,
				vector<GLfloat>* textureCoords,
				vector<GLfloat>* normals,
				vector<GLint>* indices);
			void cleanUp();

		};
		static Loader& loader = Loader::getIntance();
	}
}

#endif /* LOADER_H */