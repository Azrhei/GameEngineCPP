#pragma once

#ifndef LOADER_H
#define LOADER_H

#include "..\Utility\SharedIncludes.h"
#include "..\Model\ModelMesh.h"

#include <vector>
#include <soil.h>

namespace UtilityM
{
	class Loader
	{
	private:
		static Loader* _instance;
		static vector<GLuint>* _vaos;
		static vector<GLuint>* _vbos;
		static vector<GLuint>* _textures;
		static GLint default_texture;
		static string default_texture_filename;
		static GLint getDefaultTexture();
		static GLuint createVAO();
		static void storeDataInAttribList(GLint attribNumber, GLint coordinateSize, vector<GLfloat>* data);
		static void unbindVAO();
		static void bindIndicesVBO(vector<GLint>* indices);
		Loader();

	public:
		static void init() {};
		~Loader() noexcept;
		static GLint loadTexture(string fileName);
		static ModelM::ModelMesh * loadToVao(vector<GLfloat>* positions, vector<GLfloat>* textureCoords, vector<GLfloat>* normals, vector<GLint>* indices);
		static void cleanUp();
	};
}
#endif /* LOADER_H */