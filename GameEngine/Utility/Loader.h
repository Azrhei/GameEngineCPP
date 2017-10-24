#pragma once
#include "..\Utility\SharedIncludes.h"
#include "..\Model\ModelMesh.h"

#include <vector>
#include <soil.h>

using namespace std;

class Loader
{
private:
	vector<GLuint>* _vaos;
	vector<GLuint>* _vbos;
	vector<GLuint>* _textures;
	static GLint default_texture;
	static string default_texture_filename;
	GLint getDefaultTexture();
	GLuint createVAO();
	void storeDataInAttribList(GLint attribNumber, GLint coordinateSize, vector<GLfloat>* data);
	void unbindVAO();
	void bindIndicesVBO(vector<GLint>* indices);

public:
	Loader();
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