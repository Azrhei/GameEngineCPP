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
	void getAllUniformLocations() override;
	void bindAttributes() override;

public:
	StaticShader(string vertexFileName, string fragmentFileName);
	StaticShader();
	~StaticShader();
	//GLuint StaticShader::getUniformLocation(string name);
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera camera);
	void loadLight(Light light);
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
};

