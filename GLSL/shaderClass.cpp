#include "shaderClass.h"

shaderClass::shaderClass(void)
{
	const char* FragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		//"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"uniform float value;\n"
		"void main()\n"
		"{\n"
		"	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), value);\n"
		"}\n\0";

	const char* VertexShaderSource = "#version 400 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		//"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		//"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 change;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = change * vec4(aPos, 1.0);\n"
		//"	ourColor = aColor;\n"
		"	TexCoord = aTexCoord;\n"
		"}\n\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//ºÏ≤È‘¥¬Î±‡“Î «∑Ò¥ÌŒÛ
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}



	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

void shaderClass::useShader(void)
{
	glUseProgram(shaderProgram);
}

shaderClass::~shaderClass(void)
{

}