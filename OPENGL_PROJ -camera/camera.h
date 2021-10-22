#pragma once
#include<GL/glew.h> 
#include<GLFW/glfw3.h>
#include<iostream>
#include"errorCheck.h"
#include"texture.h"
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<gtx/vector_angle.hpp>
#include<gtx/rotate_vector.hpp>

#include"shaderClass.h"
#include "Timestep.h"

class camera {

public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);// moving  1.0f in z 
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width, height;
	bool firstClick = true;
	float speed = 0.1f;
	float sensitivity = 100.f;


	camera(int width, int height, glm::vec3 position);
	void matrix(float FOVdeg, float nearPlane, float farPlane, shader& shaderProgram, const char* uniform);
	void inputs(GLFWwindow* window, Timestep ts);
};