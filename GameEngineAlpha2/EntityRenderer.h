#pragma once

#include <map>

#include <vector>

#include "SharedIncludes.h"
#include "RawModel.h"
#include "TexturedModel.h"

#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"

extern DisplayManager* display;

class EntityRenderer
{
private:
	StaticShader * shader;


	void prepareTeturedModel(TexturedModel model);
	void prepareInstance(Entity entity);
	void unbindTexturedModel();
public:
	EntityRenderer();
	EntityRenderer(StaticShader* shader, glm::mat4 projectionMatrix);
	~EntityRenderer();

	void render(map<TexturedModel, vector<Entity>*>* entities);


};

