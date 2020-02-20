#pragma once
#include <glad/glad.h>
#include <iostream>

class shaderClass
{
	public:
		int shaderProgram;
		void useShader();
		shaderClass(void);
		~shaderClass(void);
};

