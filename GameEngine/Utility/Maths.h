#pragma once

#ifndef MATHS_H
#define MATHS_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include "..\Utility\SharedIncludes.h"
#include "..\Camera\Camera.h"

namespace UtilityM
{
	class Maths
	{
	public:
		Maths() = delete;
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
}
#endif /* MATHS_H */