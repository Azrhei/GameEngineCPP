#pragma once
#include "..\Utility\common.hpp"
#include "..\Shader\ShaderProgram.h"
#include "..\Utility\Maths.h"
#include "..\Camera\ICamera.h"
#include "..\Light\Light.h"

class TerrainShader : public ShaderProgram
{
private:
	GLint location_transformationMatrix = 0;
	GLint location_projectionMatrix = 0;
	GLint location_viewMatrix = 0;
	GLint location_lightPosition = 0;
	GLint location_lightColor = 0;
	GLint location_lightIntensity = 0;
	GLint location_shineDamper = 0;
	GLint location_reflectivity = 0;
	GLint location_useFakeLighting = 0;
	GLint location_skyColor = 0;
	GLint location_backgroundTexture = 0;
	GLint location_rTexture = 0;
	GLint location_gTexture = 0;
	GLint location_bTexture = 0;
	GLint location_blendMap = 0;
	const char * VERTEX_FILE;
	const char * FRAGMENT_FILE;
	void load();
	void loadUniforms();

public:
	TerrainShader();
	~TerrainShader();
	TerrainShader(const char * vertexShaderFile, const char * fragmentShaderFile);
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadTransformationMatrix(mat4 *matrix) override;
	void loadProjectionMatrix(mat4 *matrix) override;
	void loadViewMatrix(Camera* camera) override;
	void loadLight(Light& light) override;
	void loadShineVariables(GLfloat damper, GLfloat reflectivity) override;
	void loadFakeLighting(bool useFake) override;
	void loadSkyColor(vec3* color) override;
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b) override;
};