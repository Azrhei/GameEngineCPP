#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include "..\Utility\common.hpp"
#include "..\Camera\Camera.h"

class Maths
{
public:
	Maths()=delete;
	~Maths();

	static mat4* createTransformationMatrix(
		vec3 translation,
		GLfloat rx,
		GLfloat ry,
		GLfloat rz,
		GLfloat scale
		);

	static mat4* createViewMatrix(Camera* camera);
};

