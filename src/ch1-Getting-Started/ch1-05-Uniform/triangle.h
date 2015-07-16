#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/oglApp.h"
#include "ogl/oglShader.h"


namespace byhj
{

class Triangle
{
public:
	Triangle() :program(0), vao(0), vbo(0) { }
	~Triangle() {}

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

		//Draw the Triangle
		GLfloat time = static_cast<GLfloat>( glfwGetTime() );
		GLfloat redValue   = (sin(time) / 2.0f) + 0.5f;
		GLfloat greenValue = (cos(time) / 2.0f) + 0.5f;
		GLfloat blueValue  = (sin(time) / 2.0f) + (cos(time) / 2.0f);

		glUniform4f(color_loc, redValue, greenValue, blueValue, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Shutdown() 
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

private:

	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint color_loc;
	GLuint vbo, vao, program;
	OGLShader TriangleShader;
};

}

#endif