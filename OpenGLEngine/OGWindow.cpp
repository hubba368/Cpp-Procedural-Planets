#include "OGWindow.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>



OGWindow::OGWindow()
{
	_mWindowHeight = 768;
	_mWindowWidth = 1280;
}


OGWindow::~OGWindow()
{

}

//For Initial Shader Testing

float vertices[] =
{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};






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

	test = glGetUniformLocation(mShader->GetProgramHandle(), "transform");


}


void OGWindow::InitCamera() 
{
	camera = new MainCamera();
	camera->InitialiseCamera();
	camera->SetCameraPosition(&Vector3(0.0f, 0.0f, -1.0f));
	camera->SetCameraFOV(90);
}


void OGWindow::SetAllMatrices() 
{
	//get the V and P matrix components
	projection = *camera->GetProjectionMatrix();
	modelview = *camera->GetViewMatrix();

	//re-enter matrix uniforms for the vertex shader - transform is set for each object in scene
	glUniformMatrix4fv(0, 1, GL_FALSE, modelview.ToPtr());
	glUniformMatrix4fv(1, 1, GL_FALSE, projection.ToPtr());
	glUniformMatrix4fv(2, 1, GL_FALSE, transform.ToPtr());


}


void OGWindow::StartInitialState() 
{
	//initialise glfw
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window creation
	window = glfwCreateWindow(_mWindowWidth, _mWindowHeight, "Window", NULL, NULL);

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
	InitCamera();
	RenderLoop();
}


void OGWindow::RenderLoop() 
{

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

	//ALL RENDERING IS DONE HERE
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);
		float aspectRatio = _mWindowWidth / _mWindowHeight;
		camera->SetProjectionMatrix(90.0f, aspectRatio, 1.0f, 1000.0f);
		mShader->ActivateShaderProgram();
		glBindVertexArray(gVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		SetAllMatrices();


		CameraKeyboardMovement(window);
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


void OGWindow::CameraKeyboardMovement(GLFWwindow *window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		camera->DollyCamera(0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->StrafeCamera(-0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->DollyCamera(-0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->StrafeCamera(0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		camera->PedCamera(0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		camera->PedCamera(-0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera->RotateCamera(0, 0, -0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera->RotateCamera(0, 0, 0.01f);
	}
}


int main() 
{
	OGWindow *w = new OGWindow();
	w->StartInitialState();

	return 0;
}

