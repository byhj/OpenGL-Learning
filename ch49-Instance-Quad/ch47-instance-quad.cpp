#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

const int WIDTH = 1300;
const int HEIGHT = 900;

const static GLsizei VertexCount(30);
const static GLsizeiptr VertexSize = sizeof(GLfloat)* VertexCount;
const static GLfloat VertexData[VertexCount] = 
{ //vertex data
		// Positions   // Colors
		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		0.05f, 0.05f, 0.0f, 1.0f, 1.0f
};

GLuint vbo, vao, program, color_loc;
Shader triangleShader("Triangle");
GLuint mvp_matrix_loc;
GLuint instanceVBO;

void init_shader()  // initial the shader 
{
	triangleShader.init();
	triangleShader.attach(GL_VERTEX_SHADER, "quad.vert");
	triangleShader.attach(GL_FRAGMENT_SHADER, "quad.frag");
	triangleShader.link();
	program = triangleShader.program;
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
}


void init_buffer()
{
	glGenBuffers(1, &vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glm::vec2 translations[100];
	int index = 0;
	GLfloat offset = 0.1f;
	for (GLint y = -10; y < 10; y += 2)
	{
		for (GLint x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (GLfloat)x / 10.0f + offset;
			translation.y = (GLfloat)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);  //initial the vertex array object
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  //tranform the data to shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL + sizeof(GLfloat)* 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Also set instance data
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); //每个实例赋予不同属性
	glBindVertexArray(0);
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	init_shader();
	init_buffer();
	init_vertexArray();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
	glClearDepth(1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
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

		glfwPollEvents();

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}