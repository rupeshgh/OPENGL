#include"texture.h"
#include "stb_image.h"
#include"errorCheck.h"

texture::texture(const std::string& path) :filepath(path), localBuffer(nullptr), width(0), height(0),BPP(0),iD(0)
{
	stbi_set_flip_vertically_on_load(1);
	// opengl 0,0 at bootom left but pngor img files load from top
	
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);  //4=RGBA
	// texture data stored insida localBuffer	
	//std::cout<<	stbi_failure_reason();
	if (!localBuffer) {

		std::cout << "no tex";
	}
	glGenTextures(1, &iD);
	glBindBuffer(GL_TEXTURE_2D, iD);


	//gl linear for linear sampling...MAG  =magnification filter

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);



	//RGBA8  8 =bits in a channel
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}
		
}

texture::~texture() {

	glDeleteTextures(1,&iD);
}

void texture::Bind(unsigned int slot)  {
	glActiveTexture(GL_TEXTURE0 + slot); //32 texture for window
	glBindTexture(GL_TEXTURE_2D, iD);
}

void texture::unBind()const {
	glBindTexture(GL_TEXTURE_2D, 0);
}