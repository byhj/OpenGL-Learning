#include "RenderSystem.h"

namespace byhj
{
	void RenderSystem::v_InitInfo()
	{
		windowInfo.title += ": Point";
	}

	void RenderSystem::v_Init()
	{
		glEnable(GL_DEPTH_TEST); 

		init_fbo();

		m_Plane.Init();
		m_Cube.Init();
		m_Camera.SetPos( glm::vec3(0.0f, 0.0f, 18.0f) );
	}

	void RenderSystem::v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.3f, 0.4f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		update();

		static ogl::MvpMatrix matrix;
		matrix.view  = m_Camera.GetViewMatrix();
		matrix.proj  = glm::perspective(glm::radians(m_Camera.GetZoom() ), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::mat4(1.0f);
			
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Cube.Render(matrix, m_Camera);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    m_Plane.Render(matrix, colorBuffer);
	}

	void RenderSystem::v_Shutdown()
	{
		m_Plane.Shutdown();
		m_Cube.Shutdown();
	}

	void RenderSystem::init_fbo()
	{		
		glGenFramebuffers(1, &fbo);

		//Create floating point color buffer
		glGenBuffers(1, &colorBuffer);
		glBindTexture(GL_TEXTURE_2D, colorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, GetScreenWidth(), GetScreenHeight(), 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLuint rboDepth;
		//Craete depth buffer(renderbuffer)
		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, GetScreenWidth(), GetScreenHeight());

		//Attach buffers
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void RenderSystem::v_Movement(GLFWwindow *window)
	{
		m_Camera.movement(window);
	}
	void RenderSystem::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{		
		if(key == GLFW_KEY_H )
		   m_Plane.AddExposure();

		m_Camera.key_callback(window, key, scancode, action, mode);
	}

	void RenderSystem::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		m_Camera.mouse_callback(window, xpos, ypos);
	}

	void RenderSystem::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		m_Camera.scroll_callback(window, xoffset, yoffset);
	}

	void RenderSystem::update()
	{
		static GLfloat lastFrame = static_cast<float>( glfwGetTime() );
		GLfloat currentFrame = static_cast<float>( glfwGetTime() );
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Camera.update(deltaTime);
	}

}