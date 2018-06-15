#include <iostream> // for cout

#include "utils/GLIncludes.h"

#include "utils/config.h"
#include "renderable/renderer.h"
#include "renderable/vao.h"
#include "renderable/vbo.h"
#include "renderable/layoutElement.h"
#include "renderable/shader.h"

int main()
{
	/* GLFW window handle for loading openGL */
	GLFWwindow* window;

	Config config;

	/* Initializaing GLFW */
	if (!glfwInit())
	{
		std::cout << "[ERROR]: Failed to load GLFW\n";
		return -1;
	}

	/* Pointing the window pointer to a window object */ 
	window = glfwCreateWindow(config.width, config.height, config.windowName, NULL, NULL);

	/* Basic error checking if the window was created succefully */
	if (window == NULL)
	{
		std::cout << "[ERROR]: Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Making the window poniter as the current openGL context */
	glfwMakeContextCurrent(window);

	/* Error checking for initializaing GLEW */ 
	if(glewInit())
	{
		std::cout << "[ERROR]: Failed to load GLEW\n";
		return -1;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	Shader testShader = Shader("../sVertex.vert", "../sFragment.frag");
	
	float verties[] =
	{
		-0.5f, -0.5f, 1.0f, 0.0f, 0.6f, 0.3f,
		 0.5f,  0.5f, 1.0f, 0.0f, 0.6f, 0.3f,
		-0.5f,  0.5f, 1.0f, 0.0f, 0.6f, 0.3f,

		-0.5f, -0.5f, 1.0f, 1.0f, 0.6f, 0.3f,
		 0.5f, -0.5f, 1.0f, 1.0f, 0.6f, 0.3f,
		 0.5f,  0.5f, 1.0f, 1.0f, 0.6f, 0.3f,
	};

	Renderer renderer;
	VBO vbo = VBO(verties, sizeof(verties));

	VAO vao;

	/* Positions */
	vao.addToElements(3, GL_FLOAT, GL_FALSE);
	/* Color */
	vao.addToElements(3, GL_FLOAT, GL_FALSE);

	vao.populateLayouts(vbo);

	while(!glfwWindowShouldClose(window))
	{
		/* Clearing the screen with set color */
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.draw(vao, testShader);
//		testShader.use();
//		vao.bind();
//
//		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* Swaping the current buffer that is on the screen with a new one */
		glfwSwapBuffers(window);

		/* Polling the events that happend */
		glfwPollEvents();
	}

	/* Cleaning GLFW up */
	glfwTerminate();
	return 0;
}
