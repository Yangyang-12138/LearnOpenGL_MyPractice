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
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void set4Float(const std::string &name, float v0, float v1, float v2, float v3) const;
    void set2Vec(const std::string &name, float v0, float v1) const;
    void set2Vec(const std::string &name, const glm::vec2 &value) const;
    void set3Vec(const std::string &name, float v0, float v1, float v2) const;
    void set3Vec(const std::string &name, const glm::vec3 &value) const;
    void set4Vec(const std::string &name, float v0, float v1, float v2, float v3) const;
    void set4Vec(const std::string &name, const glm::vec4 &value) const;
    void set2Mat(const std::string &name, const glm::mat2 &value) const;
    void set3Mat(const std::string &name, const glm::mat3 &value) const;
    void set4Mat(const std::string &name, const glm::mat4 &value) const;

private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif // SHADER_M_H