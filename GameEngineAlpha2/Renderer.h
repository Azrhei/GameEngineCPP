#pragma once
#include "SharedIncludes.h"
#include "RawModel.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"

class Renderer
{
private:
	GLfloat FOV = 70;
	GLfloat N_Plane = 0.1f;
	GLfloat F_Plane = 1000;

	glm::mat4 projectionMatrix;
	void createProjectionMatrix();
public:
	Renderer();
	Renderer(StaticShader shader);
	~Renderer();

	void prepare();
	void render(Entity entity, StaticShader shader);

};

