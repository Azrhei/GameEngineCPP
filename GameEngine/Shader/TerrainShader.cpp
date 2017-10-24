#include "TerrainShader.h"

TerrainShader::~TerrainShader()
{
}

TerrainShader::TerrainShader(const char * vertexShaderFile, const char* fragmentShaderFile)
: ShaderProgram(vertexShaderFile, fragmentShaderFile)
{
	load();
}

TerrainShader::TerrainShader()
:VERTEX_FILE("terrainVertexShader.glsl"), FRAGMENT_FILE("terrainFragmentShader.glsl"), ShaderProgram("terrainVertexShader.glsl", "terrainFragmentShader.glsl")
{
	load();
}

void TerrainShader::load()
{
	wcout << L"Loading Terrain shaders..." << nl;
	generateShaderProgram();
	bindAttributes();
	buildShaderProgram();
	getAllUniformLocations();
	wcout << L"Terrain shaders loaded" << nl;
}

void TerrainShader::bindAttributes() 
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoordinates");
	bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations() 
{
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_lightIntensity = getUniformLocation("lightIntensity");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_useFakeLighting = getUniformLocation("useFakeLighting");
	location_skyColor = getUniformLocation("skyColor");
	location_backgroundTexture = getUniformLocation("backgroundTexture");
	location_rTexture = getUniformLocation("rTexture");
	location_gTexture = getUniformLocation("gTexture");
	location_bTexture = getUniformLocation("bTexture");
	location_blendMap = getUniformLocation("blendMap");
}

void TerrainShader::connectTextureUnits()
{
	loadInt(location_backgroundTexture, 0);
	loadInt(location_rTexture, 1);
	loadInt(location_gTexture, 2);
	loadInt(location_bTexture, 3);
	loadInt(location_blendMap, 4);

}

void TerrainShader::loadSkyColor(vec3* color)
{
	loadVector(location_skyColor, color);
}

void TerrainShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
	loadVector(location_skyColor, vec3{ r, g, b });
}
void TerrainShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadTransformationMatrix(glm::mat4* matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadLight(Light* light)
{
	loadVector(location_lightPosition, light->position());
	loadVector(location_lightColor, light->color());
}

void TerrainShader::loadViewMatrix(ICamera* camera)
{
	glm::mat4* viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4* projection)
{
	loadMatrix(location_projectionMatrix, projection);
}

void TerrainShader::loadFakeLighting(bool useFake)
{
	loadBool(location_useFakeLighting, useFake);
}