#include "EntityRenderer.h"

EntityRenderer::EntityRenderer()
{
	//createProjectionMatrix();
}


EntityRenderer::EntityRenderer(StaticShader* shader, glm::mat4 projectionMatrix)
{
	this->shader = shader;

	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}


EntityRenderer::~EntityRenderer()
{
}


void EntityRenderer::render(map<TexturedModel*, vector<Entity*>> *e)
{
	if (!e->empty())
	{
		for (auto models : *e)
		{
			prepareTeturedModel(models.first);

			vector<Entity*> batch = models.second;
			for (Entity* entity : batch)
			{
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, entity->getModel()->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
			}
			unbindTexturedModel();
		}
	}
}

void EntityRenderer::prepareTeturedModel(TexturedModel* model)
{
	RawModel* rawModel = model->getRawModel();

	glBindVertexArray(rawModel->getID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture* texture = model->getTexture();
	shader->loadShineVariables(texture->getshineDampener(), texture->getreflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
}

void EntityRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity* entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix
		(
		entity->getPosition(),
		entity->getRX(),
		entity->getRY(),
		entity->getRZ(),
		entity->getScale()
		);
	shader->loadTransformationMatrix(transformationMatrix);
}
