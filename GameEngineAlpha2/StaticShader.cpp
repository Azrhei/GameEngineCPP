#include "StaticShader.h"
#include "Camera.h"

StaticShader::StaticShader(string vertexShaderFile, string fragmentShaderFile)
: ShaderProgram(vertexShaderFile, fragmentShaderFile)
{

}

StaticShader::StaticShader()
	: 
	ShaderProgram("vertexShader.glsl", "fragmentShader.glsl")
{
	wcout << L"Loading shaders" << endl;
	load();
}

void StaticShader::load()
{
	generateShaderProgram();
	bindAttributes();
	buildShaderProgram();
	getAllUniformLocations();
}

StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	wcout << L"Calling correct bindAttributes() method" << endl;
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "textureCoords");
	this->bindAttribute(2, "normals");
}

//GLuint StaticShader::getUniformLocation(string name)
//{
//	return locations[name];
//}

void StaticShader::getAllUniformLocations()
{
	wcout << L"Calling correct getAllUniformLocations" << endl;
	location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	location_viewMatrix = this->getUniformLocation("viewMatrix");
	location_lightPosition = this->getUniformLocation("lightPosition");
	location_lightColor = this->getUniformLocation("lightColor");
	location_lightIntensity = this->getUniformLocation("lightIntensity");
	location_shineDamper = this->getUniformLocation("shineDamper");
	location_reflectivity = this->getUniformLocation("reflectivity");

	//locations["transformationMatrix"] = this->getUniformLocation("transformationMatrix");
	//locations["projectionMatrix"] = this->getUniformLocation("projectionMatrix");
	//locations["viewMatrix"] = this->getUniformLocation("viewMatrix");
	//locations["lightPosition"] = this->getUniformLocation("lightPosition");
	//locations["lightColor"] = this->getUniformLocation("lightColor");
	//locations["lightIntensity"] = this->getUniformLocation("lightIntensity");
	//locations["shineDamper"] = this->getUniformLocation("shineDamper");
	//locations["reflectivity"] = this->getUniformLocation("reflectivity");


}

void StaticShader::loadProjectionMatrix(glm::mat4 projection)
{
	//this->loadMatrix(locations["projectionMatrix"], projection);
	this->loadMatrix(location_projectionMatrix, projection);
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera* camera)
{
	this->loadMatrix(location_viewMatrix, Maths::createViewMatrix(camera));
}

void StaticShader::loadLight(Light* light)
{
	this->loadVector(location_lightPosition, light->getPosition());
	this->loadVector(location_lightColor, light->getColor());
	this->loadFloat(location_lightIntensity, light->getIntensity());
}

void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	this->loadFloat(location_shineDamper, damper);
	this->loadFloat(location_reflectivity, reflectivity);
}