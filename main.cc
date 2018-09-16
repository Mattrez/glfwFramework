#include <iostream> // for cout

#include "bin/app.h"

#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

int main()
{
	/* Calls config's ctor */
	Config::get("../res/config.ini");

	App app;

	app.mainLoop();

	return 0;
}
