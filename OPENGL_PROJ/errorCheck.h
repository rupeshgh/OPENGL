#pragma once
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
#include<iostream>

#define ASSERT(x) if(!x) __debugbreak();

#define glCall(x)  GLClearError();\
x;\
ASSERT(glLogCall(#x,__FILE__,__LINE__))



// __debugbreak(); compiler instrinsic
// \ ignores new line char
// NO SPACE after  \

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {

		std::cout << "[opengl error](" << error << ")" << "  Function::" << function << "  FIlE LOC: " << file << " " << " LINE:" << line << std::endl;
		return false;
	}
	return true;
}