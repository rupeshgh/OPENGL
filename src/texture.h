#pragma once
#include "shaderClass.h"


class texture {
private:
	unsigned int iD;
	std::string filepath;

	unsigned char*  localBuffer;

	int width, height, BPP;		//Bits per pixel

public:
	texture(const std::string& path);
	~texture();

	void Bind(unsigned int slot = 0) ;
	void unBind() const;


	inline int getWidth() const { return width; }
	inline int getHeight()const { return height; }
	inline unsigned int getID()const { return iD; }


};