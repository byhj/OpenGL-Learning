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
	windowInfo.title += "Triangle";
}

void RenderSystem::v_Init()
{
	m_Triangle.Init();
}

void RenderSystem::v_Render()
{
	static const float bgColor[4] = { 0.2f, 0.4f, 0.5f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, bgColor);

	m_Triangle.Render();

}

void RenderSystem::v_Shutdown()
{
	m_Triangle.Shutdown();
}
}