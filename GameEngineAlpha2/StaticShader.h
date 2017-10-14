#pragma once
#include "SharedIncludes.h"
#include "ShaderProgram.h"
#include "Maths.h"
#include <map>

class StaticShader :
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
	void load();

	const char * VERTEX_FILE;
	const char * FRAGMENT_FILE;
protected:
	void getAllUniformLocations() override;
	void bindAttributes() override;

public:
	StaticShader();
	~StaticShader();
	StaticShader(const char* vertexFileName, const char* fragmentFileName);

	//GLuint StaticShader::getUniformLocation(string name);
	void loadTransformationMatrix(glm::mat4 *matrix) override;
	void loadProjectionMatrix(glm::mat4 *matrix) override;
	void loadViewMatrix(ICamera* camera ) override;
	void loadLight(Light* light) override;
	void loadShineVariables(GLfloat damper, GLfloat reflectivity) override;
};