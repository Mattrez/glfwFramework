#include "utils/config.h"

/* Default singelton */
Config& Config::get()
{
	static Config instance;
	return instance;
}

/* Default config of the window */
Config::Config() :
	fov(45.0f),
	width(800.0f),
	height(800.0f),
	windowName("glfwFramework")
{ }

/* Constructor that changes the config variables accoring to the given file */
/* !!! NOT YET SUPPORTED !!! */
Config::Config(const char* configPath) :
	Config()
{
	std::cout << "Reading config from a file not yet supported\n";
	std::cout << "Setting the variables to default!\n";
}
