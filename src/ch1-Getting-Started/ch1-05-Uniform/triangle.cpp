#include "triangle.h"

namespace byhj
{

void Triangle::Init()
{
	init_shader();
	init_buffer();
	init_vertexArray();
}

void Triangle::Render()
{
	glUseProgram(program);
	glBindVertexArray(vao);

	update();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(0);
	glBindVertexArray(0);
}

void Triangle::Shutdown()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Triangle::update()
{
	GLfloat time = static_cast<GLfloat>(glfwGetTime());
	GLfloat redValue = (sin(time) / 2.0f) + 0.5f;
	GLfloat greenValue = (cos(time) / 2.0f) + 0.5f;
	GLfloat blueValue = (sin(time) / 2.0f) + (cos(time) / 2.0f);
	glUniform4f(color_loc, redValue, greenValue, blueValue, 1.0f);
}

const static GLfloat VertexData[] = 
{
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.0f,  0.5f
};
const static GLsizei VertexSize = sizeof(VertexData);

void Triangle::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "triangle.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "triangle.frag");
	TriangleShader.link();
	TriangleShader.info();
	program = TriangleShader.GetProgram();

	color_loc = glGetUniformLocation(program, "color");
	assert(color_loc != byhj::OGL_VALUE);
}

void Triangle::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}

}