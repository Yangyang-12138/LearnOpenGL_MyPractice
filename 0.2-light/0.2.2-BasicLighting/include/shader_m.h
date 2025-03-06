#ifndef SHADER_M_H
#define SHADER_M_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int progID;

	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name, glm::vec2 value);
	void setVec2(const std::string& name, float v0, float v1);
	void setVec3(const std::string& name, glm::vec3 value);
	void setVec3(const std::string& name, float v0, float v1, float v2);
	void setVec4(const std::string& name, glm::vec4 value);
	void setVec4(const std::string& name, float v0, float v1, float v2, float v3);
	void setMat2(const std::string& name, glm::mat2 value);
	void setMat3(const std::string& name, glm::mat3 value);
	void setMat4(const std::string& name, glm::mat4 value);

private:
	void checkCompileErrors(GLuint shaderID, std::string type);
};

#endif // !SHADER_M_H
