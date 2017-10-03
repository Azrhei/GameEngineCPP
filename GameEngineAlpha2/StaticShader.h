#pragma once
#include "SharedIncludes.h"
#include "ShaderProgram.h"
#include "Maths.h"
class StaticShader :
	public ShaderProgram
{
private:
	GLuint location_transformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColor;
	GLuint location_lightIntensity;

protected:
	void getAllUniformLocations() override;
	void bindAttributes() override;
public:
	StaticShader();
	~StaticShader();

	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera camera);
	void loadLight(Light light);
	
};

