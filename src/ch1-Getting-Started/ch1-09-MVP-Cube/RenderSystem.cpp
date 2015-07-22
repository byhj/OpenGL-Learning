#include <GL/glew.h>
#include "RenderSystem.h"

namespace byhj
{

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::v_InitInfo()
{
	windowInfo.title += "Cube";
}

void RenderSystem::v_Init()
{
	glEnable(GL_DEPTH_TEST);
	m_Cube.Init();

}

void RenderSystem::v_Render()
{
	static const float bgColor[4] = { 0.2f, 0.4f, 0.5f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, bgColor);
	static const float one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);

	static float aspect = GetAspect();
	m_Cube.Render(aspect);

}

void RenderSystem::v_Shutdown()
{
	m_Cube.Shutdown();
}
}