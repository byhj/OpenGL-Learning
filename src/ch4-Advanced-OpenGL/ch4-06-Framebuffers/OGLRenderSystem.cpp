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

		init_fbo();

		m_Cube.Init();
		m_Plane.Init();
		m_Window.Init();
		m_Camera.SetPos( glm::vec3(0.0f, 0.0f, 3.0f) );
	}

	void OGLRenderSystem::v_Render()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		update();

		static const byhj::MvpMatrix &matrix;
		matrix.view  = m_Camera.GetViewMatrix();
		matrix.proj  = glm::perspective(glm::radians(m_Camera.GetZoom() ), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::mat4(1.0f);

		m_Cube.Render(matrix);
		m_Plane.Render(matrix);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearBufferfv(GL_COLOR, 0, bgColor);

		glDisable(GL_DEPTH_TEST);

		// Use the color attachment texture as the texture of the quad plane
		m_Window.Render(matrix, textureColorbuffer);
	
	}

	void OGLRenderSystem::v_Shutdown()
	{
		m_Cube.Shutdown();
		m_Plane.Shutdown();
		m_Window.Shutdown();
	}

	// Generates a texture that is suited for attachments to a framebuffer
	GLuint OGLRenderSystem::generateAttachmentTexture(GLboolean depth, GLboolean stencil)
	{
		// What enum to use?
		GLenum attachment_type;
		if(!depth && !stencil)
			attachment_type = GL_RGB;
		else if(depth && !stencil)
			attachment_type = GL_DEPTH_COMPONENT;
		else if(!depth && stencil)
			attachment_type = GL_STENCIL_INDEX;

		//Generate texture ID and load texture data 
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		if(!depth && !stencil)
			glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, GetScreenWidth(), GetScreenHeight(), 
			             0, attachment_type, GL_UNSIGNED_BYTE, NULL);
		else // Using both a stencil and depth test, needs special format arguments
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, GetScreenWidth(), GetScreenHeight(),
			             0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		return textureID;
	}

	void OGLRenderSystem::init_fbo()
	{
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		// Create a color attachment texture
		textureColorbuffer = generateAttachmentTexture(false, false);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
		// Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

		// Now that we actually created the framebuffer and added all attachments 
		//we want to check if it is actually complete now
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	/////////////////////////////////Key and Mouse//////////////////////////////////
	void OGLRenderSystem::v_Movement(GLFWwindow *Triangle)
	{
		m_Camera.movement(Triangle);
	}
	void OGLRenderSystem::v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode)
	{
		m_Camera.key_callback(Triangle, key, scancode, action, mode);
	}

	void OGLRenderSystem::v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos)
	{
		m_Camera.mouse_callback(Triangle, xpos, ypos);
	}

	void OGLRenderSystem::v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset)
	{
		m_Camera.scroll_callback(Triangle, xoffset, yoffset);
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