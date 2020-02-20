#include <glad/glad.h>
#include "shaderClass.h"
#include "stb_image.h"
#include <glfw/glfw3.h>
#include <iostream>
#include <stdio.h>

GLFWwindow* window;
float vertices[] = {
	 0.5f,  0.5f,  0.0f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f,  0.0f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.0f,	 1.0f,  1.0f,  0.0f,	0.0f, 1.0f
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};
float value = 0.2f;

void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void VAOSet();


int main()
{
	init();
	VAOSet();

	//纹理
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);			//创建纹理
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);	//绑定纹理
	int width, height, nrChannels;
	unsigned char* data;
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	   // set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);	//绑定纹理
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	   // set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	shaderClass myshader;
	myshader.useShader();
	glUniform1i(glGetUniformLocation(myshader.shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(myshader.shaderProgram, "texture2"), 1);

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform1f(glGetUniformLocation(myshader.shaderProgram, "value"), value);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//检查并调用事件， 交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//释放资源
	glfwTerminate();
	return 0;
}

void init()
{
	//初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); //次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式


	//创建窗口对象
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window); //设置为当前线程主上下文
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//初始化GLAD,来管理OpenGL指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initaize GLAD" << std::endl;
		return;
	}

	//设置视口大小
	glViewport(0, 0, 800, 600);
}

//视口随用户调整而调整
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//按键检测
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		value -= 0.001f;
		if (value <= 0.0f) value = 0.0f;
		printf("%.2f\n", value);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		value += 0.001f;
		if (value >= 1.0f) value = 1.0f;
		printf("%.2f\n", value);
	}
		
}

void VAOSet()
{
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}