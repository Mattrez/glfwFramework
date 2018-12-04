#include "GFrame.h"

class Debug : public App
{
private:
	/* Debug only */
	rObject object;
	rObject object2;
	TextObject tObject;
public:
	Debug()
	{
		/* RenderableObject filling it with data */
		object.setModel(ModelId::Basic);
		object.addTexture(TextureId::Basic);
		object.setPosition({ 0.0f, 0.0f, 0.0f });
		object.setShaderId(ShaderId::Basic);
		
		object2.setModel(ModelId::Basic);
		object2.addTexture(TextureId::Basic);
		object2.setPosition({ 0.5f, 0.5f, -0.5f });
		object2.setShaderId(ShaderId::Basic);
		
		tObject.setModelId(ModelId::Text);
		tObject.setPosition({ 20.0f, 580.0f, 1.0f });
		tObject.setShaderId(ShaderId::Text);
		tObject.setSize({ 0.3f, 0.3f });
		
		pRenderer->reserve(2);
		pRenderer->submit(&object2);
		pRenderer->submit(&object);
		pRenderer->create();
	}

	~Debug() override
	{

	}

	void tick() override
	{
		/* Updates delta time */
		timer.setDeltaTime();

		tObject.setText(gf::dtos(gf::msToFps(timer.getDeltaTime())) + "fps");

		/* Clearing the screen with set color */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Draw call */
		pRenderer->drawText(&tObject);
		pRenderer->flush();
	}
};

int main()
{
	Debug* app = new Debug();

	app->mainLoop();

	return 0;
}
