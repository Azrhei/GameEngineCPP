#pragma once
#include "SharedIncludes.h"
#include "Loader.h"
#include "RawModel.h"
#include "ModelTexture.h"

class Terrain
{
private:
	GLint SIZE = 800;
	GLint VERTEX_COUNT = 128;

	GLfloat x;
	GLfloat z;
	RawModel* model;
	ModelTexture* texture;
public:
	Terrain();
	~Terrain();
	Terrain(GLint gridX, GLint gridZ, Loader* loader, ModelTexture* texture);
	GLfloat			getX();
	GLfloat			getZ();
	RawModel*		getModel();
	ModelTexture*	getTexture();
	RawModel*		generateTerrain(Loader* loader);

};