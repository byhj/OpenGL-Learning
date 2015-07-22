#include "OGLRenderSystem.h"

namespace byhj
{
	void OGLRenderSystem::v_InitInfo()
	{
		windowInfo.title += ": Point";
	}

	void OGLRenderSystem::v_Init()
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_MULTISAMPLE);  

		init_fbo();
		m_Cube.Init();
		m_Camera.SetPos( glm::vec3(0.0f, 0.0f, 3.0f) );
	}

	void OGLRenderSystem::v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.3f, 0.4f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		update();

		static const byhj::MvpMatrix &matrix;
		matrix.view  = m_Camera.GetViewMatrix();
		matrix.proj  = glm::perspective(glm::radians(m_Camera.GetZoom() ), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::mat4(1.0f);

		// 1. Draw scene as normal in multisampled buffers
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    m_Cube.Render(matrix);

		// 2. Now blit multisampled buffer(s) to default framebuffers
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);				
		glBlitFramebuffer(0, 0, GetScreenWidth(), GetScreenWidth(), 0, 0, GetScreenWidth(), GetScreenWidth(), GL_COLOR_BUFFER_BIT, GL_NEAREST);     
	}

	void OGLRenderSystem::v_Shutdown()
	{
		m_Cube.Shutdown();
	}

	void OGLRenderSystem::init_fbo()
	{

		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);  
		// Create a multisampled color attachment texture
		textureColorBufferMultiSampled = generateMultiSampleTexture(4);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);
		// Create a renderbuffer object for depth and stencil attachments

		GLuint rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, GetScreenWidth(), GetScreenHeight()); 
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); 

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint OGLRenderSystem::generateMultiSampleTexture(GLuint samples)
	{
		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, GetScreenWidth(), GetScreenHeight(), GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		return texture;
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