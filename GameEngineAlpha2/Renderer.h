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

class Renderer
{
private:
	GLfloat FOV = 60;
	GLfloat N_Plane = 0.1f;
	GLfloat F_Plane = 300;

	StaticShader* shader ;
	glm::mat4 projectionMatrix;
	glm::mat4 createProjectionMatrix();
	void Renderer::prepareTeturedModel(TexturedModel model);
	void prepareInstance(Entity entity);
	void unbindTexturedModel();
public:
	Renderer();
	Renderer(StaticShader* shader);
	~Renderer();

	void prepare();
	//void render(Entity entity, StaticShader* shader);
	void render(map<TexturedModel, vector<Entity>> entities);


};

