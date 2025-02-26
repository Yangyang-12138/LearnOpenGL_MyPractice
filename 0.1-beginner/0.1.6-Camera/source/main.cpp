// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "camera.h"
#include "shader_m.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
Camera camera(glm::vec3(0.0, 0.0, 20.0));
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;
float deltaTime = 0.0;
float lastFrame = 0.0;

int main()
{
    std::cout << "Today is a good day!!!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Camera", NULL, NULL);
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
    Shader myShader("./shaderCode/camera.vs", "./shaderCode/camera.fs");

    float vertices[36][5] = {
            //location       //texture
  //dice-1        
        {-0.5, -0.5, 0.5,     0.0, 0.0},
        {0.5, -0.5, 0.5,      1.0, 0.0},
        {0.5,  0.5, 0.5,      1.0, 1.0},
        
        {0.5,  0.5, 0.5,      1.0, 1.0},
        {-0.5,  0.5, 0.5,     0.0, 1.0},
        {-0.5, -0.5, 0.5,     0.0, 0.0},

  //dice-2        
        {-0.5, -0.5, -0.5,    0.0, 0.0},
        {0.5, -0.5, -0.5,     1.0, 0.0},
        {0.5, -0.5, 0.5,      1.0, 1.0},
        
        {0.5, -0.5, 0.5,      1.0, 1.0},
        {-0.5, -0.5, 0.5,     0.0, 1.0},
        {-0.5, -0.5, -0.5,    0.0, 0.0},

  //dice-3        
        {-0.5, 0.5, -0.5,     0.0, 0.0},
        {0.5, 0.5, -0.5,      1.0, 0.0},
        {0.5, -0.5, -0.5,     1.0, 1.0},
        
        {0.5, -0.5, -0.5,     1.0, 1.0},
        {-0.5, -0.5, -0.5,    0.0, 1.0},
        {-0.5, 0.5, -0.5,     0.0, 0.0},

  //dice-4     
        {-0.5, 0.5, -0.5,      0.0, 0.0},
        {-0.5, -0.5, -0.5,    1.0, 0.0},
        {-0.5, -0.5, 0.5,     1.0, 1.0},
        
        {-0.5, -0.5, 0.5,     1.0, 1.0},
        {-0.5, 0.5, 0.5,      0.0, 1.0},
        {-0.5, 0.5, -0.5,     0.0, 0.0},

  //dice-5        
        {0.5, 0.5, -0.5,      0.0, 0.0},
        {-0.5, 0.5, -0.5,     1.0, 0.0},
        {-0.5, 0.5, 0.5,      1.0, 1.0},
        
        {-0.5, 0.5, 0.5,      1.0, 1.0},
        {0.5, 0.5, 0.5,       0.0, 1.0},
        {0.5, 0.5, -0.5,      0.0, 0.0},

  //dice-6        
        {0.5, -0.5, -0.5,     0.0, 0.0},
        {0.5, 0.5, -0.5,      1.0, 0.0},
        {0.5, 0.5, 0.5,       1.0, 1.0},
        
        {0.5, 0.5, 0.5,       1.0, 1.0},
        {0.5, -0.5, 0.5,      0.0, 1.0},
        {0.5, -0.5, -0.5,     0.0, 0.0}
    };

    glm::vec3 cubePosition[10] = {
        glm::vec3(0.0, 0.0, 10.0),
        glm::vec3(1.1, 1.3, -10.0),
        glm::vec3(-1.5, -2.2, -2.5),
        glm::vec3(1.5, 8.0, -4.4),
        glm::vec3(5.5, 6.0, -1.0),
        glm::vec3(-6.6, -7.7, -9.9),
        glm::vec3(4.8, -4.8, -4.8),
        glm::vec3(-1.3, 1.0, -1.5),
        glm::vec3(1.5, 0.32, -7.7),
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int axisVBO;
    glGenBuffers(1, &axisVBO);

    unsigned int texture[6];
    glGenTextures(6, &texture[0]);
    for (int i = 0; i < sizeof(texture) / sizeof(texture[0]); i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(std::string("./textureImg/dice-" + std::to_string(i + 1) + ".png").c_str(),
            &width, &height, &nrChannels, 0);
        if (data)
        {
            unsigned int format;
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
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture:"
                << std::string("./textureImg/dice-" + std::to_string(i + 1) + ".png").c_str()
                << std::endl;
        }
        stbi_image_free(data);

        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
    }

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.75, 0.75, 0.75, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 
            (float)SCR_WIDTH / (float)SCR_HEIGHT, 
            0.1f, 100.0f);
        myShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        myShader.setMat4("view", view);

        glBindVertexArray(VAO);
        for (int i = 0; i < sizeof(cubePosition) / sizeof(cubePosition[0]); i++)
        {
            glm::mat4 model = glm::mat4(1.0);
            model = glm::translate(model, cubePosition[i]);
            float angle = 50.0f * i + 16.7;
            model = glm::rotate(model, 
                (float)glfwGetTime() * glm::radians(angle) * 5 / (i + 1), 
                glm::vec3(0.5 * sin(glfwGetTime()) + i, 
                    3.66 * i * cos(glfwGetTime()) / 100.0, 
                    1.7 * i));
            myShader.setMat4("model", model);

            //draw cubes
            myShader.setBool("isAxisPoint", GL_FALSE);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            for (int j = 0; j < sizeof(texture) / sizeof(texture[0]); j++)
            {
                myShader.setInt("texture0", j);
                myShader.setInt("texture1", j + 1);
                if (j == sizeof(texture) / sizeof(texture[0]) - 1)
                {
                    myShader.setInt("texture1", 0);
                }
                glDrawArrays(GL_TRIANGLES, 6 * j, 6);
            }

            //draw the axis of rotation
            myShader.setBool("isAxisPoint", GL_TRUE);

        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
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
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
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
