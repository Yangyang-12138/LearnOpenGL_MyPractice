#include "shader_m.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:" << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	progID = glCreateProgram();
	glAttachShader(progID, vertex);
	glAttachShader(progID, fragment);
	glLinkProgram(progID);
	checkCompileErrors(progID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(progID);
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(progID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(progID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(progID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, glm::vec2 value)
{
	glUniform2fv(glGetUniformLocation(progID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float v0, float v1)
{
	glUniform2f(glGetUniformLocation(progID, name.c_str()), v0, v1);
}

void Shader::setVec3(const std::string& name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(progID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(progID, name.c_str()), v0, v1, v2);
}

void Shader::setVec4(const std::string& name, glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(progID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(progID, name.c_str()), v0, v1, v2, v3);
}

void Shader::setMat2(const std::string& name, glm::mat2 value)
{
	glUniformMatrix2fv(glGetUniformLocation(progID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string& name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(progID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(progID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::checkCompileErrors(GLuint shaderID, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type == "PROGRAM")
	{
		glGetProgramiv(progID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(progID, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type:" << type << std::endl << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(progID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(progID, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type:" << type << std::endl << infoLog << std::endl;
		}
	}
}