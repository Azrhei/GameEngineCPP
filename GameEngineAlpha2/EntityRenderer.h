#pragma once

#include <map>

#include <vector>

#include "SharedIncludes.h"
#include "ModelMesh.h"
#include "Model.h"

#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"

extern DisplayManager* display;

class EntityRenderer
{
private:
	StaticShader * _shader;

	void prepareTeturedModel(Model* model);
	void prepareInstance(Entity* entity);
	void unbindModel();
public:
	EntityRenderer();
	EntityRenderer(StaticShader* shader, glm::mat4* projectionMatrix);
	~EntityRenderer();

	void render(map<Model*, vector<Entity*>>* entities);


};

