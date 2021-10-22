#include"VAO.h"
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
#include"errorCheck.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);

}

void VAO::linkAttrib(VBO VBO, GLuint layout, GLenum numComponents,GLenum type, GLboolean normalized, GLsizeiptr stride, void* offset){
	
	VBO.Bind();
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout,numComponents ,type, normalized, stride, offset);
	VBO.Unbind();
}


void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}
void VAO::Delete(){
	glDeleteVertexArrays(1, &ID);
}