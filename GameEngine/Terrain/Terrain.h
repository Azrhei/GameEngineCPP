#pragma once

#include "TerrainTexture.h"
#include "TerrainTexturePack.h"

#include "..\Utility\common.hpp"
#include "..\Utility\Loader.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\ModelTexture.h"

using namespace GameEngine;
using namespace ModelM;

class Terrain
{
private:
	GLint SIZE = 8000;
	GLint VERTEX_COUNT = 256;

	GLfloat _x;
	GLfloat _z;
	ModelMesh& _mesh;
	TerrainTexturePack* _texturePack;
	TerrainTexture* _blendMap;

protected:

	//Setters
	void x(GLfloat val){ _x = val; }
	void z(GLfloat val){ _z = val; }
	void mesh(ModelMesh& val){ _mesh = val; }
	void texturePack(TerrainTexturePack* val){ _texturePack = val; }
	void blendMap(TerrainTexture* val) { _blendMap = val; }

public:
	Terrain() = delete;
	~Terrain();
	Terrain
		(
		GLint gridX, 
		GLint gridZ, 
		TerrainTexturePack* texturePack,
		TerrainTexture* blendMap
		);

	//Getters
	GLfloat			x() { return _x; }
	GLfloat			z() { return _z; }
	ModelMesh&		mesh(){ return _mesh; }
	TerrainTexturePack*	texturePack(){ return _texturePack; }
	TerrainTexture * blendMap() { return _blendMap; }

	ModelMesh&		generateTerrain(const char * heightMap);

};