#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>
#include <common/loadTexture.h>
#include <common/glDebug.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MANY_CUBES



#pragma region VertexData
// Set up vertex data (and buffer(s)) and attribute pointers
static const  GLfloat VertexData[] = {
	// Positions          // Normals           // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
#pragma endregion

// Positions all containers
glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 g_lightPos(2.5f, 0.5f, 0.0f);

class TextureApp: public byhj::Application
{
public:
	TextureApp():prog_app(0),prog_light(0), AppShader("Cube Shader"), LightShader("Light Shader")
	{
		camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
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

		//////////////////////////////Draw Base Scene////////////////////////////////
		glUseProgram(prog_app);
		glBindVertexArray(vao_app);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//////////////////////////////Set Material//////////////////////////////
		glUniform1i(glGetUniformLocation(prog_app, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(prog_app, "material.specular"), 1);
		GLint matShineLoc = glGetUniformLocation(prog_app, "material.shininess"); 
		glUniform1f(matShineLoc,    32.0f);

		///////////////////Light /////////////////////////////////
		GLint lightAmbientLoc  = glGetUniformLocation(prog_app, "light.ambient");
		GLint lightDiffuseLoc  = glGetUniformLocation(prog_app, "light.diffuse");
		GLint lightSpecularLoc = glGetUniformLocation(prog_app, "light.specular");
		GLint lightPosLoc = glGetUniformLocation(prog_app, "light.position");

		glUniform3f(lightPosLoc, g_lightPos.x, g_lightPos.y, g_lightPos.z);
		glUniform1f(glGetUniformLocation(prog_app, "light.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(prog_app, "light.linear"), 0.045);
		glUniform1f(glGetUniformLocation(prog_app, "light.quadratic"), 0.045);

		glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f); // Let's darken the light a bit to fit the scene
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);   

		/////////////////////////////Other//////////////////////////////////////////
		glUniform3fv(glGetUniformLocation(prog_app, "viewPos"), 1, &camera.Position[0]);

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse_tex);
		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular_tex);

#ifdef MANY_CUBES
		for(GLuint i = 0; i < 10; i++) 
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * (i+1); 
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 view = camera.GetViewMatrix();
			glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), GetAspect(), 0.1f, 1000.0f);
			glm::mat4 mvp = proj * view * model;
			glUniformMatrix4fv(glGetUniformLocation(prog_app, "model"), 1, GL_FALSE, &model[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(prog_app, "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(prog_app, "proj"), 1, GL_FALSE, &proj[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
#else
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view  = camera.GetViewMatrix();
		proj  = glm::perspective(45.0f, GetAspect(), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(prog_app, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(prog_app, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(prog_app, "proj"), 1, GL_FALSE, &proj[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
#endif

		glBindVertexArray(0);

		///////////////////////////////Draw Light/////////////////////////////////
		glUseProgram(prog_light);
		glBindVertexArray(vao_light);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), g_lightPos)
			            * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2) );
		glm::mat4 view  = camera.GetViewMatrix();
		glm::mat4 proj  = glm::perspective(glm::radians(camera.Zoom), GetAspect(), 0.1f, 100.0f);
		glm::mat4 mvp   = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(prog_light, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	void v_Shutdown()
	{
		glDeleteProgram(prog_app);
		glDeleteProgram(prog_light);
	}
	void v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void v_Movement(GLFWwindow *window);
	void v_MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();

private:

	// Camera
	Camera camera;
	bool keys[1024];
	GLfloat lastX, lastY ;
	bool firstMouse;
	GLfloat deltaTime;
	GLfloat lastFrame;

	//
	GLuint prog_light, prog_app;
	Shader LightShader, AppShader;
	GLuint diffuse_tex, specular_tex;
	GLuint mvp_loc;
	GLuint vao_light, vao_app, vbo, ibo;
};

CALL_MAIN(TextureApp);


void TextureApp::init_shader()
{
	LightShader.init();
	LightShader.attach(GL_VERTEX_SHADER, "light.vert");
	LightShader.attach(GL_FRAGMENT_SHADER, "light.frag");
	LightShader.link();
	prog_light = LightShader.GetProgram();

	AppShader.init();
	AppShader.attach(GL_VERTEX_SHADER, "cube.vert");
	AppShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	AppShader.link();
	prog_app = AppShader.GetProgram();

}

void TextureApp::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void TextureApp::init_vertexArray()
{
	//light data
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//cube data
	glGenVertexArrays(1, &vao_app);
	glBindVertexArray(vao_app);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void TextureApp::init_texture()
{
	diffuse_tex = loadTexture("../../../media/textures/container2.png");
	specular_tex = loadTexture("../../../media/textures/container2_specular.png");
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
