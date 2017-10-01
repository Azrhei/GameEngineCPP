#pragma once
#include "SharedIncludes.h"
#include "RawModel.h"
//#include "Texture.h"

#include <vector>
#include <soil.h>

using namespace std;

class Loader
{
private:
	vector<GLuint>* vaos;
	vector<GLuint>* vbos;
	vector<GLuint>* textures;

	GLuint createVAO();
	void storeDataInAttribList(GLuint attribNumber, GLuint coordinateSize, vector<GLfloat> data);
	void unbindVAO();
	void bindIndicesVBO(vector<GLuint> indices);

public:
	Loader();
	~Loader();
	GLuint loadTexture(string fileName);
	RawModel loadToVao(vector<GLfloat> positions, vector<GLfloat> textureCoords, vector<GLuint> indices);
	void cleanUp();

};

