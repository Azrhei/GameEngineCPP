#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "..\Utility\common.hpp"
#include "..\Light\Light.h"
#include "..\Camera\Camera.h"

#include <vector>
#include <unordered_map>
#include <string>

namespace GameEngine
{
	using namespace CameraM;

	namespace ShaderM
	{
		class ShaderProgram
		{
		private:
			GLuint _programId;
			GLuint _vertexShaderID;
			GLuint _fragmentShaderID;
			const char* _vertexFileName;
			const char* _fragmentFileName;

		public:
			ShaderProgram() = delete;
			ShaderProgram(const char* vertexFile, const char* fragmentFile);
			~ShaderProgram();

			void start();
			void stop();
			void cleanUp();

			virtual void loadTransformationMatrix(mat4 matrix) = 0;
			virtual void loadProjectionMatrix(mat4 matrix) = 0;
			virtual void loadViewMatrix(Camera& camera) = 0;
			virtual void loadLight(Light& light) = 0;
			virtual void loadShineVariables(GLfloat damper, GLfloat reflectivity) = 0;
			virtual void loadFakeLighting(bool useFake) = 0;
			virtual void loadSkyColor(vec3* color) = 0;
			virtual void loadSkyColor(GLfloat r, GLfloat g, GLfloat b) = 0;

		protected:
			virtual void bindAttributes() = 0;
			virtual void getAllUniformLocations() = 0;

			void addUniformName(string name);

			vector<string>* _locationNames;
			unordered_map<string, GLint>* _locations;

			void generateShaderProgram();
			void buildShaderProgram();

			//  Reada and process a shader file.
			static GLuint loadShader(string file, GLuint type);
			static string readFile(const char *filePath);

			// Handle sending data to shader
			GLuint getUniformLocation(string uniformName);
			void bindAttribute(GLuint attribute, string variableName);

			// Load various values into the GPU shader 
			void loadFloat(GLuint location, GLfloat value);
			void loadInt(GLuint location, GLint value);
			void loadBool(GLuint location, GLboolean value);
			void loadVector(GLuint location, vec3 value);
			void loadVector(GLuint location, vec3* value);
			void loadMatrix(GLuint location, mat4 value);
			//void loadMatrix(GLuint location, mat4* value);
		};
	}
}
#endif /* SHADER_PROGRAM_H */