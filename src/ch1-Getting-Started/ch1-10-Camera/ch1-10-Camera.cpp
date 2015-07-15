#include "ogl/oglApp.h"
#include "ogl/camera.h"

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
		camera.SetPos( glm::vec3(0.0f, 0.0f, 3.0f) );
	}
	void v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		update();

		cube.Render(camera.GetViewMatrix(), camera.GetZoom(), GetAspect() );
	}

	void v_Shutdown()
	{
		cube.Shutdown();
	}

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void v_Movement(GLFWwindow *window)
	{
		camera.movement(window);
	}
	void v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		camera.key_callback(window, key, scancode, action, mode);
	}

	void v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		camera.mouse_callback(window, xpos, ypos);
	}

	void v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.scroll_callback(window, xoffset, yoffset);
	}

private:
	void update()
	{
		static GLfloat lastFrame = glfwGetTime();
		GLfloat currentFrame = glfwGetTime();
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.update(deltaTime);
	}

	byhj::Cube cube;
	byhj::Camera camera;
};

CALL_MAIN(OGLRenderSystem);