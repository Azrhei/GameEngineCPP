#include "ShaderProgram.h"
#include "StaticShader.h"
#include <vector>

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile)
:
vertexFileName(vertexFile), fragmentFileName(fragmentFile)
{
	this->load();
}

void ShaderProgram::load()
{
	vertexShaderID = loadShader(vertexFileName, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFileName, GL_FRAGMENT_SHADER);
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderID);
	glAttachShader(programId, fragmentShaderID);
	this->bindAttributes();
	glLinkProgram(programId);
	glValidateProgram(programId);
	this->getAllUniformLocations();
}
 
ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::bindAttributes()
{
	wcout << L"Calling wrong bindAttributes() method" << endl;
}

GLuint ShaderProgram::loadShader(string file, GLuint type)
{
	GLuint shaderId = glCreateShader(type);

	string fsrc = readFile(file.c_str());
	const char * src = fsrc.c_str();

	GLint result = GL_FALSE;
	int logLength;

	// Compile shader
	std::cout << "Compiling shader." << std::endl;
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);

	// Check vertex shader
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> shaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shaderId, logLength, NULL, &shaderError[0]);
	std::cout << &shaderError[0] << std::endl;
	
	return shaderId;
}

void ShaderProgram::start()
{
	glUseProgram(programId);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	stop();
	glDetachShader(programId, vertexShaderID);
	glDetachShader(programId, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programId);
}

void ShaderProgram::bindAttribute(GLuint attribute, string variableName)
{
	glBindAttribLocation(programId, attribute, variableName.c_str());
}

string ShaderProgram::readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint ShaderProgram::getUniformLocation(string uniformName)
{
	return glGetUniformLocation(programId, uniformName.c_str());
}

void ShaderProgram::getAllUniformLocations()
{
	wcout << L"Calling wrong getAllUniformLocations() method" << endl;
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
	glUniform1i(location, (value) ? GL_TRUE : GL_FALSE );
}

void ShaderProgram::loadVector(GLuint location, glm::vec3 value)
{
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::loadMatrix(GLuint location, glm::mat4 value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}