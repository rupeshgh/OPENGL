#pragma once
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
class VBO {
	public:
		GLuint ID;


	VBO(GLfloat* vertices, GLsizeiptr size);//sizeiptr =byte
	void Bind();
	void Unbind();
	void Delete();
};