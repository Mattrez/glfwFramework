project(glfwFramework)
cmake_minimum_required(VERSION 3.3)

include_directories(".")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(glfwFramework main.cc)

target_link_libraries(glfwFramework glfw GL GLEW)
