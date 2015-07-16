#include "triangle.h"

#include "ogl/loadTexture.h"

namespace byhj
{

	const static GLfloat VertexData[] = {
		// Positions    //Texcoords
		0.5f, -0.5f,    0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f,    1.0f, 0.0f,   // Bottom Left
		0.0f,  0.5f,    0.5f, 1.0f    // Top 
	};

void Triangle::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "triangle.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "triangle.frag");
	TriangleShader.link();
	TriangleShader.interfaceInfo();
	TriangleShader.use();
	program = TriangleShader.GetProgram();
	tex_loc = glGetUniformLocation(program, "tex");
	glUniform1i(tex_loc, 0);
}

void Triangle::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Tex attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}

void Triangle::init_texture()
{
	brickTex = loadTexture("../../../media/textures/wall.jpg");
}

}