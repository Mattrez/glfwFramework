#include <iostream> // for cout

#include "utils/GLIncludes.h"

#include "utils/config.h"
#include "renderable/renderer.h"
#include "renderable/vao.h"
#include "renderable/vbo.h"
#include "renderable/layoutElement.h"
#include "renderable/shader.h"
#include "renderable/ebo.h"
#include "renderable/camera.h"
#include "objects/rObject.h"

auto conf = Config::get();

float lastX = 400.0f;
float lastY = 400.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	/* GLFW window handle for loading openGL */
	GLFWwindow* window;

	/* Initializaing GLFW */
	if (!glfwInit())
	{
		std::cout << "[ERROR]: Failed to load GLFW\n";
		return -1;
	}

	/* Creating and getting the instance of the config Singeltonn */
	auto conf = Config::get();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Pointing the window pointer to a window object */ 
	window = glfwCreateWindow(conf.width, conf.height, conf.windowName, NULL, NULL);

	/* Basic error checking if the window was created succefully */
	if (window == NULL)
	{
		std::cout << "[ERROR]: Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
   
   /* Setting of all the callbacks */
   glfwSetCursorPosCallback(window, mouse_callback);

	/* Making the window poniter as the current openGL context */
	glfwMakeContextCurrent(window);

   /* Telling OpenGL to take control over our mouse */
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Error checking for initializaing GLEW */ 
	if(glewInit())
	{
		std::cout << "[ERROR]: Failed to load GLEW\n";
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glEnable(GL_DEPTH_TEST);
	
	float verties[] =
	{
		 0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, //V0
		 0.5f, -0.5f, 0.5f, 0.3f, 0.6f, 1.0f, //V1
		-0.5f, -0.5f, 0.5f, 0.0f, 0.6f, 0.3f, //V2
		-0.5f,  0.5f, 0.5f, 1.0f, 0.6f, 0.3f, //V3
	};
	
	unsigned int indi[] = 
	{
		0, 1, 3,
		1, 2, 3
	};

	Shader testShader = Shader("../shaders/sVertex.vert", "../shaders/sFragment.frag");
   Camera cam = Camera();
	VBO vbo = VBO(verties, sizeof(verties));
	VAO vao = VAO(indi, sizeof(indi));

	/* Positions */
	vao.addToElements(3, GL_FLOAT, GL_FALSE);
	/* Color */
	vao.addToElements(3, GL_FLOAT, GL_FALSE);

	vao.populateLayouts(vbo);

	/* Creating a renderableObject and filling it with data */
	rObject object;
	object.addVAO(vao);
   object.setPosition({ 0.0f, 0.0f, 0.0f });

   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	while(!glfwWindowShouldClose(window))
	{
      float currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      processInput(window);

		/* Clearing the screen with set color */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Draw call */	
		Renderer::draw(&object, testShader);

		/* Swaping the current buffer that is on the screen with a new one */
		glfwSwapBuffers(window);

		/* Polling the events that happend */
		glfwPollEvents();
	}

	/* Cleaning GLFW up */
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   if (firstMouse)
   {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
   }
   
   float xoffset = xpos - lastX;
   float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
   
   lastX = xpos;
   lastY = ypos;

   Camera& cam = Renderer::getCamera();
   cam.processMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

   Camera& cam = Renderer::getCamera();
   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cam.processKeyboard(Camera::Movement::FORWARD, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cam.processKeyboard(Camera::Movement::BACKWARD, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      cam.processKeyboard(Camera::Movement::LEFT, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      cam.processKeyboard(Camera::Movement::RIGHT, deltaTime);
}
