#include "ogl/oglApp.h"

#include "triangle.h"

class RenderSystem : public byhj::Application
{
public:
	RenderSystem() {}
	~RenderSystem() {}

	void v_InitInfo()
	{
		windowInfo.title += ": Triangle";
	}
	void v_Init()
	{
		triangle.Init();
	}
	void v_Render()
	{

		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);

		triangle.Render();


	}

	void v_Shutdown()
	{
		triangle.Shutdown();
	}

private:
	byhj::Triangle triangle;
};

CALL_MAIN(RenderSystem);
