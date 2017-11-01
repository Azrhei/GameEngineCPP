#include "EntityRenderer.h"
#include "../Renderer/MasterRenderer.h"
#include "../Shader/StaticShader.h"

namespace RenderM
{
	EntityRenderer::EntityRenderer()
	{
		//createProjectionMatrix();
	}


	EntityRenderer::EntityRenderer(ShaderM::StaticShader* shader, mat4* projectionMatrix)
	{
		_shader = shader;

		//createProjectionMatrix();

		_shader->start();
		_shader->loadProjectionMatrix(projectionMatrix);
		_shader->stop();
	}


	EntityRenderer::~EntityRenderer()
	{
	}


	void EntityRenderer::render(map<ModelM::Model*, vector<EntityM::Entity*>> *e)
	{
		assert(e != NULL);

		if (!e->empty())
		{
			for (auto models : *e)
			{
				prepareTeturedModel(models.first);

				vector<EntityM::Entity*> batch = models.second;
				for (EntityM::Entity* entity : batch)
				{
					prepareInstance(entity);
					glDrawElements(GL_TRIANGLES, entity->model()->mesh()->vertexCount(), GL_UNSIGNED_INT, 0);
				}
				unbindModel();
			}
		}
	}

	void EntityRenderer::prepareTeturedModel(ModelM::Model* model)
	{
		ModelM::ModelMesh* ModelMesh = model->mesh();

		glBindVertexArray(ModelMesh->id());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		ModelM::ModelTexture* texture = model->texture();
		if (texture->hasTransparency())
		{
			MasterRenderer::disableCulling();
		}
		if (texture->useFakeLighting())
		{
			_shader->loadFakeLighting(true);
		}
		_shader->loadShineVariables(texture->shineDampener(), texture->reflectivity());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model->texture()->id());
	}

	void EntityRenderer::unbindModel()
	{
		MasterRenderer::enableCulling();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	void EntityRenderer::prepareInstance(Entity* entity)
	{
		mat4 *transformationMatrix = UtilityM::Maths::createTransformationMatrix
		(
			entity->position(),
			entity->rx(),
			entity->ry(),
			entity->rz(),
			entity->scale()
		);
		_shader->loadTransformationMatrix(transformationMatrix);
	}
}