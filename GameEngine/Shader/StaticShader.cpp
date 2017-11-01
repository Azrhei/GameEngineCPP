#include "StaticShader.h"
#include "..\Camera\Camera.h"

namespace ShaderM
{

	StaticShader::StaticShader(const char* vertexShaderFile, const char* fragmentShaderFile)
		: ShaderProgram(vertexShaderFile, fragmentShaderFile)
	{
		load();
	}

	StaticShader::StaticShader()
		: VERTEX_FILE("vertexShader.glsl"), FRAGMENT_FILE("fragmentShader.glsl"), ShaderProgram("vertexShader.glsl", "fragmentShader.glsl")
	{
		addUniformName("transformationMatrix");
		addUniformName("projectionMatrix?");
		addUniformName("viewMatrix");
		addUniformName("lightPosition");
		addUniformName("lightColor");
		addUniformName("lightIntensity");
		addUniformName("shineDamper");
		addUniformName("reflectivity");
		addUniformName("useFakeLighting");
		addUniformName("skyColor");
		load();
	}

	StaticShader::~StaticShader()
	{
	}

	void StaticShader::load()
	{
		wcout << L"Loading Entity shaders" << nl;
		generateShaderProgram();
		bindAttributes();
		buildShaderProgram();
		getAllUniformLocations();
		wcout << L"Entity shaders loaded" << nl;
	}

	void StaticShader::bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
		bindAttribute(2, "normal");
	}

	//GLuint StaticShader::getUniformLocation(string name)
	//{
	//	return locations[name];
	//}

	void StaticShader::loadFakeLighting(bool useFake)
	{
		loadBool(location_useFakeLighting, useFake);
	}

	void StaticShader::getAllUniformLocations()
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

		for (string n : *_locationNames)
		{
			_locations->insert(make_pair(n, getUniformLocation(n)));
		}


	}

	void StaticShader::loadSkyColor(vec3* color)
	{
		loadVector(_locations->find("skyColor")->second, color);
		loadVector(location_skyColor, color);
	}

	void StaticShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
	{
		loadVector(location_skyColor, vec3{ r, g, b });
	}

	void StaticShader::loadProjectionMatrix(mat4* projection)
	{
		//this->loadMatrix(locations["projectionMatrix"], projection);
		loadMatrix(location_projectionMatrix, projection);
	}

	void StaticShader::loadTransformationMatrix(mat4* matrix)
	{
		loadMatrix(location_transformationMatrix, matrix);
	}

	void StaticShader::loadViewMatrix(ICamera* camera)
	{
		loadMatrix(location_viewMatrix, UtilityM::Maths::createViewMatrix(camera));
	}

	void StaticShader::loadLight(Light* light)
	{
		loadVector(location_lightPosition, light->position());
		loadVector(location_lightColor, light->color());
		loadFloat(location_lightIntensity, light->intensity());
	}

	void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
	{
		loadFloat(location_shineDamper, damper);
		loadFloat(location_reflectivity, reflectivity);
	}
}