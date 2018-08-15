#pragma once

#include <iostream>
#include "OGLTexture_TGA.h"
#include "OGLTexture.h"

class OGLTextureBase
{
	private:
		
		OGLTexture *mTgaHeader;

	public:
	//OGLTextureBase();
	//~OGLTextureBase();

	// TODO: CHANGE THIS SO IT IS NOT DESIGNED JUST FOR TGA FILES - FILE AGNOSTIC.
	// TODO: RENAME THIS TO OGLTEXTUREPARSER

	/// Loads an uncompressed TGA file.
	static bool				LoadUncompressedTGA(FILE* pf, const char *fileName, OGLTexture *texture);
	//TODO
	//static bool				LoadCompressedTGA(FILE* pf, const char *fileName, OGLTexture *texture);		
	/// Loads a TGA file to be used as a texture.
	static bool				LoadTGA(const char* filePath, OGLTexture *texture);
};

