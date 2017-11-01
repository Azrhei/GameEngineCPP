#pragma once

#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "..\Utility\SharedIncludes.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\Model.h"
#include "..\Entity\Entity.h"
#include "..\Shader\StaticShader.h"
#include "..\Utility\Maths.h"

#include <map>
#include <vector>

namespace RenderM
{
	class EntityRenderer
	{
	private:
		ShaderM::StaticShader * _shader;

		void prepareTeturedModel(ModelM::Model* model);
		void prepareInstance(EntityM::Entity* entity);
		void unbindModel();
	public:
		EntityRenderer();
		EntityRenderer(ShaderM::StaticShader* shader, mat4* projectionMatrix);
		~EntityRenderer();

		void render(map<ModelM::Model*, vector<EntityM::Entity*>>* entities);

	};
}
#endif /* ENTITY_RENDERER_H */