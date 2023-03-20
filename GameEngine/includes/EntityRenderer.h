#pragma once
#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include <map>
#include <vector>

#include "common.hpp"
#include "ModelMesh.h"
#include "Model.h"
#include "Display.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"

namespace GameEngine
{
		class EntityRenderer
		{
		private:
			StaticShader* _shader;

			void prepareTeturedModel(Model* model);
			void prepareInstance(Entity& entity);
			void unbindModel();
		public:
			EntityRenderer();
			EntityRenderer(StaticShader* shader, mat4 projectionMatrix);
			~EntityRenderer();

			void render(map<Model*, vector<Entity>>* entities);


		};
	
}
#endif /* ENTITY_RENDERER_H */
