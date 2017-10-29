#pragma once

#include <iostream>

class OGLTextureBase
{
	private:

	public:
	//OGLTextureBase();
	//~OGLTextureBase();

		/// holds the first 6 required bytes of the file.
		unsigned char		initialHeader[6];

		/// file header used to determine file type.
		unsigned char		fileHeader[12];

		/// uncompressed TGA header
		unsigned char		uncompressedTGASignature[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };

		/// compressed TGA header
		//unsigned char		compressedTGASignature[12] = { 0,0,10,0,0,0,0,0,0,0,0,0 };

		/// Loads an uncompressed TGA file.
		bool				LoadUncompressedTGA(FILE* pf, unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels);
		
		//TODO
		//bool				LoadCompressedTGA(FILE* pf, unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels);
		
		/// Loads a TGA file to be used as a texture.
		bool				LoadTGA(const char* filePath, unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels);
};

