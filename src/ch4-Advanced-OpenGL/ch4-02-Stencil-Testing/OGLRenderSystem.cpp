#include "OGLRenderSystem.h"
#include "ogl/glDebug.h"

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
		glDepthFunc(GL_LESS);

		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		m_Cube.Init();
		m_Plane.Init();
		m_Camera.SetPos( glm::vec3(0.0f, 0.0f, 3.0f) );

	}

	void OGLRenderSystem::v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);
		static const float zero = 0.0f;
		glClearBufferfv(GL_STENCIL, 0, &zero);

		update();

		static byhj::MvpMatrix matrix;
		matrix.view  = m_Camera.GetViewMatrix();
		matrix.proj  = glm::perspective(glm::radians(m_Camera.GetZoom() ), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::mat4(1.0f);

		// Draw floor as normal, we only care about the containers. The floor should NOT fill the stencil buffer so we set its mask to 0x00
		//disable write stencil buffer
		glStencilMask(0x00);  
		m_Plane.Render(matrix);

		// 1st. Render pass, draw objects as normal, filling the stencil buffer
		//将像素与后两位与1比较，比较模式GL_ALWAYS，即像素区域模板值都是1
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);		//enable write stencil buffer,fill the stencil buffer with 1

		m_Cube.Render(matrix);

		// 2nd. Render pass, now draw slightly scaled versions of the objects, this time disabling stencil writing.
		// Because stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are now not drawn, thus only drawing 
		// the objects' size differences, making it look like borders.
		//将模式放大一些，将后两位与1比较，不等于1的通过绘制，因为前面讲特定区域绘制成1了，所以只有边界
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		m_Cube.RenderColor(matrix);

		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);

	}

	void OGLRenderSystem::v_Shutdown()
	{
		m_Cube.Shutdown();
		m_Plane.Shutdown();
	}

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void OGLRenderSystem::v_Movement(GLFWwindow *window)
	{
		m_Camera.movement(window);
	}
	void OGLRenderSystem::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		m_Camera.key_callback(window, key, scancode, action, mode);
	}

	void OGLRenderSystem::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		m_Camera.mouse_callback(window, xpos, ypos);
	}

	void OGLRenderSystem::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		m_Camera.scroll_callback(window, xoffset, yoffset);
	}

	void OGLRenderSystem::update()
	{
		static GLfloat lastFrame = static_cast<float>( glfwGetTime() );
		GLfloat currentFrame = static_cast<float>( glfwGetTime() );
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Camera.update(deltaTime);
	}

}