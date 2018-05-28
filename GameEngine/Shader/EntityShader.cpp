#include "EntityShader.h"
#include "..\Camera\Camera.h"
#include "..\Utility\Maths.h"
#include "ShaderProgram.h"

using namespace CameraM;
using namespace UtilityM;

namespace GameEngine
{
	namespace ShaderM
	{
		EntityShader::EntityShader(const char* vertexShaderFile, const char* fragmentShaderFile)
			: ShaderProgram(vertexShaderFile, fragmentShaderFile)
		{
			loadUniforms(); // must be done before load()
			load();
		}

		EntityShader::EntityShader()
			:VERTEX_FILE("entityVertexShader.glsl"), FRAGMENT_FILE("entityFragmentShader.glsl"), ShaderProgram("entityVertexShader.glsl", "entityFragmentShader.glsl")
		{
			loadUniforms(); // must be done before load()
			load();
		}

		void EntityShader::loadUniforms()
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
		}

		EntityShader::~EntityShader()
		{
		}

		void EntityShader::load()
		{
			wcout << L"Loading Entity shaders" << nl;
			generateShaderProgram();
			bindAttributes();
			buildShaderProgram();
			getAllUniformLocations();
			wcout << L"Entity shaders loaded" << nl;
		}

		void EntityShader::bindAttributes()
		{
			bindAttribute(0, "position");
			bindAttribute(1, "textureCoords");
			bindAttribute(2, "normal");
		}

		//GLuint StaticShader::getUniformLocation(string name)
		//{
		//	return locations[name];
		//}

		void EntityShader::loadFakeLighting(bool useFake)
		{
			loadBool(location_useFakeLighting, useFake);
		}

		void EntityShader::getAllUniformLocations()
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

		void EntityShader::loadSkyColor(vec3* color)
		{
			loadVector(_locations->find("skyColor")->second, color);
			loadVector(location_skyColor, color);
		}

		void EntityShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
		{
			loadVector(location_skyColor, vec3{ r, g, b });
		}

		void EntityShader::loadProjectionMatrix(mat4* projection)
		{
			//this->loadMatrix(locations["projectionMatrix"], projection);
			loadMatrix(location_projectionMatrix, projection);
		}

		void EntityShader::loadTransformationMatrix(mat4* matrix)
		{
			loadMatrix(location_transformationMatrix, matrix);
		}

		void EntityShader::loadViewMatrix(Camera& camera)
		{
			loadMatrix(location_viewMatrix, maths.createViewMatrix(camera));
		}

		void EntityShader::loadLight(Light& light)
		{
			loadVector(location_lightPosition, light.position());
			loadVector(location_lightColor, light.color());
			loadFloat(location_lightIntensity, light.intensity());
		}

		void EntityShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
		{
			loadFloat(location_shineDamper, damper);
			loadFloat(location_reflectivity, reflectivity);
		}
	}
}