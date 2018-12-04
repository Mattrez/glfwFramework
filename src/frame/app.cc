#include "app.h"

/* All of GLFW callbacks declaration */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);

App::App() :
	config("../res/config.ini")
{
	/* Initializaing GLFW */
	if (!glfwInit())
	{
		std::cout << "[ERROR]: Failed to load GLFW\n";
	}

	/* Settings for window so it's using the proper openGL version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Pointing the window pointer to a window object */
	pWindow = glfwCreateWindow(config.width, config.height, config.windowName.c_str(), NULL, NULL);

	/* Basic error checking if the window was created succefully */
	if (pWindow == NULL)
	{
		std::cout << "[ERROR]: Failed to create GLFW window\n";
		glfwTerminate();
	}

	/* Setting of all the callbacks */
	glfwSetWindowUserPointer(pWindow, this);
	glfwSetCursorPosCallback(pWindow, mouse_callback);
	glfwSetKeyCallback(pWindow, key_callback);
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

	/* Making the window poniter as the current openGL context */
	glfwMakeContextCurrent(pWindow);

	/* Telling OpenGL to take control over our mouse */
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Error checking for initializaing GLEW */
	if (glewInit())
	{
		std::cout << "[ERROR]: Failed to load GLEW\n";
	}

	/* Settings for openGL */

	/* Background color */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Enabling Z-Buffer */
	glEnable(GL_DEPTH_TEST);

	/* Enabling transparency */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_CULL_FACE);

	pRenderer = new Renderer(config);

	float verties[] =
	{
		 0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //V0
		 0.5f, -0.5f, 0.5f, 0.3f, 0.6f, 1.0f, 1.0f, 0.0f, //V1
		-0.5f, -0.5f, 0.5f, 0.0f, 0.6f, 0.3f, 0.0f, 0.0f, //V2
		-0.5f,  0.5f, 0.5f, 1.0f, 0.6f, 0.3f, 0.0f, 1.0f, //V3
	};

	unsigned int indi[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	unsigned int textIndi[] =
	{
		0, 1, 3,
		0, 3, 2,
	};

	auto& rMA = ModelAtlas::get();

	auto obj = std::make_unique <RenderData> (indi,
											  glm::vec2(sizeof(unsigned int), 6),
											  GL_STATIC_DRAW,
											  verties,
											  glm::vec2(sizeof(float), 4 * 8),
											  GL_STATIC_DRAW);

	rMA.addModel(ModelId::Basic,
				 std::move(obj));

	auto pBM = rMA.getModel(ModelId::Basic);

	/* Positions */
	pBM->getVAO().addToElements(3, GL_FLOAT, GL_FALSE);
	/* Color */
	pBM->getVAO().addToElements(3, GL_FLOAT, GL_FALSE);
	/* Texture Coordinates */
	pBM->getVAO().addToElements(2, GL_FLOAT, GL_FALSE);

	pBM->getVAO().populateLayouts(pBM->getVBO(), pBM->getEBO());

	obj = std::make_unique <RenderData> (textIndi,
										 glm::vec2(sizeof(unsigned int), 6),
										 GL_STATIC_DRAW,
										 nullptr,
										 glm::vec2(sizeof(float), 4 * 4),
										 GL_DYNAMIC_DRAW);
	
	rMA.addModel(ModelId::Text,
				 std::move(obj));

	pBM = rMA.getModel(ModelId::Text);

	pBM->getVAO().addToElements(4, GL_FLOAT, GL_FALSE);	

	pBM->getVAO().populateLayouts(pBM->getVBO(), pBM->getEBO());

	/* Basic Shader */
	ShaderAtlas::addShader(ShaderId::Basic,
								 config.shadersPath + "sVertex.vert",
								 config.shadersPath + "sFragment.frag");

	/* Basic Text Shader */
	ShaderAtlas::addShader(ShaderId::Text,
								 config.shadersPath + "sText.vert",
								 config.shadersPath + "sText.frag");

	TextureAtlas::addTexture(TextureId::Basic,
								   config.resPath + "logo.png",
								   true);

	FontAtlas::addFont(FontId::Basic, config.resPath + "arial.ttf");
}

App::~App()
{
	/* Cleaning GLFW up */
	glfwTerminate();
}

void App::tick()
{
		/* Clearing the screen with set color */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void App::mainLoop()
{
	while(!glfwWindowShouldClose(pWindow))
	{
		/* Calling the tick function that is changed by the end user */
		tick();
			
		/* Swaping the current buffer that is on the screen with a new one */
		glfwSwapBuffers(pWindow);

		/* Process the keyboard evenets */
		processKeyboard();

		/* Polling the events that happend */
		glfwPollEvents();
	}
}

void App::processKeyboard()
{
	Camera& cam = pRenderer->getCamera();
	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS) {
		cam.processKeyboard(Camera::Movement::FORWARD,
							timer.getDeltaTime());
	}
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS) {
		cam.processKeyboard(Camera::Movement::BACKWARD,
							timer.getDeltaTime());
	}
	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS) {
		cam.processKeyboard(Camera::Movement::LEFT,
							timer.getDeltaTime());
	}
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS) {
		cam.processKeyboard(Camera::Movement::RIGHT,
							timer.getDeltaTime());
	}
}

void mouse_callback(GLFWwindow* pWindow, double xpos, double ypos)
{
	App* pApp = static_cast <App*>(glfwGetWindowUserPointer(pWindow));
	if (pApp->data.firstMouse)
	{
		pApp->data.lastX = xpos;
		pApp->data.lastY = ypos;
		pApp->data.firstMouse = false;
	}

	double xoffset = xpos - pApp->data.lastX;
	double yoffset = pApp->data.lastY - ypos; // reversed since y-coordinates go from bottom to top

	pApp->data.lastX = xpos;
	pApp->data.lastY = ypos;

	Camera& cam = pApp->pRenderer->getCamera();
	cam.processMouseMovement(static_cast<float> (xoffset), static_cast<float> (yoffset));
}

void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	/* Not used, if needed comment out */
	/* App* pApp = static_cast <App*>(glfwGetWindowUserPointer(pWindow)); */

	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(pWindow, true);
	}
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
	glViewport(0, 0, width, height);

	App* pApp = static_cast <App*>(glfwGetWindowUserPointer(pWindow));
	pApp->config.width = width;
	pApp->config.height = height;

	/* Update projections with the new width and height */
	pApp->pRenderer->updateProjections(pApp->config);
}
