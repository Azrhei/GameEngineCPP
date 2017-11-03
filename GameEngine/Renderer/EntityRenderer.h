#pragma once

#include <map>
#include <vector>

#include "..\Utility\SharedIncludes.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\Model.h"
#include "..\Display\DisplayManager.h"
#include "..\Entity\Entity.h"
#include "..\Shader\StaticShader.h"
#include "..\Utility\Maths.h"

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

