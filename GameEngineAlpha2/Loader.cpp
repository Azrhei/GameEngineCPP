#include "Loader.h"

Loader::Loader()
: vaos(new vector<GLuint>), vbos(new vector<GLuint>), textures(new vector<GLuint>)
{
}


Loader::~Loader()
{
	cleanUp();
	delete vaos;
	delete vbos;
	delete textures;
}

RawModel Loader::loadToVao
	(
	vector<GLfloat>* positions, 
	vector<GLfloat>* textureCoords, 
	vector<GLfloat>* normals, 
	vector<GLint>* indices
	)
{
	RawModel model;
	GLuint vaoID = createVAO();
	bindIndicesVBO(indices);

	if (positions->size() > 0) storeDataInAttribList(0, 3, positions );
	if (textureCoords->size() > 0) storeDataInAttribList(1, 2, textureCoords);
	if (normals->size() > 0) storeDataInAttribList(2, 3, normals);

	unbindVAO();
	model = { vaoID, indices->size() };
	return model;
}

GLuint Loader::createVAO()
{
	GLuint i;
	glGenVertexArrays(1, &i);
	vaos->push_back(i);
	glBindVertexArray(i);
	return i;
}

void Loader::storeDataInAttribList(GLint attribNumber, GLint coordinateSize, vector<GLfloat>* data)
{
	GLuint i;
	glGenBuffers(1, &i);
	vbos->push_back(i);
	glBindBuffer(GL_ARRAY_BUFFER, i);
	glBufferData(GL_ARRAY_BUFFER, data->size() /** coordinateSize*/ * sizeof(GLfloat), &data->front(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribNumber, coordinateSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::cleanUp()
{
	glDeleteVertexArrays(vaos->size(), &(*vaos)[0]);
	glDeleteBuffers(vbos->size(), &(*vbos)[0]);
	glDeleteTextures(textures->size(), &(*textures)[0]);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::bindIndicesVBO(vector<GLint>* indices)
{
	GLuint i;
	glGenBuffers(1, &i);
	vbos->push_back(i);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i);
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()/* * 3 */* sizeof(GLuint), &indices->front(), GL_STATIC_DRAW);
}

GLint Loader::loadTexture(string fileName)
{
	//Texture texture = 0;

	GLuint textureId;
	glGenTextures(1, &textureId);

	unsigned char * image;
	GLint height = 0, width = 0;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	image = SOIL_load_image(("res/" + fileName + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
	{
		wcout << L"No texture loaded" << endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures->push_back(textureId);

	return textureId;
}
