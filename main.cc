#include <iostream> // for cout

#include "bin/app.h"

#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

/* Calls config's ctor */
auto ctor = Config::get("../res/config.ini");

int main()
{
	App app;

	app.mainLoop();

	return 0;
}
