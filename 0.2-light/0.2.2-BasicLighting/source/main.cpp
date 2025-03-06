// BasicLighting.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH    = 800;
const unsigned int SCR_HEIGHT   = 800;

Camera camera(glm::vec3(0.0, 0.0, 3.0));
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;

float deltaTime = 0.0;
float lastFrame = 0.0;

glm::vec3 lightPos(2.0, 2.0, 2.0);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "BasicLighting", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader cubeShader("./shaderCode/cube.vert", "./shaderCode/cube.frag");
    Shader lightShader("./shaderCode/light.vert", "./shaderCode/light.frag");

    float vertices[36][6] =
    {
            //location          //normal
    //1
        {-1.0, 1.0, 1.0,    0.0, 0.0, 1.0},
        {-1.0, -1.0, 1.0,   0.0, 0.0, 1.0},
        {1.0, -1.0, 1.0,    0.0, 0.0, 1.0},

        {1.0, -1.0, 1.0,    0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0,     0.0, 0.0, 1.0},
        {-1.0, 1.0, 1.0,    0.0, 0.0, 1.0},

    //2
        {1.0, -1.0, 1.0,    1.0, 0.0, 0.0},
        {1.0, -1.0, -1.0,   1.0, 0.0, 0.0},
        {1.0, 1.0, -1.0,    1.0, 0.0, 0.0},

        {1.0, 1.0, -1.0,    1.0, 0.0, 0.0},
        {1.0, 1.0, 1.0,     1.0, 0.0, 0.0},
        {1.0, -1.0, 1.0,    1.0, 0.0, 0.0},

    //3
        {1.0, -1.0, -1.0,   0.0, 0.0, -1.0},
        {-1.0, -1.0, -1.0,  0.0, 0.0, -1.0},
        {-1.0, 1.0, -1.0,   0.0, 0.0, -1.0},

        {-1.0, 1.0, -1.0,   0.0, 0.0, -1.0},
        {1.0, 1.0, -1.0,    0.0, 0.0, -1.0},
        {1.0, -1.0, -1.0,   0.0, 0.0, -1.0},

    //4
        {-1.0, -1.0, 1.0,   0.0, -1.0, 0.0},
        {-1.0, -1.0, -1.0,  0.0, -1.0, 0.0},
        {1.0, -1.0, -1.0,   0.0, -1.0, 0.0},

        {1.0, -1.0, -1.0,   0.0, -1.0, 0.0},
        {1.0, -1.0, 1.0,    0.0, -1.0, 0.0},
        {-1.0, -1.0, 1.0,   0.0, -1.0, 0.0},

    //5
        {-1.0, 1.0, 1.0,    -1.0, 0.0, 0.0},
        {-1.0, 1.0, -1.0,   -1.0, 0.0, 0.0},
        {-1.0, -1.0, -1.0,  -1.0, 0.0, 0.0},

        {-1.0, -1.0, -1.0,  -1.0, 0.0, 0.0},
        {-1.0, -1.0, 1.0,   -1.0, 0.0, 0.0},
        {-1.0, 1.0, 1.0,    -1.0, 0.0, 0.0},

    //6
        {1.0, 1.0, 1.0,     0.0, 1.0, 0.0},
        {1.0, 1.0, -1.0,    0.0, 1.0, 0.0},
        {-1.0, 1.0, -1.0,   0.0, 1.0, 0.0},

        {-1.0, 1.0, -1.0,   0.0, 1.0, 0.0},
        {-1.0, 1.0, 1.0,    0.0, 1.0, 0.0},
        {1.0, 1.0, 1.0,     0.0, 1.0, 0.0}
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int lightVAO, cubeVAO;
    glGenVertexArrays(1, &lightVAO);
    glGenVertexArrays(1, &cubeVAO);

    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.75, 0.75, 0.75, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.use();
        cubeShader.setVec3("objectColor", glm::vec3(0.75, 0.88, 0.97));
        cubeShader.setVec3("lightColor", glm::vec3(0.9, 0.8, 0.7));
        cubeShader.setVec3("lightPos", glm::vec3(lightPos));
        cubeShader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.use();
        model = glm::mat4(1.0);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.1));
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        lightShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &lightVAO);
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
    if (firstMouse)
    {
        lastX = static_cast<float>(xPos);
        lastY = static_cast<float>(yPos);
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.processKeyBoard(FORWARD, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.processKeyBoard(LEFT, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.processKeyBoard(BACKWARD, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.processKeyBoard(RIGHT, deltaTime);
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
