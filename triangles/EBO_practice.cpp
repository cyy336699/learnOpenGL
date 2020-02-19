/*#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

GLFWwindow* window;
float vertices[] = {
	0.5f, 0.5f, 0.0f,	//右上角
	0.5f, -0.5f, 0.0f,	//右下角
	-0.5f, -0.5f, 0.0f,	//左下角
	-0.5f, 0.5f, 0.0f	//左上角
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

const char* FragmentShaderSource = "#version 400 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//检查源码编译是否错误
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
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
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}*/
