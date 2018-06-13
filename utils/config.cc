#include "utils/config.h"

/* Default config of the window */
Config::Config() :
	width(800),
	height(800),
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
