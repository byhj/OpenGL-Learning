#ifndef OGLRENDERSYSTEM_H
#define OGLRENDERSYSTEM_H

#include "ogl/oglApp.h"
#include "ogl/camera.h"

#include "cube.h"
#include "skybox.h"

namespace byhj
{

class OGLRenderSystem : public byhj::Application
{
public:
	OGLRenderSystem() {}
	~OGLRenderSystem() {}

	///////////////////////// Triangle and Render //////////////////////////////////
	void v_InitInfo();
	void v_Init();
	void v_Render();
	void v_Shutdown();

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void v_Movement(GLFWwindow *Triangle);
	void v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode);
	void v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset);


private:
	void update();

	byhj::Cube   m_Cube;
	byhj::Skybox m_Skybox;
	byhj::Camera m_Camera;
};


}

#endif