#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>
#include <common/model.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SkyboxApp: public byhj::Application
{
public:
	SkyboxApp():camera(glm::vec3(0.0f, 0.0f, 3.0f))
	{
		lastX = GetScreenWidth() / 2.0f;
		lastY = GetScreenHeight() / 2.0f;
		firstMouse = true;
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		for (int i = 0; i != 1024; ++ i)
			keys[i] = false;
	};
	~SkyboxApp() {};

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
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Draw skybox first, disable depth writing. 
		// This way the skybox will always be drawn at the background of all the other objects.

		glDepthMask(GL_FALSE);
		// Remove any translation component of the view matrix
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glm::mat4 proj = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 100.0f);
		glUseProgram(skybox_program);
		glm::mat4 mvp =  proj * view;
		glUniformMatrix4fv(glGetUniformLocation(skybox_program, "mvp_matrix"), 1, GL_FALSE, glm::value_ptr(mvp));
		glBindVertexArray(skybox_vao);
		glBindTexture(GL_TEXTURE_CUBE_MAP, modelmap_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS); // Set depth function back to default
		GLfloat time = glfwGetTime() / 1000.0;
		glUseProgram(model_program);
		glBindVertexArray(model_vao);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -8.0f, -15.0f))
			* glm::rotate(glm::mat4(1.0f), time * 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		view = camera.GetViewMatrix();
		mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(model_program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(model_program, "mvp_matrix"), 1, GL_FALSE, glm::value_ptr(mvp));
		glBindVertexArray(model_vao);

		objModel.Draw(model_program);

		glBindVertexArray(0);


	}
	void key_callback(GLFWwindow* Triangle, int key, int scancode, int action, int mode);
	void do_movement();
	void mouse_callback(GLFWwindow* Triangle, double xpos, double ypos);
	void scroll_callback(GLFWwindow* Triangle, double xoffset, double yoffset);

	void v_Shutdown()
	{
	}
	void v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode);
	void v_Movement(GLFWwindow *Triangle);
	void v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset);

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
	GLuint model_vbo, model_vao, model_program, model_tex_loc;
	Shader modelShader;
	Shader skyboxShader;
	GLuint skybox_vbo, skybox_vao, skybox_program;
	GLuint model_mvp_loc, skybox_mvp_loc, skybox_tex_loc;
	GLuint modelmap_texture, model_texture;
	Model objModel;
};

CALL_MAIN(SkyboxApp);

#pragma region VertexData

GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};
#pragma endregion

void SkyboxApp::init_shader()
{
	modelShader.init();
	modelShader.attach(GL_VERTEX_SHADER, "model.vert");
	modelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
	modelShader.link();
	model_program = modelShader.GetProgram();
	model_mvp_loc = glGetUniformLocation(model_program, "mvp_matrix");

	skyboxShader.init();
	skyboxShader.attach(GL_VERTEX_SHADER, "skybox.vert");
	skyboxShader.attach(GL_FRAGMENT_SHADER, "skybox.frag");
	skyboxShader.link();
	skybox_program = skyboxShader.GetProgram();
	skybox_tex_loc = glGetUniformLocation(skybox_program, "skybox");
	skybox_mvp_loc = glGetUniformLocation(skybox_program, "mvp_matrix");

}

void SkyboxApp::init_buffer()
{
	objModel.loadModel("../../../media/objects/nanosuit/nanosuit.obj");

	glGenBuffers(1, &skybox_vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SkyboxApp::init_vertexArray()
{
	//skybox data
	glGenVertexArrays(1, &skybox_vao);  
	glBindVertexArray(skybox_vao);
	glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 3, (GLvoid*)(NULL));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void SkyboxApp::init_texture()
{
	// Cubemap (Skybox)
	std::vector<std::string> faces;
	faces.push_back("../../../media/textures/skybox/right.jpg");
	faces.push_back("../../../media/textures/skybox/left.jpg");
	faces.push_back("../../../media/textures/skybox/top.jpg");
	faces.push_back("../../../media/textures/skybox/bottom.jpg");
	faces.push_back("../../../media/textures/skybox/back.jpg");
	faces.push_back("../../../media/textures/skybox/front.jpg");
	modelmap_texture = loadCubeMap(faces);
}

// Moves/alters the camera positions based on user input
void SkyboxApp::v_Movement(GLFWwindow *Triangle)
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
		glfwSetInputMode(Triangle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.ctr = false;
	}
}

// Is called whenever a key is pressed/released via GLFW
void SkyboxApp::v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode)
{
	//cout << key << std::endl;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(Triangle, GL_TRUE);

	if(action == GLFW_PRESS)
		keys[key] = true;
	else if(action == GLFW_RELEASE)
		keys[key] = false;	
}

void SkyboxApp::v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos)
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


void SkyboxApp::v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset)
{

	camera.ProcessMouseScroll(yoffset);
}