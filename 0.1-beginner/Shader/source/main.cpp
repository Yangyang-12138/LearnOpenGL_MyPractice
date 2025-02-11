// Shader.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	std::cout << "Today Is A Good Day!\n";

	wchar_t buffer[MAX_PATH];
	DWORD length = GetCurrentDirectory(MAX_PATH, buffer);
	if (length == 0)
	{
		std::cerr << "Error getting current directory." << std::endl;
	}
	else
	{
		std::wcout << "Current working directory is:" << buffer << std::endl;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shader", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
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

	//Shader myShader("D:/projects/LearnOpenGL/0.1-beginner/Shader/shaderCode/myShader.vs", "D:/projects/LearnOpenGL/0.1-beginner/Shader/shaderCode/myShader.fs");
	Shader myShader("shaderCode/myShader.vs", "shaderCode/myShader.fs");
	float vertices[9][7] = {
		//position						//color
	{ 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f, 1.0f },
	//1,2
	{ 0.0f, 0.8f, 1.0f,		0.0f, 0.1f, 0.2f, 1.0f },
	{ 0.4f, 0.0f, 1.0f,		0.3f, 0.4f, 0.5f, 1.0f },
	//3,4
	{ 0.8f, 0.0f, 1.0f,		0.6f, 0.7f, 0.8f, 1.0f },
	{ 0.0f, -0.4f, 1.0f,		0.9f, 0.8f, 0.7f, 1.0f },
	//5,6
	{ 0.0f, -0.8f, 1.0f,		0.6f, 0.5f, 0.4f, 1.0f },
	{ -0.4f, 0.0f, 1.0f,		0.3f, 0.2f, 0.1f, 1.0f },
	//7,8
	{ -0.8f, 0.0f, 1.0f,		0.0f, 0.1f, 0.2f, 1.0f },
	{ 0.0f, 0.4f, 1.0f,		0.3f, 0.4f, 0.5f, 1.0f }
	};

	unsigned int indices[4][3] = {
		{ 0, 1, 2 },
		{ 0, 3, 4 },
		{ 0, 5, 6 },
		{ 0, 7, 8 }
	};

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

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		float timeValue = glfwGetTime();
		vertices[0][0] = 0.3 * cos(-5 * timeValue) / 2 - 0.5;
		vertices[0][1] = 0.3 * sin(-5 * timeValue) / 2 + 0.5;

		vertices[1][0] = 0.8 * cos(-timeValue + M_PI / 2) / 2 - 0.5;
		vertices[1][1] = 0.8 * sin(-timeValue + M_PI / 2) / 2 + 0.5;
		vertices[3][0] = 0.8 * cos(-timeValue) / 2 - 0.5;
		vertices[3][1] = 0.8 * sin(-timeValue) / 2 + 0.5;
		vertices[5][0] = 0.8 * cos(-timeValue - M_PI / 2) / 2 - 0.5;
		vertices[5][1] = 0.8 * sin(-timeValue - M_PI / 2) / 2 + 0.5;
		vertices[7][0] = 0.8 * cos(-timeValue + M_PI) / 2 - 0.5;
		vertices[7][1] = 0.8 * sin(-timeValue + M_PI) / 2 + 0.5;


		vertices[2][0] = 0.5 * vertices[0][0] + 0.5 * vertices[3][0];
		vertices[2][1] = 0.5 * vertices[0][1] + 0.5 * vertices[3][1];
		vertices[4][0] = 0.5 * vertices[0][0] + 0.5 * vertices[5][0];
		vertices[4][1] = 0.5 * vertices[0][1] + 0.5 * vertices[5][1];
		vertices[6][0] = 0.5 * vertices[0][0] + 0.5 * vertices[7][0];
		vertices[6][1] = 0.5 * vertices[0][1] + 0.5 * vertices[7][1];
		vertices[8][0] = 0.5 * vertices[0][0] + 0.5 * vertices[1][0];
		vertices[8][1] = 0.5 * vertices[0][1] + 0.5 * vertices[1][1];
				

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
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

