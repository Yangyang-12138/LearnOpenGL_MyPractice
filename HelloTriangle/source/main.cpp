// HelloTriangle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct CColorRGB
{
    float r, g, b;
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
CColorRGB HsvToRgb(float h, float s, float v);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 800;
const char* vertexShaderSource = "#version 330 core\n"
                                                        "layout (location = 0) in vec3 aPos;\n"
                                                        "layout (location = 1) in vec4 aColor;\n"
                                                        "out vec4 vertexColor;\n"
                                                        "void main()\n"
                                                        "{\n"
                                                        "       gl_Position = vec4(aPos, 1.0);\n"
                                                        "       vertexColor = aColor;\n"
                                                        "}\n\0";
const char* fragmentShaderSource =  "#version 330 core\n"
                                                                "in vec4 vertexColor;\n"
                                                                "out vec4 FragColor;\n"
                                                                "void main()\n"
                                                                "{\n"
                                                                "       FragColor = vertexColor;\n"
                                                                "}\n\0";

int main()
{
    std::cout << "Hello World!!!\nToday Is A Good Day!!!\n"<<std::endl;

    //Variables used to draw the graph
    float vertices[9][7] = {
        //location                  //color
{0.0f, 0.0f, 0.0f,          0.9f, 0.9f, 0.9f, 1.0f},
{0.1f, 0.2f, 0.0f,          0.9f, 0.0f, 0.0f, 1.0f},
{0.3f, 0.4f, 0.0f,          0.0f, 0.9f, 0.0f, 1.0f},
{0.5f, 0.6f, 0.0f,          0.0f, 0.1f, 0.2f, 0.7f},
{0.7f, 0.8f, 0.0f,          0.3f, 0.4f, 0.5f, 0.6f},
{0.9f, 1.0f, 0.0f,          0.6f, 0.7f, 0.8f, 0.5f},
{0.9f, 0.8f, 0.0f,          0.9f, 1.0f, 0.9f, 0.4f},
{0.7f, 0.6f, 0.0f,          0.8f, 0.7f, 0.6f, 0.3f},
{0.5f, 0.4f, 0.0f,          0.5f, 0.4f, 0.3f, 0.2f},
    };

    float i =0.0f, j = 0.0f;

    unsigned int indices[][3] = {
        {0,1,2},
        {0,2,3},
        {0,3,4},
        {0,4,5},
        {0,5,6},
        {0,6,7},
        {0,7,8},
        {0,8,1}
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "HelloTriangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed To Create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed To Initialized GLAD" << std::endl;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        float timeValue = glfwGetTime();
        for (int k = 0; k < sizeof(vertices) / 7/sizeof(float) - 1; k++)
        {
            if ((k % 2) == 1)
            {
                vertices[k + 1][0] = (0.7 - 0.3 * sin(1.7 * timeValue)) * cos(k * M_PI / 4 + sin(1.3 * timeValue) / 0.3);
                vertices[k + 1][1] = (0.7 - 0.3 * sin(1.7 * timeValue)) * sin(k * M_PI / 4 + sin(1.3 * timeValue) / 0.3);
            }
            else
            {
                vertices[k + 1][0] = (0.7 + 0.3 * sin(2.1 * timeValue)) * cos(k * M_PI / 4 + sin(1.3 * timeValue) / 0.3);
                vertices[k + 1][1] = (0.7 + 0.3 * sin(2.1 * timeValue)) * sin(k * M_PI / 4 + sin(1.3 * timeValue) / 0.3);
            }

            CColorRGB rgb = { 0, 0, 0 };
            rgb = HsvToRgb(k * M_PI / 4 + sin(timeValue), 0.1 + 0.9 * sin(0.7 * timeValue), 0.2 + 0.8 * sin(1.3 * timeValue));
            vertices[k + 1][3] = rgb.r;
            vertices[k + 1][4] = rgb.g;
            vertices[k + 1][5] = rgb.b;
        }        

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

CColorRGB HsvToRgb(float h, float s, float v)
{
    h = fmod(h, 2 * M_PI);
    if (h < 0)
    {
        h += 2 * M_PI;
    }

    float c = v * s;
    float x = c * (1 - std::fabs(fmod(h / (M_PI / 3), 2) - 1));
    float m = v - c;

    float r = 0, g = 0, b = 0;

    if ((h >= 0) && (h < M_PI / 3))
    {
        r = c;
        g = x;
        b = 0;
    }
    else if ((h >= M_PI / 3) && (h < 2 * M_PI / 3))
    {
        r = x;
        g = c;
        b = 0;
    }
    else if ((h >= 2 * M_PI / 3) && (h < M_PI))
    {
        r = 0;
        g = c;
        b = x;
    }
    else if ((h >= M_PI) && (h < 4 * M_PI / 3))
    {
        r = 0;
        g = x;
        b = c;
    }
    else if ((h >= 4 * M_PI / 3) && (h < 5 * M_PI / 3))
    {
        r = x;
        g = 0;
        b = c;
    }
    else if ((h >= 5 * M_PI / 3) && (h < 2 * M_PI))
    {
        r = c;
        g = 0;
        b = x;
    }
    return{ r + m,g + m,b + m };
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

 //入门使用技巧: 
 //  1. 使用解决方案资源管理器窗口添加/管理文件
 //  2. 使用团队资源管理器窗口连接到源代码管理
 //  3. 使用输出窗口查看生成输出和其他消息
 //  4. 使用错误列表窗口查看错误
 //  5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
 //  6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
