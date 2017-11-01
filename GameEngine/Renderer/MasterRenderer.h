#pragma once

#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include "..\Light\Light.h"
#include "..\Shader\StaticShader.h"
#include "..\Renderer\EntityRenderer.h"
#include "..\Entity\Entity.h"
#include "..\Model\Model.h" 
#include "..\Renderer\TerrainRenderer.h"
#include "..\Shader\TerrainShader.h"

#include <map>
#include <vector>

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

		ShaderM::StaticShader* _entity_shader;
		ShaderM::TerrainShader* _terrain_shader;

		EntityRenderer* _entity_renderer;
		RenderM::TerrainRenderer* _terrain_renderer;

		map<ModelM::Model*, vector<EntityM::Entity*>>* _entities;
		vector <TerrainM::Terrain* > * _terrains;

		mat4* projectionMatrix;
		void prepare();

	protected:
		mat4* createProjectionMatrix();

	public:
		MasterRenderer();
		~MasterRenderer();
		static void enableCulling();
		static void disableCulling();

		void processTerrain(TerrainM::Terrain* terrain);
		void cleanUp() { _entity_shader->cleanUp(); }
		void processEntity(EntityM::Entity* entity);

		void render(Light* sun, Camera* camera);
	};
}
#endif /* MASTER_RENDERER_H */