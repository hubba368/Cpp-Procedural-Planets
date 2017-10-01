#pragma once
#include "GLEW\include\glew.h"
#include "GLFW\include\GLFW\glfw3.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
* Representation of an OpenGL shader program.
* Handles attachment of fragment and vertex shaders,
* and various functions to allow for a complete
* shader program.
* Also allows setting of shader uniforms and attributes.
*/
class OGLShaderLoader
{
	private:
		unsigned int	mSystemHandle;		//Program ID for each type of shader assigned by OpenGL
		int				mShaderCount = 4;	//number of max shaders 
	public:
						OGLShaderLoader();
						~OGLShaderLoader();

	/// Returns the system handle of the program.
	inline unsigned int GetProgramHandle() 
	{
		return mSystemHandle;
	}

	/// Builds a Shader Program and assigns a system handle.
	void				LoadShaderProgram();

	/// Links Shader source code to a shader program.
	void				LinkShaderProgram();

	/// Activates the shader program for use.
	void				ActivateShaderProgram();

	/// Deactivates the shader program.
	void				DeactivateShaderProgram();

	//TODO: Delete Shader Program and shader method
	//void				DeleteShaderProgram();
	//void				DeleteShader();

	/// Loads shader code from a ShaderBase object, and attaches it to the program.
	void				AttachAndBuildFromSource(std::string filePath, GLenum shaderType);

	/// Binds an attribute location located in shader source code.
	void				BindAttributeLocation(int index, const char *paramName);

	

};

