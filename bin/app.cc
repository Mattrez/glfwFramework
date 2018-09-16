#include "app.h"

/* All of GLFW callbacks declaration */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

App::App()
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

	auto config = Config::get();

	/* Pointing the window pointer to a window object */
	pWindow = glfwCreateWindow(config.width, config.height, config.windowName, NULL, NULL);

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

	rMA.addModel(ModelId::Basic,
				 indi,
				 { sizeof(unsigned int), 6 },
				 GL_STATIC_DRAW,
				 verties,
				 { sizeof(float), 4 * 8 },
				 GL_STATIC_DRAW);

	auto pBM = rMA.getModel(ModelId::Basic);

	/* Positions */
	pBM->getVAO().addToElements(3, GL_FLOAT, GL_FALSE);
	/* Color */
	pBM->getVAO().addToElements(3, GL_FLOAT, GL_FALSE);
	/* Texture Coordinates */
	pBM->getVAO().addToElements(2, GL_FLOAT, GL_FALSE);

	pBM->getVAO().populateLayouts(pBM->getVBO(), pBM->getEBO());

	rMA.addModel(ModelId::Text,
				 textIndi,
				 { sizeof(unsigned int), 6 },
				 GL_STATIC_DRAW,
				 NULL,
				 { sizeof(float), 4 * 4 },
				 GL_DYNAMIC_DRAW);

	pBM = rMA.getModel(ModelId::Text);

	pBM->getVAO().addToElements(4, GL_FLOAT, GL_FALSE);	

	pBM->getVAO().populateLayouts(pBM->getVBO(), pBM->getEBO());

	/* Basic Shader */
	ShaderAtlas::get().addShader(ShaderId::Basic,
								 "../shaders/sVertex.vert",
								 "../shaders/sFragment.frag");

	/* Basic Text Shader */
	ShaderAtlas::get().addShader(ShaderId::Text,
								 "../shaders/sText.vert",
								 "../shaders/sText.frag");

	TextureAtlas::get().addTexture(TextureId::Basic, "../res/logo.png", true);

	FontAtlas::get().addFont(FontId::Basic, "../res/arial.ttf");

	/* RenderableObject filling it with data */
	object.addModel(ModelId::Basic);
	object.setPosition({ 0.0f, 0.0f, 0.0f });
	object.setShaderId(ShaderId::Basic);
	object.setTextureId(TextureId::Basic);

	tObjext.setModelId(ModelId::Text);
	tObjext.setPosition({ 25.5f, 25.5f, 1.0f });
	tObjext.setRotation(0.0f);
	tObjext.setShaderId(ShaderId::Text);
	tObjext.setSize({ 1.0f, 1.0f });
	tObjext.setText("GFrame");
}

App::~App()
{
	/* Cleaning GLFW up */
	glfwTerminate();
}

void App::mainLoop()
{
	while(!glfwWindowShouldClose(pWindow))
	{
		/* Updates delta time */
		timer.setDeltaTime();

		/* Clearing the screen with set color */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Draw call */
		Renderer::draw(&object);
		Renderer::drawText(&tObjext);

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
	Camera& cam = Renderer::getCamera();
	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
		cam.processKeyboard(Camera::Movement::FORWARD, timer.getDeltaTime());
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
		cam.processKeyboard(Camera::Movement::BACKWARD, timer.getDeltaTime());
	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		cam.processKeyboard(Camera::Movement::LEFT, timer.getDeltaTime());
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		cam.processKeyboard(Camera::Movement::RIGHT, timer.getDeltaTime());
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

	Camera& cam = Renderer::getCamera();
	cam.processMouseMovement(static_cast<float> (xoffset), static_cast<float> (yoffset));
}

void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	/* Not used, if needed comment out */
	/* App* pApp = static_cast <App*>(glfwGetWindowUserPointer(pWindow)); */

	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(pWindow, true);
}
