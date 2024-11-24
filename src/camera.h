#pragma once
#include "errorCheck.h"
#include "texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

#include "Timestep.h"
#include "shaderClass.h"

class camera {

public:
  glm::vec3 Position;
  glm::vec3 Orientation =
      glm::vec3(0.0f, 0.0f, -1.0f); // moving  camera in z by 1.0f
  glm::vec3 Up = glm::vec3(
      0.0f, 1.0f, 0.0f); // it means y axis is in upward or vertical direction .

  int width, height;
  bool firstClick = true;
  float speed = 0.1f;
  float sensitivity = 100.f;

  camera(int width, int height, glm::vec3 position);
  void matrix(float FOVdeg, float nearPlane, float farPlane,
              shader &shaderProgram, const char *uniform);
  void inputs(GLFWwindow *window, Timestep ts);
};
