/*
 *                      Model Matrix              View Matrix
 * Local(Object) Space ------------->World Space------------>
 *                       Proj Matrix                 
 * Camera(View)  Space ------------->Clip  Space(change data to (-1.0, 1.0) 
 * which is NDC, frustum clip , then take the  perspective division 
 * Viewport
 * ----------> Screen Space( Map to Window Screen Width and Height)
 */
#include "ogl/oglApp.h"

#include "cube.h"

class OGLRenderSystem : public byhj::Application
{
public:
	OGLRenderSystem() {}
	~OGLRenderSystem() {}

	void v_InitInfo()
	{
		windowInfo.title += ": Cube";
	}
	void v_Init()
	{
		cube.Init();
	}
	void v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		cube.Render();
	}

	void v_Shutdown()
	{
		cube.Shutdown();
	}

private:
	byhj::Cube cube;
};

CALL_MAIN(OGLRenderSystem);