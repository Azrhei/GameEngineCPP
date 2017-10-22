#pragma once
#include <map>
#include <vector>

#include "Light.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "Entity.h"
#include "Model.h" 
#include "TerrainRenderer.h"
#include "TerrainShader.h"

class MasterRenderer
{
private:
	const GLfloat FOV = 60;
	const GLfloat N_Plane = 0.1f;
	const GLfloat F_Plane = 300;
	const GLfloat RED = 0.5f;
	const GLfloat GREEN = 0.5f;
	const GLfloat BLUE = 0.5f;

	StaticShader* _entity_shader;
	TerrainShader* _terrain_shader;

	EntityRenderer* _entity_renderer;
	TerrainRenderer* _terrain_renderer;

	map<Model*, vector<Entity*>>* _entities;
	vector<Terrain*>* _terrains;

	mat4* projectionMatrix;
	void prepare();

protected:
	mat4* createProjectionMatrix();

public:
	MasterRenderer();
	//MasterRenderer(StaticShader * shader);
	~MasterRenderer();
	static void enableCulling();
	static void disableCulling();

	void processTerrain(Terrain* terrain);
	void cleanUp() { _entity_shader->cleanUp(); }
	void processEntity(Entity* entity);

	void render(Light* sun, ICamera* camera);
};

