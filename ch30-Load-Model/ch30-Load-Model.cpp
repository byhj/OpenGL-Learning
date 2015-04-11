#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "model.h"
#include "camera.h"

void key_callback(GLFWwindow * window,  int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void do_movement();

const GLuint WIDTH = 1300, HEIGHT = 900;
Camera camera( glm::vec3(0.0f, 0.0f, 0.0f) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

glm::vec3 lightPos(1.0f, 0.5f, 1.0f);
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
Shader modelShader("Model");
GLuint mvp_matrix_loc, model_matrix_loc, program;
Model model;

struct Material {
	GLuint diffuse;
	GLuint specular;
	float     shininess;
};

Material material;
GLint lightSpecularLoc, lightDiffuseLoc, lightAmbientLoc;

void init_shader()  // initial the shader 
{
	modelShader.init();
	modelShader.attach(GL_VERTEX_SHADER, "model.vert");
	modelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
	modelShader.link();
	program = modelShader.program;

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

void init()
{
	init_shader();
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	model.loadModel("../media/object/nanosuit/nanosuit.obj");
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	float time = glfwGetTime() / 1000.0f;

	//set the mvp matrix
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -8.0f, -15.0f))
		                   * glm::rotate(glm::mat4(1.0f),glm::radians(time* 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view_matrix = camera.GetViewMatrix();//glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -10.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 proj_matrix = glm::perspective(45.0f, 1300 / 900.0f, 0.1f, 1000.0f);
	glm::mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);

	//set the light unfirom
	glm::vec3 diffuseColor = glm::vec3(0.8f); // Decrease the influence
	glm::vec3 ambientColor = glm::vec3(0.8f); // Low influence
	glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

	model.Draw(program);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Fail to initial the GLEW:"  << std::endl;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	init();

	while(!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		do_movement();

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}