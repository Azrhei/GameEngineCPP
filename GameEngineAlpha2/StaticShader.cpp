#include "StaticShader.h"
#include "Camera.h"

StaticShader::StaticShader()
	: 
	ShaderProgram("vertexShader.glsl", "fragmentShader.glsl")
{
	wcout << L"Loading shaders" << endl;
	this->load();
}

StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	wcout << L"Calling correct bindAttributes() method" << endl;
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "textureCoords");
}

void StaticShader::getAllUniformLocations()
{
	wcout << L"Calling correct getAllUniformLocations" << endl;
	location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	location_viewMatrix = this->getUniformLocation("viewMatrix");
}

void StaticShader::loadProjectionMatrix(glm::mat4 projection)
{
	this->loadMatrix(location_projectionMatrix, projection);
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera camera)
{
	this->loadMatrix(location_viewMatrix, Maths::createViewMatrix(camera));
}