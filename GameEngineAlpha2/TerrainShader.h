#pragma once
#include "SharedIncludes.h"
#include "ShaderProgram.h"
#include "Maths.h"

class TerrainShader : public ShaderProgram
{
private:
	GLuint location_transformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColour;
	GLuint location_shineDamper;
	GLuint location_reflectivity;

	const char * VERTEX_FILE;
	const char * FRAGMENT_FILE;
	void load();
public:
	TerrainShader();
	~TerrainShader();
	TerrainShader(const char * vertexShaderFile, const char * fragmentShaderFile);
	void bindAttributes();
	void getAllUniformLocations();
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadTransformationMatrix(glm::mat4* matrix);
	void loadLight(Light* light);
	void loadViewMatrix(ICamera* camera);
	void loadProjectionMatrix(glm::mat4* projection);
};