#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/oglApp.h"
#include "ogl/oglShader.h"

namespace byhj
{

class Rectangle
{
public:
	Rectangle(): program(0), vao(0), vbo(0), ibo(0) { }
	~Rectangle() {}

public:

	void Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void Render() 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);

		//We set the display mode is line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Shutdown() 
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

private:

	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint vbo, vao, ibo, program;
	OGLShader RectangleShader;
};

}

#endif