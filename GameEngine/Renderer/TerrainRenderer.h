#pragma once
#include "..\Utility\SharedIncludes.h"
#include "..\Terrain\Terrain.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\ModelTexture.h"
#include "..\Shader\TerrainShader.h"
#include "..\Utility\Maths.h"

#include <vector>

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

