#include "asphere.h"

aSphere::aSphere()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

aSphere::~aSphere()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int img_width, img_height, nrChannel;
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

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SphereVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SphereVertex), (void*)(offsetof(SphereVertex, normal)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SphereVertex), (void*)(offsetof(SphereVertex, texturePos)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
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
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader->setInt("nTexture", 0);
    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void aSphere::genVertices(unsigned int nLonSegments, unsigned int nLatSegments, float r)
{
    vertices.clear();

    float lonTheta, latPhi;

    for (unsigned int iLat = 0; iLat <= nLatSegments; iLat++)
    {
        latPhi = (float)(iLat * M_PI / nLatSegments - M_PI / 2);
        for (unsigned int iLon = 0; iLon <= nLonSegments; iLon++)
        {
            lonTheta = (float)(2 * iLon * M_PI / nLonSegments);
            float vx = radius * cos(latPhi) * sin(lonTheta);
            float vy = radius * sin(latPhi);
            float vz = radius * cos(latPhi) * cos(lonTheta);
            SphereVertex ball = {
                {vx, vy, vz},
                glm::normalize(glm::vec3(vx, vy, vz)),
                {(float)iLon / nLonSegments, 1.0 - (float)iLat / nLatSegments},
            };
            vertices.push_back(ball);
        }
    }
}

void aSphere::genIndices(unsigned int nLonSegments, unsigned int nLatSegments)
{
    indices.clear();

    for (unsigned int iLat = 0; iLat < nLatSegments; iLat++)
    {
        for (unsigned int iLon = 0; iLon < nLonSegments; iLon++)
        {
            indices.push_back(iLat * (nLonSegments + 1) + iLon);
            indices.push_back((iLat + 1) * (nLonSegments + 1) + iLon + 1);
            indices.push_back((iLat + 1) * (nLonSegments + 1) + iLon);

            indices.push_back(iLat * (nLonSegments + 1) + iLon);
            indices.push_back(iLat * (nLonSegments + 1) + iLon + 1);
            indices.push_back((iLat + 1) * (nLonSegments + 1) + iLon + 1);
        }
    }
}