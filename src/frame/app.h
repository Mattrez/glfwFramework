#ifndef APP_H
#define APP_H

#include <iostream> // for cout
#include <memory>

#include "utils/GLIncludes.h"

#include "frame/app.h"
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
	virtual ~App();

	virtual void mainLoop();
	virtual void processKeyboard();

	friend void mouse_callback(GLFWwindow* pWindow, double xpos, double ypos);
	friend void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
	friend void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);
protected:
	virtual void tick();
private:
	struct mouseData
	{
		bool firstMouse = true;
		double lastX = 0.0f;
		double lastY = 0.0f;
	};
protected:
	GLFWwindow* pWindow;
	Renderer* pRenderer;
	Config config;
	Timer timer;
	mouseData data;
};

#endif
