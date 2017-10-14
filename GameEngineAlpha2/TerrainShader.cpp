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
	wcout << L"Loading Terrain shaders..." << endl;
	generateShaderProgram();
	bindAttributes();
	buildShaderProgram();
	getAllUniformLocations();
	wcout << L"Terrain shaders loaded" << endl;
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
	location_lightColour = getUniformLocation("lightColour");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");

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
	loadVector(location_lightPosition, light->getPosition());
	loadVector(location_lightColour, light->getColor());
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
