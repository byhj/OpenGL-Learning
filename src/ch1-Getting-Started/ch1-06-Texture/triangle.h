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
		init_texture();
	}

	void Render() 
	{
		glUseProgram(program);
		glBindVertexArray(vao);

		//Draw the Triangle
		glBindTexture(GL_TEXTURE_2D, brickTex);
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
	void init_texture();

	GLuint vbo, vao, program;
	GLuint brickTex, tex_loc;
	OGLShader TriangleShader;
};

}

#endif