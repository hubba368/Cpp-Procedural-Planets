#include "OGLShaderBase.h"

#define NULL_SYSTEM_HANDLE 0xffffffff

OGLShaderBase::OGLShaderBase()
{
	mShaderSystemHandle = NULL_SYSTEM_HANDLE;
}


OGLShaderBase::~OGLShaderBase()
{

}

GLuint OGLShaderBase::LoadShaderFromTextFile(std::string filePath, GLenum shaderType)
{
	//open file and get shader source
	GLhandleARB shaderID;
	std::string shaderCode;
	std::ifstream sourceFile(filePath.c_str());

	if (sourceFile)
	{
		//get the source - iterate through file until null character is reached
		shaderCode.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

		shaderID = glCreateShader(shaderType);
		mShaderSystemHandle = shaderID;

		//set and compile shader source code
		const GLchar *shader = shaderCode.c_str();
		glShaderSource(shaderID, 1, (const GLchar**)&shader, NULL);
		glCompileShader(shaderID);

		//compile the shader debugger
		GLint result = 0;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &result);

		//check if successful compile, output error log
		if (result > 0)
		{
			printf("Unable to load shader.\n");

			char *log = new char[result];
			int loglen = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &loglen);


			glGetShaderInfoLog(shaderID, result, &loglen, log);
			printf("Shader log %s\n", log);
			glDeleteShader(shaderID);
		}
		else
		{
			printf("Shader successfully compiled.\n", filePath);
		}
	}
	else
	{
		printf("Unable to open source file %s\n:", filePath.c_str());
	}

	return shaderID;
}

