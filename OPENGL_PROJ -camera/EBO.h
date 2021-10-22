#pragma once
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
class EBO {
public:
	GLuint ID;


	EBO(GLuint* indices, GLsizeiptr size);//sizeiptr =byte
	void Bind();
	void Unbind();
	void Delete();
};