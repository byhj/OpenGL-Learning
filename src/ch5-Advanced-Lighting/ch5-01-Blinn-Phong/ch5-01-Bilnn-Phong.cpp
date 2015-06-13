#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Options
GLboolean blinn = false;
// Light source
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

class CullingApp: public byhj::Application
{
public:
	CullingApp():program(0), TriangleShader("Triangle Shader"), camera(glm::vec3(0.0f, 0.0f, 3.0f))
	{
		lastX = GetScreenWidth() / 2.0f;
		lastY = GetScreenHeight() / 2.0f;
		firstMouse = true;
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		for (int i = 0; i != 1024; ++ i)
			keys[i] = false;
	};
	~CullingApp() {};

	void v_Init()
	{			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);  

		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(planeVAO);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 100.0f);
		
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		// Set light uniforms
		glUniform3fv(glGetUniformLocation(program,  "lightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(program,  "viewPos"), 1, &camera.Position[0]);
		glUniform1i( glGetUniformLocation(program, "blinn"), blinn);
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		// Floor

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

private:

	// Camera
	Camera camera;
	bool keys[1024];
	GLfloat lastX, lastY ;
	bool firstMouse;
	GLfloat deltaTime;
	GLfloat lastFrame;

	//
	GLuint program;
	Shader TriangleShader;
    GLuint texture;
	// Setup plane VAO
	GLuint planeVAO, planeVBO;
};

CALL_MAIN(CullingApp);

#pragma region VertexData

GLfloat planeVertices[] = {
	// Positions          // Normals         // Texture Coords
	8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
	-8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
	-8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,

	8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
	-8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
	8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
};
#pragma endregion

void CullingApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "light.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "light.frag");
	TriangleShader.link();
	program = TriangleShader.GetProgram();

}

void CullingApp::init_buffer()
{
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void CullingApp::init_vertexArray()
{
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	
	glBindVertexArray(0);
}

void CullingApp::init_texture()
{
	texture = loadTexture("../../../media/textures/wood.png");
}

// Moves/alters the camera positions based on user input
void CullingApp::v_Movement(GLFWwindow *window)
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
	if (keys[GLFW_KEY_B])
	{
       blinn = !blinn;
	}
}

// Is called whenever a key is pressed/released via GLFW
void CullingApp::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << std::endl;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if(action == GLFW_PRESS)
		keys[key] = true;
	else if(action == GLFW_RELEASE)
		keys[key] = false;	
}

void CullingApp::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
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


void CullingApp::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

	camera.ProcessMouseScroll(yoffset);
}