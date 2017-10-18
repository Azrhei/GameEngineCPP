#pragma once
#include "SharedIncludes.h"
#include "Loader.h"
#include "RawModel.h"
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"
#include "ModelTexture.h"

class Terrain
{
private:
	GLint SIZE = 8000;
	GLint VERTEX_COUNT = 256;

	GLfloat _x;
	GLfloat _z;
	RawModel* _model;
	TerrainTexturePack* _texturePack;
	TerrainTexture* _blendMap;
public:
	Terrain();
	~Terrain();
	Terrain
		(
		GLint gridX, 
		GLint gridZ, 
		Loader* loader, 
		TerrainTexturePack* texturePack,
		TerrainTexture* blendMap
		);
	GLfloat			x();
	GLfloat			z();
	RawModel*		model();
	TerrainTexturePack*	texturePack();
	TerrainTexture * blendMap();
	RawModel*		generateTerrain(Loader* loader);

};