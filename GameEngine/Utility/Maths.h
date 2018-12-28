#pragma once

#ifndef MATHS_H
#define MATHS_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include "..\Utility\common.hpp"
#include "..\Camera\Camera.h"

using namespace GameEngine;
using namespace CameraM;

namespace GameEngine
{
	namespace UtilityM
	{
		float randFloat(float min, float max);

		class Maths
		{
		public:
			Maths() {}
			Maths(const Maths&) = delete;
			void operator=(Maths&) = delete;
			~Maths();

			static Maths& getInstance()
			{
				static Maths _inst_;
				return _inst_;
			}

			static mat4 createTransformationMatrix(
				vec3 translation,
				GLfloat rx,
				GLfloat ry,
				GLfloat rz,
				GLfloat scale
			);
			static GLfloat barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos);
			static mat4 createViewMatrix(Camera& camera);
		};
		static Maths& maths = Maths::getInstance();
	}
}
#endif /* MATHS_H */