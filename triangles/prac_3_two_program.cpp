/*#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

GLFWwindow* window;
unsigned int VBOs[2], VAOs[2];

const char* FragmentShaderSource_1 = "#version 400 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* FragmentShaderSource_2 = "#version 400 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

const char* VertexShaderSource  = "#version 400 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void VAOSet();


int main()
{
	init();
	VAOSet();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader_1;
	fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &FragmentShaderSource_1, NULL);
	glCompileShader(fragmentShader_1);

	unsigned int fragmentShader_2;
	fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &FragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);

	unsigned int shaderProgram_1;
	shaderProgram_1 = glCreateProgram();
	glAttachShader(shaderProgram_1, vertexShader);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);

	unsigned int shaderProgram_2;
	shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, vertexShader);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);

	glDeleteShader(fragmentShader_1);
	glDeleteShader(fragmentShader_2);
	glDeleteShader(vertexShader);

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram_1);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//检查并调用事件， 交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

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
		return ;
	}
	glfwMakeContextCurrent(window); //设置为当前线程主上下文
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//初始化GLAD,来管理OpenGL指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initaize GLAD" << std::endl;
		return ;
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
}

void VAOSet()
{
	float firstTriangle[] = {
		-1.0f, 0.0f, 0.0f,
		-0.5f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	float secondTriangle[] = {
		0.0f, 0.0f, 0.0f,
		0.5f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}*/