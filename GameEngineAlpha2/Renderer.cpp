#include "Renderer.h"
Renderer::Renderer()
{
	createProjectionMatrix();
}


Renderer::Renderer(StaticShader* shader)
{
	this->shader = shader;
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	createProjectionMatrix();
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}


Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0, 0.0f, 0);
}

void Renderer::render(map<TexturedModel, vector<Entity>> e)
{
	for (auto models : e)
	{
		prepareTeturedModel(models.first);

		vector<Entity> batch = models.second;
		for (Entity entity : batch)
		{
			prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void Renderer::prepareTeturedModel(TexturedModel model)
{
	RawModel rawModel = model.getRawModel();

	glBindVertexArray(rawModel.getID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture texture = model.getTexture();
	shader->loadShineVariables(texture.getshineDampener(), texture.getreflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getId());
}

void Renderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::prepareInstance(Entity entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix
		(
		entity.getPosition(),
		entity.getRX(),
		entity.getRY(),
		entity.getRZ(),
		entity.getScale()
		);
	shader->loadTransformationMatrix(transformationMatrix);
}

glm::mat4 Renderer::createProjectionMatrix()
{
	
	GLfloat aspectRatio =  ::display->getWidth() / ::display->getHeight();
	GLfloat y_scale = (1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustrum_length = F_Plane - N_Plane;
	
	glm::mat4 matrix{ 1 };
	matrix[0][0] = x_scale;
	matrix[1][1] = y_scale;
	matrix[2][2] = -((F_Plane + N_Plane) / frustrum_length);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * N_Plane * F_Plane) / frustrum_length);
	matrix[3][3] = 0;

	return matrix;
}