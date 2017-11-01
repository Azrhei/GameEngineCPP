#pragma once

#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "..\Utility\SharedIncludes.h"
#include "..\Terrain\Terrain.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\ModelTexture.h"
#include "..\Shader\TerrainShader.h"
#include "..\Utility\Maths.h"

#include <vector>

namespace RenderM
{
	class TerrainRenderer
	{
	private:
		ShaderM::TerrainShader* _shader;
	public:
		TerrainRenderer();
		~TerrainRenderer();
		TerrainRenderer(ShaderM::TerrainShader* shader, glm::mat4* projectionMatrix);
		void prepareTerrain(TerrainM::Terrain* terrain);
		void unbindModel();
		void loadModelMatrix(TerrainM::Terrain* terrain);
		void render(vector<TerrainM::Terrain*>* terrains);
		void bindTextures(TerrainM::Terrain* terrain);
	};
#ifndef TERRAINM
#define TERRAINM
#endif /* TERRAINM */
}

#endif /* TERRAIN_RENDERER_H */