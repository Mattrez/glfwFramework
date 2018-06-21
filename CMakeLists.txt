project(glfwFramework)
cmake_minimum_required(VERSION 3.3)

include_directories(".")
include_directories("includes/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW  REQUIRED)

add_subdirectory(utils)
add_subdirectory(renderable)
add_subdirectory(objects)

add_executable(glfwFramework main.cc)

target_link_libraries(glfwFramework utils renderable objects ${GLFWLIB} glfw GL GLEW)
