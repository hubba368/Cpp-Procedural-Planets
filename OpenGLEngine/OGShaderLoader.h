#pragma once
#include "GLEW\include\glew.h"
#include "GLFW\include\GLFW\glfw3.h"
#include <iostream>

class OGShaderLoader
{
public:

	OGShaderLoader();
	~OGShaderLoader();

	GLuint loadShaderFromTxtFile(std::string fileName, GLenum ID);
};

