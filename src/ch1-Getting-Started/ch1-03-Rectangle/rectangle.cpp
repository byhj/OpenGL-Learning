#include "Rectangle.h"

namespace byhj
{

void Rectangle::Init()
{
	init_shader();
	init_buffer();
	init_vertexArray();
}

void Rectangle::Render()
{
	glUseProgram(program);
	glBindVertexArray(vao);

	//We set the display mode is line
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
}

void Rectangle::Shutdown()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

//////////////////////////Data///////////////////////////
const static GLfloat VertexData[] =
{
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.5f,  0.5f,
	-0.5f,  0.5f,
};
const static GLsizei VertexSize = sizeof(VertexData);

const static GLuint IndexData[] =
{
	0, 1, 2,
	2, 3, 0,
};
const static GLsizei IndexSize = sizeof(IndexData);

//////////////////////////Data////////////////////////////

void Rectangle::init_shader()
{
	RectangleShader.init();
	RectangleShader.attach(GL_VERTEX_SHADER, "rectangle.vert");
	RectangleShader.attach(GL_FRAGMENT_SHADER, "rectangle.frag");
	RectangleShader.link();
	RectangleShader.info();
	program = RectangleShader.GetProgram();
}

void Rectangle::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);    //load the vertex data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexSize, IndexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Rectangle::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}

}