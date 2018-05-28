#pragma once
#ifndef ENTITY_SHADER_H
#define ENTITY_SHADER_H
#include "ShaderProgram.h"

#include "..\Utility\common.hpp"
#include "..\Utility\Maths.h"
#include "..\Camera\Camera.h"
#include <map>

using namespace CameraM;

namespace GameEngine
{
	namespace ShaderM
	{
		class EntityShader :
			public ShaderProgram
		{
		private:
			//map<string, GLuint> locations;

			GLint location_transformationMatrix = 0;
			GLint location_projectionMatrix = 0;
			GLint location_viewMatrix = 0;
			GLint location_lightPosition = 0;
			GLint location_lightColor = 0;
			GLint location_lightIntensity = 0;
			GLint location_shineDamper = 0;
			GLint location_reflectivity = 0;
			GLint location_useFakeLighting = 0;
			GLint location_skyColor = 0;

			void load();
			void loadUniforms();

			const char * VERTEX_FILE;
			const char * FRAGMENT_FILE;
		protected:
			void getAllUniformLocations() override;
			void bindAttributes() override;

		public:
			EntityShader();
			~EntityShader();
			EntityShader(const char* vertexFileName, const char* fragmentFileName);

			//GLuint StaticShader::getUniformLocation(string name);

			void loadTransformationMatrix(glm::mat4 *matrix) override;
			void loadProjectionMatrix(glm::mat4 *matrix) override;
			void loadViewMatrix(Camera& camera) override;
			void loadLight(Light& light) override;
			void loadShineVariables(GLfloat damper, GLfloat reflectivity) override;
			void loadFakeLighting(bool useFake) override;
			void loadSkyColor(vec3* color) override;
			void loadSkyColor(GLfloat r, GLfloat g, GLfloat b) override;
		};
	}
}
#endif /* ENTITY_SHADER_H */