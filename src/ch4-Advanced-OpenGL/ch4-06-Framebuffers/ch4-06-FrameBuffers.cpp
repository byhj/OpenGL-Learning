#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TextureApp: public byhj::Application
{
public:
	TextureApp():program(0), camera(glm::vec3(0.0f, 0.0f, 3.0f))
	{
		lastX = GetScreenWidth() / 2.0f;
		lastY = GetScreenHeight() / 2.0f;
		firstMouse = true;
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		for (int i = 0; i != 1024; ++ i)
			keys[i] = false;
	};
	~TextureApp() {};

	void v_Init()
	{			
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
		init_fbo();

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void v_Render()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glUseProgram(program);
		glm::mat4 model;
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glm::mat4 projection = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, &projection[0][0]);

		// Cubes
		glBindVertexArray(cube_vao);
		glBindTexture(GL_TEXTURE_2D, cube_texture);  // We omit the glActiveTexture part since TEXTURE0 is already the default active texture unit. (sampler used in fragment is set to 0 as well as default)		
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Floor
		glBindVertexArray(plane_vao);
		glBindTexture(GL_TEXTURE_2D, plane_texture);
		model = glm::mat4();
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		// Draw Screen
		glUseProgram(screen_program);
		glBindVertexArray(quad_vao);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// Use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

	}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void do_movement();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void v_Shutdown()
	{
		glDeleteProgram(program);
	}
	void v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void v_Movement(GLFWwindow *window);
	void v_MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	void init_shader();
	void init_texture();
	void init_buffer();
	void init_vertexArray();
	void init_fbo();
	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

private:

	// Camera
	Camera camera;
	bool keys[1024];
	GLfloat lastX, lastY ;
	bool firstMouse;
	GLfloat deltaTime;
	GLfloat lastFrame;


	GLuint cube_vao, cube_vbo, plane_vao, plane_vbo, quad_vao, quad_vbo;
	Shader depthShader;
	Shader screenShader;
	GLuint program, screen_program;
	GLuint cube_texture, plane_texture;
	GLuint tex, rbo, fbo;
	GLuint textureColorbuffer;
};

CALL_MAIN(TextureApp);


#pragma region Data


GLfloat cubeVertices[] = {
	// Positions          // Texture Coords
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

GLfloat planeVertices[] = {
	// Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
	5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
	-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

	5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
	5.0f, -0.5f, -5.0f, 2.0f, 2.0f
};

GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// Positions   // TexCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};
#pragma endregion

void TextureApp::init_shader()
{
	depthShader.init();
	depthShader.attach(GL_VERTEX_SHADER, "fbo.vert");
	depthShader.attach(GL_FRAGMENT_SHADER, "fbo.frag");
	depthShader.link();
	depthShader.use();
	program = depthShader.GetProgram();
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);

	screenShader.init();
	screenShader.attach(GL_VERTEX_SHADER, "screen.vert");
	screenShader.attach(GL_FRAGMENT_SHADER, "screen.frag");
	screenShader.link();
	screenShader.use();
	screen_program = screenShader.GetProgram();
	glUniform1i(glGetUniformLocation(screen_program, "texture1"), 0);
}

void TextureApp::init_texture()
{
	cube_texture = loadTexture("../../../media/textures/marble.jpg");
	plane_texture = loadTexture("../../../media/textures/metal.png");
}


void TextureApp::init_buffer()
{
	glGenBuffers(1, &cube_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &plane_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Setup screen VAO
	glGenVertexArrays(1, &quad_vao);
	glGenBuffers(1, &quad_vbo);
	glBindVertexArray(quad_vao);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void TextureApp::init_vertexArray()
{
	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	glGenVertexArrays(1, &plane_vao);
	glBindVertexArray(plane_vao);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

// Generates a texture that is suited for attachments to a framebuffer
GLuint TextureApp::generateAttachmentTexture(GLboolean depth, GLboolean stencil)
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
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, GetScreenWidth(), GetScreenHeight(), 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	else // Using both a stencil and depth test, needs special format arguments
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, GetScreenWidth(), GetScreenHeight(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

void TextureApp::init_fbo()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Create a color attachment texture
	textureColorbuffer = generateAttachmentTexture(false, false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	

	// Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
// Moves/alters the camera positions based on user input
void TextureApp::v_Movement(GLFWwindow *window)
{
	// Camera controls
	if(keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if(keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if(keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if(keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_C])
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.ctr = false;
	}
}

// Is called whenever a key is pressed/released via GLFW
void TextureApp::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << std::endl;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if(action == GLFW_PRESS)
		keys[key] = true;
	else if(action == GLFW_RELEASE)
		keys[key] = false;	
}

void TextureApp::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}	


void TextureApp::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

	camera.ProcessMouseScroll(yoffset);
}



