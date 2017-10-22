#pragma once
#include "SharedIncludes.h"
#include <vector>
#include "Terrain.h"
#include "ModelMesh.h"
#include "ModelTexture.h"
#include "TerrainShader.h"
#include "Maths.h"

class TerrainRenderer
{
private:
	TerrainShader* _shader;
public:
	TerrainRenderer();
	~TerrainRenderer();
	TerrainRenderer(TerrainShader* shader, glm::mat4* projectionMatrix);
	void prepareTerrain(Terrain* terrain);
	void unbindModel();
	void loadModelMatrix(Terrain* terrain);
	void render(vector<Terrain*>* terrains);
	void bindTextures(Terrain* terrain);
};

