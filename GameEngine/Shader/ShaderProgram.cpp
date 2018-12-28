#include "ShaderProgram.h"
#include "StaticShader.h"
#include "..\Debugger.h"

namespace GameEngine
{
	using namespace Debugger;
	namespace ShaderM
	{
		ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
			: _vertexFileName(vertexFile), _fragmentFileName(fragmentFile), _locationNames(new vector<string>), _locations(new unordered_map<string, GLint>)
		{

		}

		void ShaderProgram::generateShaderProgram()
		{
			_vertexShaderID = loadShader(_vertexFileName, GL_VERTEX_SHADER);
			_fragmentShaderID = loadShader(_fragmentFileName, GL_FRAGMENT_SHADER);
			_programId = glCreateProgram();
			glAttachShader(_programId, _vertexShaderID);
			glAttachShader(_programId, _fragmentShaderID);
		}

		void ShaderProgram::buildShaderProgram()
		{
			glLinkProgram(_programId);
			glValidateProgram(_programId);
		}


		ShaderProgram::~ShaderProgram()
		{
		}


		GLuint ShaderProgram::loadShader(string file, GLenum type)
		{

			GLuint shaderId = glCreateShader(type);

			string fsrc = readFile((string("res/") + file).c_str());
			const char * src = fsrc.c_str();

			GLint result = GL_FALSE;
			int logLength;

			// Compile shader
			std::cout << "Compiling shader." << nl;
			glShaderSource(shaderId, 1, &src, NULL);
			glCompileShader(shaderId);

			// Check vertex shader
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> shaderError((logLength > 1) ? logLength : 1);
			glGetShaderInfoLog(shaderId, logLength, NULL, &shaderError[0]);
			std::cout << &shaderError[0] << nl;

			return shaderId;
		}

		void ShaderProgram::start()
		{
			glUseProgram(_programId);
		}

		void ShaderProgram::stop()
		{
			glUseProgram(0);
		}

		void ShaderProgram::cleanUp()
		{
			glDetachShader(_programId, _vertexShaderID);
			glDetachShader(_programId, _fragmentShaderID);
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);
			glDeleteProgram(_programId);
		}

		void ShaderProgram::bindAttribute(GLuint attribute, string variableName)
		{
			glBindAttribLocation(_programId, attribute, variableName.c_str());
		}

		string ShaderProgram::readFile(const char *filePath) {
			string content;
			ifstream fileStream{ filePath, ios::in };

			if (!fileStream.is_open()) {
				wcerr << L"Could not read file " << filePath << L". File does not exist." << nl;
				return "";
			}

			string line = "";
			while (!fileStream.eof()) {
				getline(fileStream, line);
				content.append(line + "\n");
			}

			fileStream.close();
			return content;
		}

		GLuint ShaderProgram::getUniformLocation(string uniformName)
		{
			return glGetUniformLocation(_programId, uniformName.c_str());
		}

		void ShaderProgram::loadFloat(GLuint location, GLfloat value)
		{
			glUniform1f(location, value);
		}

		void ShaderProgram::loadInt(GLuint location, GLint value)
		{
			glUniform1i(location, value);
		}
		void ShaderProgram::loadBool(GLuint location, GLboolean value)
		{
			glUniform1i(location, (value) ? GL_TRUE : GL_FALSE);
		}

		void ShaderProgram::loadVector(GLuint location, glm::vec3 value)
		{
			glUniform3f(location, value.x, value.y, value.z);
		}

		void ShaderProgram::loadVector(GLuint location, glm::vec3* value)
		{
			glUniform3f(location, value->x, value->y, value->z);
		}

		void ShaderProgram::loadMatrix(GLuint location, glm::mat4 value)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, &(value)[0][0]);
		}

		void ShaderProgram::addUniformName(string name)
		{
			_locationNames->push_back(name);
		}
	}
}