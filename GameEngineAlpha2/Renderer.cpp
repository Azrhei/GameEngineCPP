#include "Renderer.h"
Renderer::Renderer()
{
	createProjectionMatrix();
}


Renderer::Renderer(StaticShader shader)
{
	createProjectionMatrix();
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}


Renderer::~Renderer()
{
}

void Renderer::prepare()
{
#ifdef DEBUG
	wcout << "Preparing to render" << endl;
#endif
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0.4f, 0);


}

void Renderer::render(Entity entity, StaticShader shader)
{
#ifdef DEBUG
	wcout << L"Rendering Model" << endl;
#endif

	TexturedModel model = entity.getModel();
	RawModel rawModel = model.getRawModel();
	

	glBindVertexArray(rawModel.getID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glm::mat4 transformationMatrix = Maths::createTransformationMatrix
		(
		entity.getPosition(), 
		entity.getRX(), 
		entity.getRY(), 
		entity.getRZ(), 
		entity.getScale()
		);
	shader.loadTransformationMatrix(transformationMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getId());
	glDrawElements(GL_TRIANGLES,rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

#ifdef DEBUG
	wcout << L"Model Rendered" << endl;
#endif
}

void Renderer::createProjectionMatrix()
{
	GLfloat aspectRatio = 720 / 1280;
	GLfloat y_scale = (1 / glm::tan(glm::radians(FOV / 2))) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustrum_length = F_Plane - N_Plane;
	
	glm::mat4 matrix{ 1 };
	matrix[0][0] = x_scale;
	matrix[1][1] = y_scale;
	matrix[2][2] = -((F_Plane + N_Plane) / frustrum_length);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * N_Plane * F_Plane) / frustrum_length);
	matrix[3][3] = 0;
}