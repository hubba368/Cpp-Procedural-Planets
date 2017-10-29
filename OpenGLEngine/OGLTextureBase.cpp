#include "OGLTextureBase.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

bool OGLTextureBase::LoadUncompressedTGA(FILE* pf, unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels)
{
	if (fread(initialHeader, sizeof(initialHeader), 1, pf) == 0)
	{
		//check the first 6 bytes of the file, return false if there is error
		return false;
	}

	//calculate image width and height
	*sizeX = (int)initialHeader[1] * 256 + initialHeader[0];
	*sizeY = (int)initialHeader[3] * 256 + initialHeader[2];
	//calculate bits per pixel
	*bpp = initialHeader[4];

	//check if dimensions are atleast 1 pixel, and bpp is 24 OR 32
	//essentially checking that the file contains actual image data
	if((*sizeX <= 0) || (*sizeY <= 0) || ((*bpp != 24) && (*bpp != 32)))
	{
		return false;
	}
	
	//calculate bytes per pixel
	*nChannels = (*bpp) / 8;
	//calc memory space needed for the image
	int imageSize = (*sizeX) * (*sizeY) * (*nChannels);
	*buffer = (unsigned char*)malloc(imageSize);

	if (buffer == NULL) 
	{
		return false;
	}

	//try and read all the data we just stored
	if (fread(*buffer, 1, imageSize, pf) != imageSize) 
	{
		delete[](*buffer);
		*buffer = NULL;
		return false;
	}

	//TGA files are stored in reverse order so we must reverse it for OpenGLs sake
	for (int charSwap = 0; charSwap < imageSize; charSwap += (*nChannels)) 
	{
		//swap the 1st and 3rd bytes in every pixel
		//you can XOR each byte 3 times to do this
		(*buffer)[charSwap] ^= (*buffer)[charSwap + 2] ^=
			(*buffer)[charSwap] ^= (*buffer)[charSwap + 2];
	}

	return true;
}


bool OGLTextureBase::LoadTGA(const char* filePath, unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels)
{
	FILE* pFile = NULL;
	bool result = true;
	*buffer = NULL;
	errno_t err = 0;

	//try to open the file
	err = fopen_s(&pFile, filePath, "rb");

	if (err) 
	{
		printf("Error opening image file: %s\n", filePath);
		return false;
	}

	if (!pFile) 
	{
		//cannot find the file to load
		return false;
	}

	//check the header file to see if it is uncompressed
	if (memcmp(uncompressedTGASignature, initialHeader, sizeof(initialHeader)) == 0)
	{
		result = LoadUncompressedTGA(pFile, buffer, sizeX, sizeY, bpp, nChannels);
	}
	else
	{
		//unrecognised header signature 
		fclose(pFile);
		return false;
	}

	fclose(pFile);

	return result;
}
