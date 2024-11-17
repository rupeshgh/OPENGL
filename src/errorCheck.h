#pragma once
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
#include<iostream>

#if defined(_WIN32) || defined(_WIN64)
	// Windows specific
	#define ASSERT(x) if (!(x)) __debugbreak();
#elif defined(__APPLE__)
	// macOS specific
	#define ASSERT(x) if (!(x)) __builtin_trap();
#else
	// Default for other platforms
	#define ASSERT(x) if (!(x)) abort();
#endif

#define glCall(x)  GLClearError();\
x;\
ASSERT(glLogCall(#x,__FILE__,__LINE__))
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