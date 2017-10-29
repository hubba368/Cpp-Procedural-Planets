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

	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	
};

GLfloat bufferData[] = 
{
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};






void OGWindow::InitialiseShaders() 
{
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);

	//needed to stop vertices that you can't see from being rendered until seen.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//initialise and load shaders
	mShader = new OGLShaderLoader();

	mShader->LoadShaderProgram();
	//Vertex Shader
	mShader->AttachAndBuildFromSource("C:/Users/Elliott/Documents/Visual Studio 2015/Projects/OpenGLEngine/Assets/Shaders/VertShader.vert", GL_VERTEX_SHADER);
	//Frag Shader
	mShader->AttachAndBuildFromSource("C:/Users/Elliott/Documents/Visual Studio 2015/Projects/OpenGLEngine/Assets/Shaders/FragShader.frag", GL_FRAGMENT_SHADER);

	mShader->BindAttributeLocation(0, "position");
	//mShader->BindAttributeLocation(1, "vertexColour");

	glBindFragDataLocation(mShader->GetProgramHandle(), 0, "colour");

	mShader->LinkShaderProgram();

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
	
	
	GLuint colourBuffer;
	glGenBuffers(1, &colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	//ALL RENDERING IS DONE HERE
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float aspectRatio = _mWindowWidth / _mWindowHeight;
		camera->SetProjectionMatrix(90.0f, aspectRatio, 1.0f, 1000.0f);
		transform.Translate(Vector4(0.0, 0.0, -10.0));
		mShader->ActivateShaderProgram();
		glBindVertexArray(gVAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
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

