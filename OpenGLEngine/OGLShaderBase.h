#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <vector>

/**
* Class which handles loading
* of all shader types, reduces size
* of a single main shader handling source file.
*/

class OGLShaderBase
{
	private:
		GLuint				mShaderSystemHandle;	//system handle assigned by openGL
	public:
							OGLShaderBase();
		virtual				~OGLShaderBase();

		/// Loads and compiles shader GLSL source code from a text file
		GLuint		LoadShaderFromTextFile(std::string filePath, GLenum shaderType);
		
		/// Retrieves the shader handle.
		inline GLuint		GetShaderHandle() 
		{
			return mShaderSystemHandle;
		}
};

