#pragma once
#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include <map>
#include <vector>

#include "..\Utility\common.hpp"
#include "..\Model\ModelMesh.h"
#include "..\Model\Model.h"
#include "..\Display\Display.h"
#include "..\Entity\Entity.h"
#include "..\Shader\StaticShader.h"
#include "..\Utility\Maths.h"

namespace GameEngine
{
	using namespace DisplayM;
	using namespace EntityM;
	using namespace ShaderM;

	namespace RenderM
	{
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
	}
}
#endif /* ENTITY_RENDERER_H */
