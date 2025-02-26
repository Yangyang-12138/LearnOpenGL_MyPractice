// CoordSys.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string.h>

#include "shader_m.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CoordSys", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader myShader("shaderCode/coordsys.vs", "shaderCode/coordsys.fs");

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

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(2.0, 5.0, -15.0),
        glm::vec3(-1.5, -2.2, -2.5),
        glm::vec3(-3.8, -2.0, -12.3),
        glm::vec3(2.4, -0.4, -3.5),
        glm::vec3(-1.7, 3.0, -7.5),
        glm::vec3(1.3, -2.0, -2.5),
        glm::vec3(1.5, 2.0, -2.5),
        glm::vec3(1.5, 0.3, -1.5),
        glm::vec3(-1.3, 1.0, -1.5),
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

    unsigned int texture[6];
    glGenTextures(6, texture);

    for (int i = 0; i < sizeof(texture) / sizeof(texture[0]); i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(("textureImg/dice-" + std::to_string(i + 1) + ".png").c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            unsigned int format = NULL;
            if (nrChannels == 1)
            {
                format = GL_RED;
            }
            else if (nrChannels == 3)
            {
                format = GL_RGB;
            }
            else if (nrChannels == 4)
            {
                format = GL_RGBA;
            }
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    //myShader.use();
    //myShader.setInt("texture0", 0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.75, 0.75, 0.75, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myShader.use();
        for (int i = 0; i < sizeof(texture) / sizeof(texture[0]); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, texture[i]);
        }

        glm::mat4 view = glm::mat4(1.0);
        glm::mat4 projection = glm::mat4(1.0);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0, 0.0, -10.0));
        view = glm::rotate(view, (float)glm::radians(90.0), glm::vec3(1.0, 1.5, 2.0));
        myShader.set4Mat("projection", projection);
        myShader.set4Mat("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0);
            model = glm::translate(model, cubePositions[i]);
            float angle = 13.1 * i + 11.7;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0 - i * 1.7, i * 2.0 + 0.3, 3.5 * i));
            myShader.set4Mat("model", model);
            for (int j = 0; j < 6; j++)
            {
                myShader.setInt("texture0", j);
                glDrawArrays(GL_TRIANGLES, 6 * j, 6);
            }
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
    std::cout << "Window size :" << width << "×" << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
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
