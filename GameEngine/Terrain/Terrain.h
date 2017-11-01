#pragma once

#ifndef TERRAIN_H
#define TERRAIN_H

#include "TerrainTexture.h"
#include "TerrainTexturePack.h"

#include "..\Utility\SharedIncludes.h"
#include "..\Utility\Loader.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\ModelTexture.h"

namespace TerrainM {
	class Terrain
	{
	private:
		GLint SIZE = 8000;
		GLint VERTEX_COUNT = 256;

		GLfloat _x;
		GLfloat _z;
		ModelM::ModelMesh* _mesh;
		TerrainTexturePack* _texturePack;
		TerrainTexture* _blendMap; 

	protected:

		//Setters
		void x(GLfloat val) { _x = val; }
		void z(GLfloat val) { _z = val; }
		void mesh(ModelM::ModelMesh* val) { _mesh = val; }
		void texturePack(TerrainTexturePack* val) { _texturePack = val; }
		void blendMap(TerrainTexture* val) { _blendMap = val; }
		  
	public:
		Terrain() = delete;
		Terrain(const Terrain& t) = default;
		Terrain&& operator=(const Terrain& t) = delete;
		~Terrain();
		Terrain(GLint gridX, GLint gridZ, TerrainTexturePack* texturePack, TerrainTexture* blendMap);

		//Getters
		GLfloat	x() { return _x; }
		GLfloat	z() { return _z; }
		ModelM::ModelMesh* mesh() { return _mesh; }
		TerrainTexturePack*	texturePack() { return _texturePack; }
		TerrainTexture * blendMap() { return _blendMap; }

		ModelM::ModelMesh* generateTerrain();
	};
}
#endif /* TERRAIN_H */