#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <shader.h>

Shader PointShader("Point Size");
GLuint program, vao, vbo;

static const GLfloat VertexData[] = {
	0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

void init_shader()
{
	PointShader.init();
	PointShader.attach(GL_VERTEX_SHADER, "line.vert");
	PointShader.attach(GL_GEOMETRY_SHADER, "line.geo");
	PointShader.attach(GL_FRAGMENT_SHADER, "line.frag");
	PointShader.link();
	program = PointShader.program;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
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
	//glPointSize(10.0f);
	glPolygonMode(GL_FRONT, GL_LINE);
	glDrawArrays(GL_POINTS, 0, 5);
	glutSwapBuffers();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("Point size");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}