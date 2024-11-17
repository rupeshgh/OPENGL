cmake_minimum_required(VERSION 3.10)
project(OpenGL_SFML_Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files from directories
file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add executable and link source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Find external packages like OpenGL and SFML
find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)# Add GLEW if needed

# Link the libraries to your executable
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} sfml-system sfml-window sfml-graphics  ${GLEW_LIBRARIES} glfw)
