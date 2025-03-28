#include "asphere.h"

aSphere::aSphere()
    :shader(NULL),
    radius(1.0f),
    textureData(NULL),
    vShaderPath(NULL),
    fShaderPath(NULL),
    texturePath(NULL),
    nLonSegments(8),
    nLatSegments(8),
    img_width(0),
    img_height(0),
    nrChannel(0)
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
        std::cout << "Failed to set radius£ºThe radius of the ball must be greater than 0" << std::endl;
    }
}

void aSphere::setTexture(const char* texPath, bool vFlip)
{
    texturePath = texPath;
    stbi_set_flip_vertically_on_load(vFlip);
    textureData = stbi_load(texturePath, &img_width, &img_height, &nrChannel, 0);
    if (textureData)
    {
        unsigned int format = NULL;
        switch (nrChannel)
        {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
            break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, img_width, img_height, 0, format, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture:" << texturePath << std::endl;
    }
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