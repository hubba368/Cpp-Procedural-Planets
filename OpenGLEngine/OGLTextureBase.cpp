#include "OGLTextureBase.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

bool OGLTextureBase::LoadUncompressedTGA(FILE* pFile, const char *fileName, OGLTexture *texture)
{
	// check the first 6 bytes of the header 
	if (fread(texture->tgaTexture.header, sizeof(texture->tgaTexture.header), 1, pFile) == 0)
	{
		printf("Error reading header of uncompressed tga file.\n");
		return false;
	}

	// calculate image width and height
	//texture->OGLTextureObj.width = 45;
	GLuint width = (texture->tgaTexture.header[1]<<8) | texture->tgaTexture.header[0];
	GLuint height = (texture->tgaTexture.header[3]<<8) | texture->tgaTexture.header[2];

	// calculate bits per pixel
	GLuint bpp = texture->tgaTexture.header[4];

	// copy previous calculated values into TGA specific struct
	texture->tgaTexture.width = width;
	texture->tgaTexture.height = height;
	texture->tgaTexture.bitsPerPixel = bpp;

	// check if dimensions are atleast 1 pixel, and bpp is 24 OR 32
	// essentially checking that the file contains actual image data
	if((width <= 0) || (height <= 0) 
		|| ((bpp != 24) && (bpp != 32)))
	{
		printf("Error with pixel dimensions of image file.\n");
		return false;
	}
	
	// check the colour type of the image file (RGB or RGBA)
	if (bpp == 24) 
	{
		texture->OGLTextureObj.colourType = GL_RGB;
	}
	else if(bpp == 32)
	{
		texture->OGLTextureObj.colourType = GL_RGBA;
	}

	// calculate bytes per pixel
	texture->tgaTexture.bytesPerPixel = (bpp) >> 3;
	// calc memory space needed for the image
	texture->tgaTexture.imageSize = (texture->tgaTexture.bytesPerPixel) * (texture->tgaTexture.width) * (texture->tgaTexture.height);
	texture->OGLTextureObj.imageData = (GLubyte*)malloc(texture->tgaTexture.imageSize);

	if (texture->OGLTextureObj.imageData == NULL)
	{
		printf("Error allocating memory for image data.\n");
		return false;
	}

	// try and read all the data we just stored
	if (fread(texture->OGLTextureObj.imageData, 1, texture->tgaTexture.imageSize, pFile) != texture->tgaTexture.imageSize)
	{
		delete[](texture->OGLTextureObj.imageData);
		texture->OGLTextureObj.imageData = NULL;
		return false;
	}

	// TGA files are stored in reverse order to what OpenGL requires, so we must reverse it.
	for (int charSwap = 0; charSwap < (int)texture->tgaTexture.imageSize; charSwap += (texture->tgaTexture.bytesPerPixel))
	{
		// swap the 1st and 3rd bytes in every pixel
		// you can XOR each byte 3 times to do this
		(texture->OGLTextureObj.imageData)[charSwap] ^= (texture->OGLTextureObj.imageData)[charSwap + 2] ^=
			(texture->OGLTextureObj.imageData)[charSwap] ^= (texture->OGLTextureObj.imageData)[charSwap + 2];
	}

	// copy values into OpenGL texture struct
	texture->OGLTextureObj.width = width;
	texture->OGLTextureObj.height = height;
	texture->OGLTextureObj.bpp = bpp;
	texture->OGLTextureObj.colourType = texture->tgaTexture.colourType;

	fclose(pFile);
	return true;
}


bool OGLTextureBase::LoadTGA(const char* filePath, OGLTexture *texture)
{
	// attempt to open the file
	FILE* pFile = NULL;
	bool result = true;
	errno_t err = 0;

	err = fopen_s(&pFile, filePath, "rb");

	if (err)
	{
		printf("Error opening image file: %s\n", filePath);
		return false;
	}

	if (fread(&texture->tgaHeader,1, sizeof(texture->tgaHeader), pFile) == 0) 
	{
		printf("Error attempting to read image file.\n");
		return false;
	}

	//check the header file to see if it is uncompressed
	if (memcmp(texture->uncompressedTGASignature, &texture->tgaHeader, sizeof(texture->tgaHeader)) == 0)
	{
		printf("Loading uncompressed tga file.\n");
		result = LoadUncompressedTGA(pFile, filePath, texture);
	}
	else if(memcmp(texture->compressedTGASignature, &texture->tgaHeader, sizeof(texture->tgaHeader)) == 0)
	{
		// load compressed tga file
		printf("Loading compressed tga file.\n");
		//result = LoadCompressedTGA(pFile, filePath, texture);
	}
	else
	{
		//unrecognised header signature 
		printf("Error: unrecognised header signature on image file.\n");
		fclose(pFile);
		return false;
	}

	fclose(pFile);

	return result;
}
