#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <SOIL/SOIL.h>
#include <map>
#include "camera.h"

void key_callback(GLFWwindow * window,  int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void do_movement();
GLuint loadTexture(GLchar* path, GLboolean alpha = false);

const GLuint WIDTH = 1300, HEIGHT = 900;
Camera camera( glm::vec3(0.0f, 0.0f, 3.0f) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat cubeVertices[] = {
	// Positions          // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f
};
GLfloat planeVertices[] = {
	// Positions          // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
	5.0f, -0.5f,  5.0f,  2.0f,  0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f,  0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f,  2.0f,

	5.0f, -0.5f,  5.0f,  2.0f,  0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f,  2.0f,
	5.0f, -0.5f, -5.0f,  2.0f,  2.0f
};

GLfloat transparentVertices[] = {
	// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

GLuint cube_vao, cube_vbo, plane_vao, plane_vbo, transparent_vao, transparent_vbo;
Shader depthShader("Depth test");
GLuint program;
GLuint cube_texture, plane_texture , transparent_texture;
GLuint tex;

void init_shader()
{
	depthShader.init();
	depthShader.attach(GL_VERTEX_SHADER, "blend.vert");
	depthShader.attach(GL_FRAGMENT_SHADER, "blend.frag");
	depthShader.link();
	program = depthShader.program;
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);
}

void init_buffer()
{
	glGenBuffers(1, & cube_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &plane_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &transparent_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, transparent_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_vertexArray()
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

	glGenVertexArrays(1, &transparent_vao);
	glBindVertexArray(transparent_vao);
	glBindBuffer(GL_ARRAY_BUFFER, transparent_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

GLuint loadTexture(GLchar* path, GLboolean alpha)
{
	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width,height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);	

	// Parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT );	// Use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes value from next repeat 
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

void init_texture()
{
	cube_texture = loadTexture("../media/texture/marble.jpg");
	plane_texture = loadTexture("../media/texture/metal.png");
	transparent_texture = loadTexture("../media/texture/window.png", true);
}

void init()
{

	init_shader();
	init_buffer();
	init_vertexArray();
	init_texture();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glm::mat4 model;
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera.Zoom, 1300.0f / 900.0f, 0.1f, 100.0f);
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

	// Floor
	glBindVertexArray(plane_vao);
	glBindTexture(GL_TEXTURE_2D, plane_texture);
	model = glm::mat4();
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// Vegetation
	// Sort windows
	std::vector<glm::vec3> windows;
	windows.push_back(glm::vec3(-1.5f,  0.0f, -0.48f));
	windows.push_back(glm::vec3( 1.5f,  0.0f,  0.51f));
	windows.push_back(glm::vec3( 0.0f,  0.0f,  0.7f));
	windows.push_back(glm::vec3(-0.3f,  0.0f, -2.3f));
	windows.push_back(glm::vec3( 0.5f,  0.0f, -0.6f));
	std::map<GLfloat, glm::vec3> sorted;
	for (GLuint i = 0; i < windows.size(); i++)
	{
		GLfloat distance = glm::length(camera.Position - windows[i]);
		sorted[distance] = windows[i];
	}
	glBindVertexArray(transparent_vao);
	glBindTexture(GL_TEXTURE_2D, transparent_texture);
	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		model = glm::mat4();
		model = glm::translate(model, it->second);
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
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