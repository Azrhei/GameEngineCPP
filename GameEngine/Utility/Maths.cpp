#include "Maths.h"
#include "..\Camera\Camera.h"

using namespace GameEngine;
using namespace CameraM;

namespace GameEngine
{
	namespace UtilityM
	{
		float randFloat(float min, float max)
		{
			return min + ((float)rand() / (float)RAND_MAX) * (max - min);
		}

		Maths::~Maths()
		{
		}

		mat4* Maths::createTransformationMatrix(
			vec3 translation,
			GLfloat rx,
			GLfloat ry,
			GLfloat rz,
			GLfloat scale
		)
		{
			mat4* matrix = new mat4{ 1 };

			*matrix = translate(*matrix, translation);
			*matrix = rotate(*matrix, radians(rx), vec3{ 1, 0, 0 });
			*matrix = rotate(*matrix, radians(ry), vec3{ 0, 1, 0 });
			*matrix = rotate(*matrix, radians(rz), vec3{ 0, 0, 1 });
			*matrix = glm::scale(*matrix, vec3(scale, scale, scale));

			return matrix;
		}

		mat4* Maths::createViewMatrix(Camera& camera)
		{
			mat4* matrix = new mat4{ 1 };

			*matrix = rotate(*matrix, radians(camera.pitch()), vec3{ 1, 0, 0 });
			*matrix = rotate(*matrix, radians(camera.yaw()), vec3{ 0, 1, 0 });
			*matrix = rotate(*matrix, radians(camera.roll()), vec3{ 0, 0, 1 });

			auto & cameraPos = camera.position();
			auto & negCameraPos = vec3{ -cameraPos.x, -cameraPos.y, -cameraPos.z };
			*matrix = translate(*matrix, negCameraPos);

			return matrix;
		}


		GLfloat Maths::barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos)
		{
			float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
			float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
			float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
			float l3 = 1.0f - l1 - l2;
			return l1 * p1.y + l2 * p2.y + l3 * p3.y;
		}
	}
}