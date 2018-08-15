#pragma once
#include "OGLShaderLoader.h"
#include "Matrix4x4.h"
#include "MainCamera.h"
#include "OGLTextureLoader.h"

GLFWwindow			*window;

/**
* Class which is main entry point for
* the program.
*/
class OGWindow
{
private:

	OGLShaderLoader		*mShader;	//openGL shader program

	Matrix4x4			modelview;
	Matrix4x4			projection;

	int					_mWindowWidth;
	int					_mWindowHeight;

	int mUniformTexSampler;
	int mUniformTexture;

	/// Initialises shaders and shader program.
	void				InitialiseShaders();

	/// Main Render loop of the program.
	void				RenderLoop();

	/// Initialise the main camera.
	void				InitCamera();

	/// Sets all camera related matrices and uniforms.
	void				SetAllMatrices();

	/// Handles camera movement via keyboard presses.
	void				CameraKeyboardMovement(GLFWwindow *window);

protected:
	unsigned int test;

public:

	OGWindow();
	~OGWindow();

	/////TESTING/////
	OGLTextureLoader *m_texture;
	OGLTextureBase	 *m_tex;
	/////TESTING/////

	MainCamera			*camera;
	Matrix4x4			transform;

	/// Initialises GLFW and GLEW, and window context.
	void				StartInitialState();




};

