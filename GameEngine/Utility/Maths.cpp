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
	mat4* matrix=new mat4 {1};

	*matrix = translate(*matrix, translation);
	*matrix = rotate(*matrix, radians(rx), vec3{ 1, 0, 0 });
	*matrix = rotate(*matrix, radians(ry), vec3{ 0, 1, 0 });
	*matrix = rotate(*matrix, radians(rz), vec3{ 0, 0, 1 });
	*matrix = glm::scale(*matrix, vec3(scale, scale, scale));

	return matrix;
}

mat4* Maths::createViewMatrix(Camera* camera)
{
	mat4* matrix = new mat4{ 1 };

	*matrix = rotate(*matrix, radians(camera->pitch()),	vec3{ 1, 0, 0 });
	*matrix = rotate(*matrix, radians(camera->yaw()),	vec3{ 0, 1, 0 });
	*matrix = rotate(*matrix, radians(camera->roll()),	vec3{ 0, 0, 1 });

	vec3 cameraPos = camera->position();
	vec3 negCameraPos = vec3{ -cameraPos.x, -cameraPos.y, -cameraPos.z };
	*matrix = translate(*matrix, negCameraPos);

	return matrix;
}