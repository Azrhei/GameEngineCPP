#include "Maths.h"

Maths::~Maths()
{
}

glm::mat4* Maths::createTransformationMatrix(
	glm::fvec3 translation,
	GLfloat rx,
	GLfloat ry,
	GLfloat rz,
	GLfloat scale
	)
{
	glm::mat4* matrix=new glm::mat4 {};

	*matrix = glm::translate(*matrix, translation);
	*matrix = glm::rotate(*matrix, glm::radians(rx), glm::vec3{ 1, 0, 0 });
	*matrix = glm::rotate(*matrix, glm::radians(ry), glm::vec3{ 0, 1, 0 });
	*matrix = glm::rotate(*matrix, glm::radians(rz), glm::vec3{ 0, 0, 1 });
	*matrix = glm::scale(*matrix, glm::vec3(scale, scale, scale));

	return matrix;
}

glm::mat4* Maths::createViewMatrix(ICamera* camera)
{
	glm::mat4* matrix = new glm::mat4{ 1 };

	*matrix = glm::rotate(*matrix, glm::radians(camera->getPitch()),	glm::vec3{ 1, 0, 0 });
	*matrix = glm::rotate(*matrix, glm::radians(camera->getYaw()),	glm::vec3{ 0, 1, 0 });
	*matrix = glm::rotate(*matrix, glm::radians(camera->getRoll()),	glm::vec3{ 0, 0, 1 });

	glm::vec3 cameraPos = camera->getPosition();
	glm::vec3 negCameraPos = glm::vec3{ -cameraPos.x, -cameraPos.y, -cameraPos.z };
	*matrix = glm::translate(*matrix, negCameraPos);

	return matrix;
}