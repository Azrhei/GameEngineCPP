#pragma once
#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <map>
#include <vector>

#include "Light.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "Entity.h"
#include "Model.h" 
#include "TerrainRenderer.h"
#include "TerrainShader.h"

namespace GameEngine
{
		class MasterRenderer
		{
		private:
			const GLfloat FOV = 90;			// used for projection matrix....
			const GLfloat N_Plane = 0.1f;	// used for projection matrix....
			const GLfloat F_Plane = 1200;	// used for projection matrix....
			const GLfloat RED = 0.5f;
			const GLfloat GREEN = 0.5f;
			const GLfloat BLUE = 0.5f;

			StaticShader* _entity_shader;
			TerrainShader* _terrain_shader;

			EntityRenderer* _entity_renderer;
			TerrainRenderer* _terrain_renderer;

			map<Model*, vector<Entity>>* _entities; // goes into entity renderer class
			vector<Terrain>* _terrains; // goes into terrain renderer class

			mat4 projectionMatrix; // do we need to keep this here? 
			void prepare();

		protected:
			mat4 createProjectionMatrix();

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

#endif /* MASTER_RENDERER_H */