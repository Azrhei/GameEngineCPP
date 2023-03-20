#include "Loader.h"
#include "Error.h"
#include <fstream>
#include "common.hpp"

namespace GameEngine {
	//image_data* Loader::loadPNGImage(string filename)
	//{
	//	image_data* result = new image_data{};
	//	result->_data = SOIL_load_image
	//	(
	//		"terrain.tga",
	//		&result->_width, &result->_height, &result->_channels,
	//		SOIL_LOAD_AUTO
	//	);
	//	return result;
	//}

	//void Loader::destroyPNGImage(image_data* data)
	//{
	//	delete data;
	//}

	Loader::~Loader()
	{
		cleanUp();
	}

	ModelMesh& Loader::loadToVao
	(
		vector<GLfloat>& positions,
		vector<GLfloat>& textureCoords,
		vector<GLfloat>& normals,
		vector<GLint>& indices
	)
	{
		GLuint vaoID = createVAO();
		bindIndicesVBO(indices);

		if (positions.size() > 0) storeDataInAttribList(0, 3, positions);
		if (textureCoords.size() > 0) storeDataInAttribList(1, 2, textureCoords);
		if (normals.size() > 0) storeDataInAttribList(2, 3, normals);


		ModelMesh& mesh = *(new ModelMesh(vaoID, (GLsizei)indices.size()));
		unbindVAO();
		return std::move(mesh);
	}

	GLuint Loader::createVAO()
	{
		GLuint i = 0;
		glGenVertexArrays(1, &i);
		_vaos.push_back(i);
		glBindVertexArray(i);
		return i;
	}

	void Loader::storeDataInAttribList(GLint attribNumber, GLint coordinateSize, vector<GLfloat>& _data)
	{
		GLuint i = 0;
		glGenBuffers(1, &i);
		_vbos.push_back(i);
		glBindBuffer(GL_ARRAY_BUFFER, i);
		glBufferData(GL_ARRAY_BUFFER, (GLsizei)_data.size() * sizeof(GLfloat), (_data.data()), GL_STATIC_DRAW);
		glVertexAttribPointer(attribNumber, coordinateSize, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Loader::cleanUp()
	{
		if (_vaos.size() > 0)
		{
			glDeleteVertexArrays((GLsizei)_vaos.size(), _vaos.data());
		}
		if (_vbos.size() > 0)
		{
			glDeleteBuffers((GLsizei)_vbos.size(), _vbos.data());
		}
		if (_textures.size() > 0)
		{
			glDeleteTextures((GLsizei)_textures.size(), _textures.data());
		}
	}

	void Loader::unbindVAO()
	{
		glBindVertexArray(0);
	}

	void Loader::bindIndicesVBO(vector<GLint>& indices)
	{
		GLuint i = 0;
		glGenBuffers(1, &i);
		_vbos.push_back(i);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)indices.size() * sizeof(GLuint), /*&(indices)[0]*/ (indices.data()), GL_STATIC_DRAW);
	}

	GLint Loader::loadTexture(string fileName)
	{
		//Texture texture = 0;

		GLuint textureId = 0;
		glGenTextures(1, &textureId);

		unsigned char* image;
		GLint height = 0, width = 0;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		image = SOIL_load_image(("res/" + fileName + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
		{
			wcout << L"No texture loaded" << nl;
			ifstream ifile(("res/" + default_texture_filename + ".obj").c_str());
			if (ifile)
			{
				return getDefaultTexture();
			}
			else
			{
				exit(EXIT_CODES::DEFAULT_FILE_MISSING);
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		_textures.push_back(textureId);

		return textureId;
	}

	GLint Loader::getDefaultTexture()
	{
		if (!Loader::default_texture)
		{
			Loader::default_texture = loadTexture(Loader::default_texture_filename);
		}
		return Loader::default_texture;
	}
}