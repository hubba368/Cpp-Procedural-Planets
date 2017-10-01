#include "OGLShaderLoader.h"
#include "OGLShaderBase.h"

OGLShaderLoader::OGLShaderLoader()
{
	//Set to 0xFFFFFFFF to initialise
	mSystemHandle = 4294967295;
}


OGLShaderLoader::~OGLShaderLoader()
{
	//Delete shaders and program
}

void OGLShaderLoader::LoadShaderProgram()
{
	//true if there is already a program created
	if (mSystemHandle != 0xffffffff) 
	{
		return;
	}

	//Create 'shader object' program
	mSystemHandle = glCreateProgram();
}


void OGLShaderLoader::AttachAndBuildFromSource(string filePath, GLenum shaderType) 
{
	//Attach the shader code to the shader object program
	GLuint programID = mSystemHandle;

	//create new shader code object
	OGLShaderBase *shader = new OGLShaderBase();

	//check that code is found and compiled properly
	if (shader->LoadShaderFromTextFile(filePath, shaderType)) 
	{
		//attach vertex/frag/geometry shader to program
		printf("Shader successfully attached.\n");
		glAttachShader(mSystemHandle, shader->GetShaderHandle());
	}
	else 
	{
		//delete shader object
		printf("Shader attachment unsuccessful.\n");
		delete shader;
	}
}


void OGLShaderLoader::LinkShaderProgram() 
{
	//Link the compiled shaders to the shader program
	GLint isLinked = 0;

	glLinkProgram(mSystemHandle);
	glGetProgramiv(mSystemHandle, GL_LINK_STATUS, &isLinked);

	if (isLinked > 0)
	{
		//Retrieve openGL generated error log
		printf("Could not link shader.\n");

		int maxLength = 0;
		glGetProgramiv(mSystemHandle, GL_INFO_LOG_LENGTH, &maxLength);

		char *log = new char[isLinked];
		glGetProgramInfoLog(mSystemHandle, maxLength, &maxLength, log);
		printf("program log %s\n", log);

	}
	else 
	{
		printf("Shader successfully linked.\n");
		/*int maxLength = 0;
		glGetProgramiv(mSystemHandle, GL_INFO_LOG_LENGTH, &maxLength);

		char *log = new char[isLinked];
		glGetProgramInfoLog(mSystemHandle, maxLength, &maxLength, log);
		printf("program log %s\n", log);*/
	}
}


void OGLShaderLoader::ActivateShaderProgram() 
{
	glUseProgram(mSystemHandle);
}


void OGLShaderLoader::DeactivateShaderProgram() 
{
	glUseProgram(0);
}


void OGLShaderLoader::BindAttributeLocation(int index, const char *paramName) 
{
	glBindAttribLocation(mSystemHandle, index, paramName);
}

