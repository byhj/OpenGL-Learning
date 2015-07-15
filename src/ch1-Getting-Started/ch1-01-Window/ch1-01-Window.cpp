#include "ogl/oglApp.h"

#include "window.h"

class OGLRenderSystem : public byhj::Application
{
public:
	OGLRenderSystem() {}
	~OGLRenderSystem() {}

	void v_InitInfo()
	{
		windowInfo.title += ": Window";
	}
	void v_Init()
	{
		window.Init();
	}
	void v_Render()
	{

		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);

		window.Render();

	}
	void v_Shutdown()
	{
		window.Shutdown();
	}

private:
	byhj::Window window;
};

CALL_MAIN(OGLRenderSystem);