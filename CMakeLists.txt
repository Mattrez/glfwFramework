project(glfwFramework)
cmake_minimum_required(VERSION 3.3)

include_directories(".")
include_directories("include/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

set(GLFWLIB ${CMAKE_SOURCE_DIR}/libs/GLFW/libglfw3.a)
set(GLEWLIB ${CMAKE_SOURCE_DIR}/libs/GLEW/libglew32.a)

add_subdirectory(utils)
add_subdirectory(renderable)
add_subdirectory(objects)

add_executable(glfwFramework main.cc)

target_link_libraries(glfwFramework utils renderable objects ${GLFWLIB} -lopengl32 ${CMAKE_SOURCE_DIR}/libs/GLEW/libglew32.a)
