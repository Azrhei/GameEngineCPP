#include "StaticShader.h"
#include "Camera.h"

StaticShader::StaticShader(const char* vertexShaderFile, const char* fragmentShaderFile)
: ShaderProgram(vertexShaderFile, fragmentShaderFile)
{
	load();
}

StaticShader::StaticShader()
:VERTEX_FILE("vertexShader.glsl"), FRAGMENT_FILE("fragmentShader.glsl"), ShaderProgram("vertexShader.glsl", "fragmentShader.glsl")
{
	load();
}

StaticShader::~StaticShader()
{
}

void StaticShader::load()
{
	wcout << L"Loading Entity shaders" << endl;
	generateShaderProgram();
	bindAttributes();
	buildShaderProgram();
	getAllUniformLocations();
	wcout << L"Entity shaders loaded" << endl;
}

void StaticShader::bindAttributes()
{
	wcout << L"Calling correct bindAttributes() method" << endl;
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normals");
}

//GLuint StaticShader::getUniformLocation(string name)
//{
//	return locations[name];
//}

void StaticShader::getAllUniformLocations()
{
	wcout << L"Calling correct getAllUniformLocations" << endl;
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_lightIntensity = getUniformLocation("lightIntensity");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	//locations["transformationMatrix"] = this->getUniformLocation("transformationMatrix");
	//locations["projectionMatrix"] = this->getUniformLocation("projectionMatrix");
	//locations["viewMatrix"] = this->getUniformLocation("viewMatrix");
	//locations["lightPosition"] = this->getUniformLocation("lightPosition");
	//locations["lightColor"] = this->getUniformLocation("lightColor");
	//locations["lightIntensity"] = this->getUniformLocation("lightIntensity");
	//locations["shineDamper"] = this->getUniformLocation("shineDamper");
	//locations["reflectivity"] = this->getUniformLocation("reflectivity");


}

void StaticShader::loadProjectionMatrix(glm::mat4* projection)
{
	//this->loadMatrix(locations["projectionMatrix"], projection);
	this->loadMatrix(location_projectionMatrix, projection);
}

void StaticShader::loadTransformationMatrix(glm::mat4* matrix)
{
	this->loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadViewMatrix(ICamera* camera)
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