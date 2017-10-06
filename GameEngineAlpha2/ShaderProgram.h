#pragma once
#include "SharedIncludes.h"
#include "Light.h"

class ShaderProgram
{
private:

	static GLuint loadShader(string file, GLuint type);
	static string readFile(const char *filePath);

public:
	ShaderProgram() = delete;
	ShaderProgram(string vertexFile, string fragmentFile);
	~ShaderProgram();

	void start();
	void stop();
	void cleanUp();

protected:
	GLuint programId;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	string vertexFileName;
	string fragmentFileName;
	void load();
	GLuint getUniformLocation(string uniformName);
	virtual void bindAttributes();
	virtual void getAllUniformLocations();
	void bindAttribute(GLuint attribute, string variableName);
	void loadFloat(GLuint location, GLfloat value);
	void loadInt(GLuint location, GLint value);
	void loadBool(GLuint location, GLboolean value);

	void loadVector(GLuint location, glm::vec3 value);
	void loadMatrix(GLuint location, glm::mat4 value);
};

