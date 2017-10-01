#pragma once
#include "SharedIncludes.h"

class ShaderProgram
{
private:
	GLuint programId;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	string vertexFileName;
	string fragmentFileName;

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
	void load();
	GLuint getUniformLocation(string uniformName);
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;
	void bindAttribute(GLuint attribute, string variableName);
	void loadFloat(GLuint location, GLfloat value);
	void loadInt(GLuint location, GLint value);
	void loadBool(GLuint location, GLboolean value);

	void loadVector(GLuint location, glm::vec3 value);
	void loadMatrix(GLuint location, glm::mat4 value);
};

