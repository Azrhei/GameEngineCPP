#pragma once
#include "SharedIncludes.h"
#include "Light.h"
#include "Camera.h"

class ShaderProgram
{
private:
	GLuint programId;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	string vertexFileName;
	string fragmentFileName;

public:
	ShaderProgram() = delete;
	ShaderProgram(string vertexFile, string fragmentFile);
	~ShaderProgram();

	void start();
	void stop();
	void cleanUp();

	virtual void loadTransformationMatrix(glm::mat4 matrix) = 0;
	virtual void loadProjectionMatrix(glm::mat4 matrix) = 0;
	virtual void loadViewMatrix(Camera camera) = 0;
	virtual void loadLight(Light light) = 0;
	virtual void loadShineVariables(GLfloat damper, GLfloat reflectivity) = 0;

protected:
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;

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
	void loadVector(GLuint location, glm::vec3 value);
	void loadMatrix(GLuint location, glm::mat4 value);
};

