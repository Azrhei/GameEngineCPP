#pragma once

#include "SharedIncludes.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include "Camera.h"

class Maths
{
public:
	Maths()=delete;
	~Maths();

	static glm::mat4 createTransformationMatrix(
		glm::fvec3 translation,
		GLfloat rx,
		GLfloat ry,
		GLfloat rz,
		GLfloat scale
		);

	static glm::mat4 createViewMatrix(Camera camera);
};

