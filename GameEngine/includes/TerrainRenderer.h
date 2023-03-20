#pragma once
#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "common.hpp"
#include "Terrain.h"
#include "ModelMesh.h"
#include "ModelTexture.h"
#include "TerrainShader.h"
#include "Maths.h"

#include <vector>

namespace GameEngine
{
	class TerrainRenderer
	{
	private:
		TerrainShader* _shader;
	public:
		TerrainRenderer();
		~TerrainRenderer();
		TerrainRenderer(TerrainShader* shader, mat4 projectionMatrix);
		void prepareTerrain(Terrain& terrain);
		void unbindModel();
		void loadModelMatrix(Terrain& terrain);
		void render(vector<Terrain>* terrains);
		void bindTextures(Terrain& terrain);
	};
}
#endif