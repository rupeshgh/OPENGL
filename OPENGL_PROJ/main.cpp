#include<GL/glew.h> 
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include <string>  //for getline
#include<sstream> //string stream

#include"shaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"

#include"errorCheck.h"

//#include"texture.h"

int main()
{
	GLFWwindow* window;



	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	


	window = glfwCreateWindow(800, 800, "YoLo", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK)   //glewinit only after valid window context
		std::cout << "glew not ok" << std::endl;



	GLfloat vertices[] =
	{	//cordinates		//colors			//tex cordinate			
		-0.5f,  -0.5f,		1.0f, 0.0f, 0.0f,  0.0f,0.0f,
		-0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f,1.0f,
		 0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,1.0f,
		 0.5f,   -0.5f,		1.0f, 0.0f, 1.0f,	1.0f,0.0f
	};

	// Indices for vertices order
	GLuint indexes[] =
	{
		0, 2, 1,
		 0, 3,	2
	};
	
	//shader shaderProgram("default.vert", "default.frag");
	//use this if you have vertex and fragment shader on different file

	shader shaderProgram("Basic.shader");
	//use this if you have vertex and fragment shader on same file



	VAO VAO1;
	VAO1.Bind();
	

	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indexes, sizeof(indexes));

	VAO1.linkAttrib(VBO1, 0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7,(void*) (sizeof(float)*2));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 5));

	
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	


	

	static float Scale = 0.0f;
	static float Delta = 0.0005f;


	
	//shaderProgram.Activate();


	GLint ScaleLocation = glGetUniformLocation(shaderProgram.ID, "gScale");



	VAO1.Bind();

	//std::string path = "C:\\Users\\rupesh\\Desktop\\images";

	//texture t("C:\\Users\\rupesh\\Desktop\\images\\tick.png");
	//t.Bind();

	//GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	////shaderProgram.Activate();
	//glUniform1i(tex0Uni, 0);



	//t.unBind();






	
	 

	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		
		shaderProgram.Activate();


		//t.Bind();
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		
		
		

		Scale += Delta;
		if((Scale >= 1.0f)|| (Scale <= -1.0f)){
			Delta *=-1.0f;
		}

		glUniform1f(ScaleLocation, Scale);
	
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		

		glfwSwapBuffers(window);

	
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	shaderProgram.Delete();

	glfwTerminate();

	return 0;
}



