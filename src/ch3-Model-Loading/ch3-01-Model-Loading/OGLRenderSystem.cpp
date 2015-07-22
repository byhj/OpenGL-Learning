#include "OGLRenderSystem.h"

const static glm::vec3 g_LightPos(1.5f, 0.5f, 0.0f);

namespace byhj
{
	void OGLRenderSystem::v_InitInfo()
	{
		windowInfo.title += ": Cube";
	}

	void OGLRenderSystem::v_Init()
	{
		glEnable(GL_DEPTH_TEST);

		objModel.Init();

		camera.SetPos( glm::vec3(0.0f, 7.0f, 22.0f) );
	}

	void OGLRenderSystem::v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		update();

		static const byhj::MvpMatrix &matrix;
		matrix.view  = camera.GetViewMatrix();
		matrix.proj  = glm::perspective(glm::radians( camera.GetZoom() ), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		objModel.Render(matrix);
	
	}

	void OGLRenderSystem::v_Shutdown()
	{
		objModel.Shutdown();
	}

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void OGLRenderSystem::v_Movement(GLFWwindow *Triangle)
	{
		camera.movement(Triangle);
	}
	void OGLRenderSystem::v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode)
	{
		camera.key_callback(Triangle, key, scancode, action, mode);
	}

	void OGLRenderSystem::v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos)
	{
		camera.mouse_callback(Triangle, xpos, ypos);
	}

	void OGLRenderSystem::v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset)
	{
		camera.scroll_callback(Triangle, xoffset, yoffset);
	}

	void OGLRenderSystem::update()
	{
		static GLfloat lastFrame = static_cast<float>( glfwGetTime() );
		GLfloat currentFrame = static_cast<float>( glfwGetTime() );
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.update(deltaTime);
	}

}