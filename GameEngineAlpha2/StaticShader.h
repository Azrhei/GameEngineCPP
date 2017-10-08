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

	GLuint location_transformationMatrix = 0;
	GLuint location_projectionMatrix = 0;
	GLuint location_viewMatrix = 0;
	GLuint location_lightPosition = 0;
	GLuint location_lightColor = 0;
	GLuint location_lightIntensity = 0;
	GLuint location_shineDamper = 0;
	GLuint location_reflectivity = 0;


protected:
	void load();
	void getAllUniformLocations() override;
	void bindAttributes() override;

public:
	StaticShader();
	~StaticShader();
	StaticShader(string vertexFileName, string fragmentFileName);

	//GLuint StaticShader::getUniformLocation(string name);
	void loadTransformationMatrix(glm::mat4 matrix) override;
	void loadProjectionMatrix(glm::mat4 matrix) override;
	void loadViewMatrix(Camera* camera )override;
	void loadLight(Light* light) override;
	void loadShineVariables(GLfloat damper, GLfloat reflectivity) override;
};

