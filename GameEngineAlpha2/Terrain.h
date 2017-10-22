#pragma once
#include "SharedIncludes.h"
#include "Loader.h"
#include "ModelMesh.h"
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
	ModelMesh* _mesh;
	TerrainTexturePack* _texturePack;
	TerrainTexture* _blendMap;

protected:

	//Setters
	void x(GLfloat val){ _x = val; }
	void z(GLfloat val){ _z = val; }
	void mesh(ModelMesh* val){ _mesh = val; }
	void texturePack(TerrainTexturePack* val){ _texturePack = val; }
	void blendMap(TerrainTexture* val) { _blendMap = val; }

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

	//Getters
	GLfloat			x() { return _x; }
	GLfloat			z() { return _z; }
	ModelMesh*		mesh(){ return _mesh; }
	TerrainTexturePack*	texturePack(){ return _texturePack; }
	TerrainTexture * blendMap() { return _blendMap; }

	ModelMesh*		generateTerrain(Loader* loader);

};