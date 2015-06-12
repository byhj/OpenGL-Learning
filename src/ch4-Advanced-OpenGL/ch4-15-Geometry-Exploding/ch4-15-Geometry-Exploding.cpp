#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>
#include <common/model.h>

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
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);  
		glEnable(GL_PROGRAM_POINT_SIZE);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		float time = glfwGetTime();

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -8.0f, -15.0f))
			* glm::rotate(glm::mat4(1.0f),glm::radians(time* 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 view_matrix = camera.GetViewMatrix();
		glm::mat4 proj_matrix = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 1000.0f);
		glm::mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
		glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);

		//set the light unfirom
		glm::vec3 diffuseColor = glm::vec3(0.8f); // Decrease the influence
		glm::vec3 ambientColor = glm::vec3(0.8f); // Low influence
		glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
		glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(program, "time"), time);

		model.Draw(program);

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

	Shader modelShader;
	GLuint mvp_matrix_loc, model_matrix_loc, program;
	Model model;

	GLint lightSpecularLoc, lightDiffuseLoc, lightAmbientLoc;
};

CALL_MAIN(TextureApp);



void TextureApp::init_shader()
{
	modelShader.init();
	modelShader.attach(GL_VERTEX_SHADER, "model.vert");
	modelShader.attach(GL_GEOMETRY_SHADER, "model.geom");
	modelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
	modelShader.link();
	modelShader.use();

	program = modelShader.GetProgram();

	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	model_matrix_loc = glGetUniformLocation(program, "model_matrix");
	GLint matDiffuseLoc = glGetUniformLocation(program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(program, "material.shininess");
	glUniform3fv(matSpecularLoc, 1, &glm::vec3(0.5f, 0.5f, 0.5f)[0]);
	glUniform1f(matShineLoc, 64.0f);
	glUniform1i(matDiffuseLoc, 0);
	lightAmbientLoc = glGetUniformLocation(program, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(program, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(program,"light.specular");

}

void TextureApp::init_buffer()
{
	model.loadModel("../../../media/objects/nanosuit/nanosuit.obj");

}

void TextureApp::init_vertexArray()
{

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