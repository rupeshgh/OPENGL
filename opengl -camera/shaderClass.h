#pragma once
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include <string> 
#include<sstream> 



class shader {
	public:
		GLuint ID;
		shader(const char* vertexFile, const char* shaderFIle);
		shader(const char* shaderfile);
		
		void Activate();
		void Delete();

private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);


};