#include "OGLTextureLoader.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

OGLTextureLoader::OGLTextureLoader()
{
	mSyshandle = -1;
	mApphandle = -1;
}

OGLTextureLoader::~OGLTextureLoader()
{
	FreeTexture();
}


void OGLTextureLoader::CreateTextureFromFile(std::string filePath)
{
	if (mSyshandle != -1 || mApphandle != -1) 
	{
		//check if a texture has already been created
		return;
	}

	//try and load the image file
	OGLTexture *tex = new OGLTexture();
	unsigned char* buffer = NULL;
	int width;
	int height;
	int bpp;
	int nChannels;

	if (OGLTextureBase::LoadTGA(filePath.c_str(), tex) != true) 
	{
		printf("Error loading TGA file.\n");
		return;
	}

	printf("NO ERRORS");
	//texture now ready for OpenGL usage
	//set the texture paramters for the current active texture unit
	glGenTextures(1, &mSyshandle);
	glBindTexture(GL_TEXTURE_2D, mSyshandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set the type of the image - 24 bit = rgb image, 32 bit = rgba image
	if (tex->OGLTextureObj.bpp == 24) 
	{
		//24 bit
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex->OGLTextureObj.width, tex->OGLTextureObj.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->OGLTextureObj.imageData);
	}
	else if (tex->OGLTextureObj.bpp == 32)
	{
		//32 bit
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex->OGLTextureObj.width, tex->OGLTextureObj.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->OGLTextureObj.imageData);
	}

	free(buffer);
}

void OGLTextureLoader::FreeTexture()
{
	if (mSyshandle != -1) 
	{
		//delete texture
		mSyshandle = -1;
		mApphandle = -1;
		glDeleteTextures(1, &mSyshandle);
	}
}
