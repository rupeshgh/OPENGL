#include "camera.h"
camera::camera(int width, int height, glm::vec3 position) {
  camera::width = width;
  camera::height = height;
  Position = position;
}
void camera::matrix(float FOVdeg, float nearPlane, float farPlane,
                    shader &shader, const char *camMatrix_uniform) {

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  view = glm::lookAt(Position, Position + Orientation, Up);
  projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height),
                                nearPlane, farPlane);
  unsigned int camLocation = glGetUniformLocation(shader.ID, camMatrix_uniform);
  glUniformMatrix4fv(camLocation, 1, GL_FALSE,
                     glm::value_ptr(projection * view));

  // pos+ orientation ..to distance camera (viewpoint) from view frustum..
  // First parameter(camera pos)  second (point to look) ..
  // Also we add orientation to poisiton when we give inputs to move camera
  // atm w and s key move world to +-z by 1 if  glm::vec3 Orientation =
  // glm::vec3(0.0f, 0.0f, -1.0f); to move left right we need to get move world
  // along x axis..for that perform corss product of orientation and UP and
  // normalize it.
}

void camera::inputs(GLFWwindow *window, Timestep ts) {
  float dt = ts.getSeconds();
  speed = dt * speed * 10;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    Position += speed * Orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    Position += speed * -glm::normalize(glm::cross(Orientation, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    Position += speed * -Orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    Position += speed * glm::normalize(glm::cross(Orientation, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    Position += speed * Up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    Position += speed * -Up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed = 0.4f;
  } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    speed = 0.1f;
  }

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    // Hides mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Prevents camera from jumping on the first click
    if (firstClick) {
      glfwSetCursorPos(window, (width / 2), (height / 2));
      firstClick = false;
    }

    // Stores the coordinates of the cursor
    double mouseX;
    double mouseY;
    // Fetches the coordinates of the cursor
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Normalizes and shifts the coordinates of the cursor such that they begin
    // in the middle of the screen and then "transforms" them into degrees
    float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
    float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

    // Calculates upcoming vertical change in the Orientation
    glm::vec3 newOrientation =
        glm::rotate(Orientation, glm::radians(-rotX),
                    glm::normalize(glm::cross(Orientation, Up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <=
        glm::radians(85.0f)) {
      Orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    // Sets mouse cursor to the middle of the screen so that it doesn't end up
    // roaming around
    glfwSetCursorPos(window, (width / 2), (height / 2));
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    // Unhides cursor since camera is not looking around anymore
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // Makes sure the next time the camera looks around it doesn't jump
    firstClick = true;
  }
}
