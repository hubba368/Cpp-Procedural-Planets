#include "OGWindow.h"

#include "GLEW\include\glew.h"
#include "GLFW\include\GLFW\glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>



OGWindow::OGWindow()
{
	
}


OGWindow::~OGWindow()
{

}

//For Initial Shader Testing
/*
float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

GLuint gVAO;
GLuint gVBO;
glGenVertexArrays(1, &gVAO);
glBindVertexArray(gVAO);

glGenBuffers(1, &gVBO);
glBindBuffer(GL_ARRAY_BUFFER, gVBO);

glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

glClear(GL_COLOR_BUFFER_BIT);
mShader->ActivateShaderProgram();
glBindVertexArray(gVAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
*/

void OGWindow::InitialiseShaders() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//initialise and load shaders
	mShader = new OGLShaderLoader();

	mShader->LoadShaderProgram();
	//Vertex Shader
	mShader->AttachAndBuildFromSource("C:/Users/Elliott/Documents/Visual Studio 2015/Projects/OpenGLEngine/Assets/Shaders/VertShader.vert", GL_VERTEX_SHADER);
	//Frag Shader
	mShader->AttachAndBuildFromSource("C:/Users/Elliott/Documents/Visual Studio 2015/Projects/OpenGLEngine/Assets/Shaders/FragShader.frag", GL_FRAGMENT_SHADER);

	mShader->BindAttributeLocation(0, "aPos");

	glBindFragDataLocation(mShader->GetProgramHandle(), 0, "colour");

	mShader->LinkShaderProgram();




}


void OGWindow::StartInitialState() 
{
	//initialise glfw
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window creation
	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to initialise window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//initialise glew after window creation
	GLint initResult = glewInit();

	if (GLEW_OK != initResult)
	{
		printf("Error: %s\n", glewGetErrorString(initResult));
		//exit(EXIT_FAILURE);
	}


	InitialiseShaders();
	RenderLoop();
}


void OGWindow::RenderLoop() 
{




	while (!glfwWindowShouldClose(window))
	{
//		ProcessInput(window);

		//rendering pls


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//callback function to resize window accordingly
	glViewport(0, 0, width, height);
}


void ProcessInput(GLFWwindow *window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
}


int main() 
{
	OGWindow *w = new OGWindow();
	w->StartInitialState();

	return 0;
}

