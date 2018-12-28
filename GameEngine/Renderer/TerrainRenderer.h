#pragma once
#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "..\Utility\common.hpp"
#include "..\Terrain\Terrain.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\ModelTexture.h"
#include "..\Shader\TerrainShader.h"
#include "..\Utility\Maths.h"

#include <vector>

namespace GameEngine
{
	using namespace ShaderM;
	namespace RenderM
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
}
#endif