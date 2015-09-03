#include "triangle.h"

#include "ogl/loadTexture.h"

namespace byhj
{

void Triangle::Init()
{
	init_shader();
	init_buffer();
	init_vertexArray();
	init_texture();
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
	glDeleteTextures(1, &brickTex);
}

void Triangle::update()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTex);
	glUniform1i(tex_loc, 0);
}

const static GLfloat VertexData[] = 
{
	// Positions    //Texcoords
	 0.5f, -0.5f,    0.0f, 0.0f,   // Bottom Right
	-0.5f, -0.5f,    1.0f, 0.0f,   // Bottom Left
	 0.0f,  0.5f,    0.5f, 1.0f    // Top 
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

	tex_loc = glGetUniformLocation(program, "tex");
	assert(tex_loc != ogl::VALUE);
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
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::init_texture()
{
	brickTex = ogl::loadTexture("../../../media/textures/wall.jpg");
}

}