// Color.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"

#include <iostream>

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
glm::vec3 lightPos(1.2, 1.0, 2.0);

int main()
{
    std::cout << "Today is a good day!!!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Color", NULL, NULL);
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
        std::cout << "Failed to initialize GLAD." << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader lightShader("shaderCode/light.vs", "shaderCode/light.fs");
    Shader cubeShader("shaderCode/cube.vs", "shaderCode/cube.fs");

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

    unsigned int cubeVAO, VBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.75, 0.75, 0.75, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2));

        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        lightShader.setMat4("model", model);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cubeShader.use();
        cubeShader.setVec3("objectColor", glm::vec3(1.0, 0.5, 0.31));
        cubeShader.setVec3("lightColor", glm::vec3(0.5, 0.6, 0.7));
        model = glm::mat4(1.0);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);
        glBindVertexArray(cubeVAO);
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
    float xpos = static_cast<float>(xPos);
    float ypos = static_cast<float>(yPos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = -ypos + lastY;

    lastX = xpos;
    lastY = ypos;

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


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
