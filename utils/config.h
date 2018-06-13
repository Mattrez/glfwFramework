#ifndef CONFIG_H
#define CONFIG_H

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

#endif
