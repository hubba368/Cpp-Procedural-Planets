#pragma once

#include <iostream>
#include "OGLTextureBase.h"

class OGLTextureLoader
{
	private:

	public:
						OGLTextureLoader();
	virtual				~OGLTextureLoader();

	unsigned int		mSyshandle;
	unsigned int		mApphandle;

	virtual void		CreateTextureFromFile(std::string filePath);
	
	//TODO:
	//set texture as render target
	//set texture as depth target

};

