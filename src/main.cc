#include "GFrame.h"

class Debug : public App
{
public:
	Debug()
	{

	}

	~Debug() override
	{

	}
};

int main()
{
	Debug* app = new Debug();

	app->mainLoop();

	return 0;
}
