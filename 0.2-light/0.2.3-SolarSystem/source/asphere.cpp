#include "asphere.h"

aSphere::aSphere()
    :shader(NULL),
    radius(1.0f),
    vShaderPath(NULL),
    fShaderPath(NULL),
    texturePath(NULL),
    nLonSegments(8),
    nLatSegments(8)
{
}

aSphere::~aSphere()
{
}

void aSphere::setRadius(float r)
{
    if (r > 0)
    {
        radius = r;
    }
    else
    {
        std::cout << "Failed to set radius" << std::endl;
    }
}

void aSphere::setTexture(const char* texPath) 
{
    texturePath = texPath;
}

void aSphere::setSegments(unsigned int nLon, unsigned int nLat)
{
    genVertices(nLon, nLat, radius);
    genIndices(nLon, nLat);
}

void aSphere::setShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    vShaderPath = vertexShaderPath;
    fShaderPath = fragmentShaderPath;

    if (shader)
    {
        delete shader;
        shader = NULL;
    }
    shader = new Shader(vShaderPath, fShaderPath);
}

void aSphere::drawMe()
{
}


void aSphere::genVertices(unsigned int nLon, unsigned int nLat, float r)
{
}

void aSphere::genIndices(unsigned int nLon, unsigned int nLat)
{
}