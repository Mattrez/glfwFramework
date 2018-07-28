project(glfwFramework)
cmake_minimum_required(VERSION 3.3)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/bin
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/objects
    ${PROJECT_SOURCE_DIR}/renderable
    ${PROJECT_SOURCE_DIR}/utils)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} \
	-Wall \
	-Wextra \
	-pedantic")

set (OpenGL_GL_PREFERENCE GLVND)

find_package(GLEW  REQUIRED)
find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIRS})

add_subdirectory(utils)
add_subdirectory(renderable)
add_subdirectory(objects)
add_subdirectory(bin)

add_executable(exec main.cc)

target_link_libraries(exec bin utils renderable objects ${GLFWLIB} glfw GL GLEW freetype)
