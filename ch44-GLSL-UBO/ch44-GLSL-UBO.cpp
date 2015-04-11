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

static const glm::vec3 Pos[4] = 
{
	glm::vec3(-0.75f,  0.75f, 0.0f),
	glm::vec3( 0.75f,  0.75f, 0.0f),
	glm::vec3(-0.75f, -0.75f, 0.0f),
	glm::vec3( 0.75f, -0.75f, 0.0f),
};

const GLuint Width(1200), Height(1024);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLuint vbo, vao, ibo, program, ubo;
Shader TriangleShader("Triangle Shader");
GLuint color_loc;
GLuint transformLoc;
GLuint mvp_matrix_loc;
GLuint red_ubo_index, green_ubo_index, blue_ubo_index, yellow_ubo_index;

void init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "cube.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	TriangleShader.link();
	program = TriangleShader.program;

	//index --- binding point
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	red_ubo_index = glGetUniformBlockIndex(program, "transform");
	green_ubo_index = glGetUniformBlockIndex(program, "transform");
	blue_ubo_index = glGetUniformBlockIndex(program, "transform");
	yellow_ubo_index = glGetUniformBlockIndex(program, "transform");
	glUniformBlockBinding(program, red_ubo_index, 0);
	glUniformBlockBinding(program, green_ubo_index, 0);
	glUniformBlockBinding(program, blue_ubo_index, 0);
	glUniformBlockBinding(program, yellow_ubo_index, 0);
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
	
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glm::mat4 proj_matrix = glm::perspective(45.0f, 1300.0f / 900.0f, 1.0f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 2.2), glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0));
	// binding -- ubo -- 
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &proj_matrix[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

	//we render four cube with different position
    for (int i = 0; i != 4; ++i)
	{
		glBindVertexArray(vao);
		glUseProgram(program);
		glm::mat4 model;
		model = glm::translate(model, Pos[i]);	// Move top-left
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glUniform1i(glGetUniformLocation(program, "color"), i);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	}
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
	glDeleteBuffers(1, &ubo);
	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);  //we should close the window
}