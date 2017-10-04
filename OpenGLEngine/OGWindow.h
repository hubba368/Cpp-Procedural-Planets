#pragma once
#include "OGLShaderLoader.h"
#include "Matrix4x4.h"

GLFWwindow			*window;

/**
* Class which is main entry point for
* the program.
*/
class OGWindow
{
public:
	OGWindow();
	~OGWindow();

	/// Initialises GLFW and GLEW, and window context.
	void				StartInitialState();

private:
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	OGLShaderLoader		*mShader;	//openGL shader program

	/// Initialises shaders and shader program.
	void				InitialiseShaders();

	/// Main Render loop of the program.
	void				RenderLoop();


protected:
	unsigned int test;


};

