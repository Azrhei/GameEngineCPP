#pragma once
#include <map>
#include <vector>

#include "Light.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "Entity.h"
#include "TexturedModel.h" 
#include "TerrainRenderer.h"
#include "TerrainShader.h"

class MasterRenderer
{
private:
	GLfloat FOV = 60;
	GLfloat N_Plane = 0.1f;
	GLfloat F_Plane = 300;

	StaticShader* shader;
	TerrainShader* terrain_shader;

	EntityRenderer* entity_renderer;
	TerrainRenderer* terrain_renderer;

	map<TexturedModel*, vector<Entity*>>* entities;
	vector<Terrain*>* terrains;

	glm::mat4* projectionMatrix;
	void prepare();

protected:
	glm::mat4* createProjectionMatrix();

public:
	MasterRenderer();
	//MasterRenderer(StaticShader * shader);
	~MasterRenderer();
	void processTerrain(Terrain* terrain);
	void cleanUp() { shader->cleanUp(); }
	void processEntity(Entity* entity);

	void render(Light* sun, ICamera* camera);
};

