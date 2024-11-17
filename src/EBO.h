#pragma once
#include<GL/glew.h>

class EBO {
public:
	GLuint ID;


	EBO(GLuint* indices, GLsizeiptr size);//sizeiptr =byte
	void Bind();
	void Unbind();
	void Delete();
};