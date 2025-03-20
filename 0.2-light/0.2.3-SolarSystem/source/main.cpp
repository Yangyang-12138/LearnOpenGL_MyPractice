// SolarSystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <iomanip>

#include "shader.h"
#include "camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define _USE_MATH_DEFINES
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
std::vector<glm::vec3> genBallVertices(unsigned int nLonSegments, unsigned int nLatSegments);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

Camera camera(glm::vec3(0.0, 0.0, 3.0));
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;

float deltaTime = 0.0;
float lastFrame = 0.0;

glm::vec3 lightColor = glm::vec3(0.7, 0.8, 0.6);
glm::vec3 lightPos(1.2, 1.0, 2.0);

int main()
{
    std::cout << "Today is a good day!!!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader lampShader("shaderCode/lamp.vert", "shaderCode/lamp.frag");
    Shader cubeShader("shaderCode/cube.vert", "shaderCode/cube.frag");

    float vertices[36][8] =
    {
        //location              normal         texture
//dice-1
       {-1.0, -1.0, 1.0,    0.0, 0.0, 1.0,    0.0, 1.0},
       {-1.0, 1.0, 1.0,     0.0, 0.0, 1.0,    1.0, 1.0},
       {1.0, 1.0, 1.0,      0.0, 0.0, 1.0,    1.0, 0.0},

       {1.0, 1.0, 1.0,      0.0, 0.0, 1.0,    1.0, 0.0},
       {1.0, -1.0, 1.0,     0.0, 0.0, 1.0,    0.0, 0.0},
       {-1.0, -1.0, 1.0,    0.0, 0.0, 1.0,    0.0, 1.0},

//dice-2
       {1.0, -1.0, 1.0,     1.0, 0.0, 0.0,    0.0, 1.0},
       {1.0, 1.0, 1.0,      1.0, 0.0, 0.0,    1.0, 1.0},
       {1.0, 1.0, -1.0,     1.0, 0.0, 0.0,    1.0, 0.0},

       {1.0, 1.0, -1.0,     1.0, 0.0, 0.0,    1.0, 0.0},
       {1.0, -1.0, -1.0,    1.0, 0.0, 0.0,    0.0, 0.0},
       {1.0, -1.0, 1.0,     1.0, 0.0, 0.0,    0.0, 1.0},

//dice-3
       {1.0, -1.0, -1.0,    0.0, 0.0, -1.0,   0.0, 1.0},
       {1.0, 1.0, -1.0,     0.0, 0.0, -1.0,   1.0, 1.0},
       {-1.0, 1.0, -1.0,    0.0, 0.0, -1.0,   1.0, 0.0},

       {-1.0, 1.0, -1.0,    0.0, 0.0, -1.0,   1.0, 0.0},
       {-1.0, -1.0, -1.0,   0.0, 0.0, -1.0,   0.0, 0.0},
       {1.0, -1.0, -1.0,    0.0, 0.0, -1.0,   0.0, 1.0},

//dice-4
       {-1.0, -1.0, 1.0,    0.0, -1.0, 0.0,   0.0, 1.0},
       {1.0, -1.0, 1.0,     0.0, -1.0, 0.0,   1.0, 1.0},
       {1.0, -1.0, -1.0,    0.0, -1.0, 0.0,   1.0, 0.0},

       {1.0, -1.0, -1.0,    0.0, -1.0, 0.0,   1.0, 0.0},
       {-1.0, -1.0, -1.0,   0.0, -1.0, 0.0,   0.0, 0.0},
       {-1.0, -1.0, 1.0,    0.0, -1.0, 0.0,   0.0, 1.0},

//dice-5
       {-1.0, 1.0, 1.0,     -1.0, 0.0, 0.0,   0.0, 1.0},
       {-1.0, -1.0, 1.0,    -1.0, 0.0, 0.0,   1.0, 1.0},
       {-1.0, -1.0, -1.0,   -1.0, 0.0, 0.0,   1.0, 0.0},

       {-1.0, -1.0, -1.0,   -1.0, 0.0, 0.0,   1.0, 0.0},
       {-1.0, 1.0, -1.0,    -1.0, 0.0, 0.0,   0.0, 0.0},
       {-1.0, 1.0, 1.0,     -1.0, 0.0, 0.0,   0.0, 1.0},

//dice-6
       {1.0, 1.0, 1.0,      0.0, 0.0, 1.0,   0.0, 1.0},
       {-1.0, 1.0, 1.0,     0.0, 0.0, 1.0,   1.0, 1.0},
       {-1.0, 1.0, -1.0,    0.0, 0.0, 1.0,   1.0, 0.0},

       {-1.0, 1.0, -1.0,    0.0, 0.0, 1.0,   1.0, 0.0},
       {1.0, 1.0, -1.0,     0.0, 0.0, 1.0,   0.0, 0.0},
       {1.0, 1.0, 1.0,      0.0, 0.0, 1.0,   0.0, 1.0}
    };

    unsigned int lampVAO, cubeVAO, VBO;
    glGenVertexArrays(1, &lampVAO);
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(lampVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int textures[6];
    glGenTextures(6, textures);
    for (int i = 0; i < sizeof(textures) / sizeof(textures[0]); i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int img_width, img_height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(
            ("../../textures/cube/dice_black-" + std::to_string(i + 1) + (".jpeg")).c_str(), 
            &img_width, &img_height, &nrChannels, 0);
        if (data)
        {
            unsigned int format = NULL;
            switch (nrChannels)
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
            glTexImage2D(GL_TEXTURE_2D, 0, format, img_width, img_height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture:" 
                << ("../../textures/cube/dice_black-" + std::to_string(i + 1) + (".jpeg")).c_str() 
                << std::endl;
        }
    }


    Shader ballShader("shaderCode/firstBall.vert", "shaderCode/firstBall.frag");
    std::vector<glm::vec3> ballVertices = genBallVertices(5, 5);
    unsigned int ballVAO, ballVBO;
    glGenVertexArrays(1, &ballVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(ballVAO);
    glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ballVertices), ballVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightPos.x = sin(1.3 * glfwGetTime()) * 2.0;
		lightPos.y = sin(1.5 * glfwGetTime()) * 2.0;
		lightPos.z = cos(1.7 * glfwGetTime()) * 2.0;

        cubeShader.use();
        cubeShader.setVec3("lightColor", lightColor);
        cubeShader.setVec3("lightPos", lightPos);
        cubeShader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0);

        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);

        glBindVertexArray(cubeVAO);

        for (int j = 0; j < sizeof(textures) / sizeof(textures[0]); j++)
        {
            glActiveTexture(GL_TEXTURE0 + j);
            glBindTexture(GL_TEXTURE_2D, textures[j]);
            cubeShader.setInt("nTexture", j);
            glDrawArrays(GL_TRIANGLES, j * 6, 6);
        }

        lampShader.use();
        lampShader.setVec3("lightColor", lightColor);
        model = glm::mat4(1.0);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.1));
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        lampShader.setMat4("model", model);

        glBindVertexArray(lampVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &lampVAO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    float xpos = static_cast<float>(xPos);
    float ypos = static_cast<float>(yPos);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(xOffset, yOffset);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

std::vector<glm::vec3> genBallVertices(unsigned int nLonSegments, unsigned int nLatSegments)
{
	std::vector<glm::vec3> vertices;
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);

    float lonTheta, latPhi;

    for (int iLat = 0; iLat <= nLatSegments; iLat++)
    {
        latPhi = iLat * M_PI / nLatSegments - M_PI / 2;
        for (int iLat = 0; iLat <= nLonSegments; iLat++)
        {
            lonTheta = 2 * iLat * M_PI / nLonSegments;
            float x = cos(latPhi) * sin(lonTheta);
            float y = sin(latPhi);
            float z = cos(latPhi) * cos(lonTheta);
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    return vertices;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
