#include "ogl/oglApp.h"

#include "rectangle.h"

class OGLRenderSystem : public byhj::Application
{
public:
	OGLRenderSystem() {}
	~OGLRenderSystem() {}

	void v_InitInfo()
	{
		windowInfo.title += ": Rectangle";
	}
	void v_Init()
	{
		rectangle.Init();
	}
	void v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);

		rectangle.Render();
	}

	void v_Shutdown()
	{
		rectangle.Shutdown();
	}

private:
	byhj::Rectangle rectangle;
};

CALL_MAIN(OGLRenderSystem);