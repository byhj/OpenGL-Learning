#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>

const static GLfloat VertexData[] = {
	// front
	-0.25, -0.25,  0.25,
	0.25, -0.25,  0.25,
	0.25,  0.25,  0.25,
	-0.25,  0.25,  0.25,
	// back
	-0.25, -0.25, -0.25,
	0.25, -0.25, -0.25,
	0.25,  0.25, -0.25,
	-0.25,  0.25, -0.25,
};
const static GLushort ElementData[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	3, 2, 6,
	6, 7, 3,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// left
	4, 0, 3,
	3, 7, 4,
	// right
	1, 5, 6,
	6, 2, 1,
};

const GLuint Width(1200), Height(1024);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLuint vbo, vao, ibo, program;
Shader TriangleShader("Triangle Shader");
GLuint color_loc;
GLuint transformLoc;

void init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "cube.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	TriangleShader.link();
	program = TriangleShader.program;
	transformLoc = glGetUniformLocation(program, "mvp_matrix");

}

void init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);    //load the vertex data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElementData), ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); 
	glBindVertexArray(0);
}

void render()
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glUseProgram(program);
	 glBindVertexArray(vao);

	 // Create transformations
	 glm::mat4 model;
	 glm::mat4 view;
	 glm::mat4 proj;
	 float time = glfwGetTime();
	 model = glm::rotate(model, glm::radians(time * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	 view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
	 proj  = glm::perspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	 glm::mat4 mvp = proj * view * model;
	 glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &mvp[0][0]);
	 glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	 glBindVertexArray(0);
}
void init()
{		
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);  
	init_shader();
	init_buffer();
	init_vertexArray();
}

int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(Width, Height, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL) 
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, Width, Height);
	init();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		render();

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);  //we should close the window
}