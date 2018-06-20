#ifndef CONFIG_H
#define CONFIG_H

#include <iostream> // for cout

struct Config
{
public:
	static Config& get();
private:
	Config();
	
	Config(const char* configPath);
public:
	float fov;
	float width;
	float height;
	const char* windowName;
};

#endif
