#pragma once
#include "SharedIncludes.h"
#include "Light.h"
#include "Camera.h"

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

	virtual void loadTransformationMatrix(glm::mat4* matrix) = 0;
	virtual void loadProjectionMatrix(glm::mat4* matrix) = 0;
	virtual void loadViewMatrix(ICamera* camera) = 0;
	virtual void loadLight(Light* light) = 0;
	virtual void loadShineVariables(GLfloat damper, GLfloat reflectivity) = 0;
	virtual void loadFakeLighting(bool useFake) = 0;
	virtual void loadSkyColor(vec3* color) = 0;
	virtual void loadSkyColor(GLfloat r, GLfloat g, GLfloat b) = 0;


protected:
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;

	void generateShaderProgram();
	void buildShaderProgram();

	//  Reada and process a shader file.
	static GLuint loadShader(const char* file, GLuint type);
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
	void loadMatrix(GLuint location, mat4* value);
};

