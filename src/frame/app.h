#ifndef APP_H
#define APP_H

#include <iostream> // for cout

#include "utils/GLIncludes.h"

#include "utils/config.h"
#include "utils/timer.h"
#include "utils/macros.h"
#include "renderable/renderer.h"
#include "renderable/vao.h"
#include "renderable/vbo.h"
#include "renderable/layoutElement.h"
#include "renderable/shader.h"
#include "renderable/ebo.h"
#include "renderable/camera.h"
#include "renderable/modelAtlas.h"
#include "renderable/shaderAtlas.h"
#include "renderable/texture.h"
#include "renderable/textureAtlas.h"
#include "objects/rObject.h"
#include "objects/textObject.h"

class App
{
public:
	App();
	~App();

	void mainLoop();
	void processKeyboard();

	friend void mouse_callback(GLFWwindow* pWindow, double xpos, double ypos);
	friend void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
private:
	struct mouseData
	{
		bool firstMouse = true;
		double lastX = 0.0f;
		double lastY = 0.0f;
	};
private:
	GLFWwindow* pWindow;
	Renderer* pRenderer;
	Timer timer;
	mouseData data;
	/* Debug only */
	rObject object;
	rObject object2;
	TextObject tObject;
};

#endif
