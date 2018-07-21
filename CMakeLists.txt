project(glfwFramework)
cmake_minimum_required(VERSION 3.3)

include_directories(".")
include_directories("includes/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} \
	-Wall \
	-Wextra \
	-pedantic")

set (OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW  REQUIRED)

add_subdirectory(utils)
add_subdirectory(renderable)
add_subdirectory(objects)
add_subdirectory(bin)

add_executable(exec main.cc)

target_link_libraries(exec bin utils renderable objects ${GLFWLIB} glfw GL GLEW)
