#pragma once
#ifndef __OGLTEXTURE_H__
#define __OGLTEXTURE_H__

#include "GLEW/glew.h"
#include <windows.h>
#include <stdio.h>

class OGLTexture
{

private:
	
	// Texture struct that acts at the data to be utilised by OpenGL.
	typedef struct
	{
		GLubyte *imageData;
		GLuint bpp; //bits per pixel
		GLuint width;
		GLuint height;
		GLuint texID;
		GLuint colourType;
	} Texture;

	// TGA file format specific structs
	typedef struct
	{
		GLubyte header[12];
	} Texture_TGA_Header;

	typedef struct
	{
		unsigned char header[6];
		GLuint bytesPerPixel;
		GLuint imageSize;
		GLuint width;
		GLuint height;
		GLuint colourType;
		GLuint bitsPerPixel;
	} Texture_TGA;
	//


public:

	// OpenGL texture 
	Texture OGLTextureObj;

	// TGA file format
	Texture_TGA_Header tgaHeader;
	Texture_TGA tgaTexture;
	GLubyte uncompressedTGASignature[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	GLubyte compressedTGASignature[12] = { 0,0,10,0,0,0,0,0,0,0,0,0 };
};

#endif