project(glfwFramework)
cmake_minimum_required(VERSION 3.3)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/frame
    ${PROJECT_SOURCE_DIR}/src/objects
    ${PROJECT_SOURCE_DIR}/src/renderable
    ${PROJECT_SOURCE_DIR}/src/utils)

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

add_subdirectory(src/utils)
add_subdirectory(src/renderable)
add_subdirectory(src/objects)
add_subdirectory(src/frame)

add_executable(exec src/main.cc)

target_link_libraries(exec frame objects renderable utils ${GLFWLIB} glfw GL GLEW freetype)
