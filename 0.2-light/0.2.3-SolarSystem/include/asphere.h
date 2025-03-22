#ifndef ASPHERE_H
#define ASPHERE_H

#include <stdio.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct SphereVertex {
    glm::vec3 vertexPos;
    glm::vec3 normal;
    glm::vec2 texturePos;
};

class aSphere
{
public:
	aSphere();
	~aSphere();

    Shader* shader;

    void setRadius(float r);
    void setTexture(const char* texPath);
    void setSegments(unsigned int nLon = 8, unsigned int nLat = 8);
    void setShader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void drawMe();

private:
    const char* vShaderPath;
    const char* fShaderPath;
    const char* texturePath;
    unsigned int nLonSegments;
    unsigned int nLatSegments;
    float radius;

    std::vector<glm::vec3> vertexPos;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> texCoord;
    std::vector<unsigned int > indices;

    void genVertices(unsigned int nLon, unsigned int nLat, float r);
    void genIndices(unsigned int nLon, unsigned int nLat);

};

#endif