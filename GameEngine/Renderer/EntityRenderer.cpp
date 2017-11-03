#include "EntityRenderer.h"
#include "../Renderer/MasterRenderer.h"
#include "../Shader/StaticShader.h"

EntityRenderer::EntityRenderer()
{
	//createProjectionMatrix();
}


EntityRenderer::EntityRenderer(StaticShader* shader, mat4* projectionMatrix)
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


void EntityRenderer::render(map<Model*, vector<Entity*>> *e)
{
	assert(e != NULL);

	if (!e->empty())
	{
		for (auto models : *e)
		{
			prepareTeturedModel(models.first);

			vector<Entity*> batch = models.second;
			for (Entity* entity : batch)
			{
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, entity->model()->mesh()->vertexCount(), GL_UNSIGNED_INT, 0);
			}
			unbindModel();
		}
	}
}

void EntityRenderer::prepareTeturedModel(Model* model)
{
	ModelMesh* ModelMesh = model->mesh();

	glBindVertexArray(ModelMesh->id());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture* texture = model->texture();
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
	glm::mat4 *transformationMatrix = Maths::createTransformationMatrix
		(
		entity->position(),
		entity->rx(),
		entity->ry(),
		entity->rz(),
		entity->scale()
		);
	_shader->loadTransformationMatrix(transformationMatrix);
}
