#pragma once
#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <map>
#include <vector>

#include "..\Light\Light.h"
#include "..\Shader\StaticShader.h"
#include "..\Renderer\EntityRenderer.h"
#include "..\Entity\Entity.h"
#include "..\Model\Model.h" 
#include "..\Renderer\TerrainRenderer.h"
#include "..\Shader\TerrainShader.h"

namespace GameEngine
{
	using namespace EntityM;
	using namespace ShaderM;
	using namespace ModelM;

	namespace RenderM
	{
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

			map<Model*, vector<Entity>>* _entities;
			vector<Terrain>* _terrains;

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

			void processTerrain(Terrain terrain);
			void cleanUp() { _entity_shader->cleanUp(); }
			void processEntity(Entity& entity);

			void render(Light& sun, Camera& camera);
		};
	}
}
#endif /* MASTER_RENDERER_H */