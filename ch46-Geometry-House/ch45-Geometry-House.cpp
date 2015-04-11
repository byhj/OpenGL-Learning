#include <gl/glew.h>
#include <gl/glfw3.h>
#include <shader.h>
#include <glm/glm.hpp>

const int Width  = 1300;
const int Height = 900;
Shader GeometryShader("Line");
GLuint vao, vbo, program;

// Vertex data
GLfloat VertexData[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
	 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // Bottom-left
};

void init_shader()
{
	GeometryShader.init();
	GeometryShader.attach(GL_VERTEX_SHADER, "house.vert");
	GeometryShader.attach(GL_GEOMETRY_SHADER, "house.geom");
	GeometryShader.attach(GL_FRAGMENT_SHADER, "house.frag");
	GeometryShader.link();
	program = GeometryShader.program;
}

void init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
	glBindVertexArray(1);
}

void init()
{

	glEnable(GL_PROGRAM_POINT_SIZE);
    glClearColor(0.0, 0.0, 0.0, 1.0);
	init_shader();
	init_buffer();
	init_vertexArray();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 5);
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
	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}