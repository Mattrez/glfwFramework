#include <iostream> // for cout

struct Config
{
	Config();
	
	Config(const char* configPath);
public:
	int width;
	int height;
	const char* windowName;
};
