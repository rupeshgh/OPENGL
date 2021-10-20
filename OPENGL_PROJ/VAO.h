#pragma once
#include"VBO.h"
#include<GL/glew.h> 
#include<GLFW/glfw3.h>

class VAO {
public:
	GLuint ID;
	VAO();

	void linkAttrib(VBO VBO, GLuint layout, GLenum numComponents,GLenum type, GLboolean normalized,GLsizeiptr stride,void* offset);
	void Bind();
	void Unbind();
	void Delete();

};