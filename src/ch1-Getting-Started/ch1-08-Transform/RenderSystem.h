#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ogl/App.h"
#include "Rectangle.h"

namespace byhj
{

class RenderSystem : public ogl::App
{
public:
	RenderSystem();
	~RenderSystem();

public:
	void v_InitInfo();
	void v_Init();
	void v_Render();
	void v_Shutdown();

private:

	byhj::Rectangle m_Rectangle;
};

}

#endif