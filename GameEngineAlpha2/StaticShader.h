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

	GLuint location_transformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColor;
	GLuint location_lightIntensity;
	GLuint location_shineDamper;
	GLuint location_reflectivity;


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
	void loadViewMatrix(Camera camera )override;
	void loadLight(Light light) override;
	void loadShineVariables(GLfloat damper, GLfloat reflectivity) override;
};

