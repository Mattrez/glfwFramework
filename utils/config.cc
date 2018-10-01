#include "utils/config.h"

/* Default singelton */
Config& Config::get(const std::string& configPath)
{
	static Config instance (configPath.c_str());
	return instance;
}

Config::Config(const char* configPath)
{
	std::ifstream cfgFile (configPath);

	if(cfgFile.is_open())
	{
		std::string line;
		while(getline(cfgFile, line))
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			if (line[0] == '#' || line.empty()) { continue; }
			auto delimiterPos = line.find('=');
			auto name = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);
			setValue(name, value);
		}
	}
	else
	{
		std::cout << "[ERROR]: Couldn't open the config file\n";
	}
}

void Config::setValue(const std::string& name,
					  const std::string& value)
{
	if (name == "fov")
	{
		fov = static_cast <float> (std::stoi(value));
	}
	else if (name == "width")
	{
		width = static_cast <float> (std::stoi(value));
	}
	else if (name == "height")
	{
		height = static_cast <float> (std::stoi(value));
	}
	else if (name == "windowName")
	{
		windowName = value;
	}
	else if (name == "shadersPath")
	{
		shadersPath = value;
	}
	else if (name == "resPath")
	{
		resPath = value;
	}
}
