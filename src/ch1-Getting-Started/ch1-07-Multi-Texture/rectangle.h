#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/oglApp.h"
#include "ogl/oglShader.h"

namespace byhj
{

class Rectangle
{
public:
	Rectangle(): program(0){ }
	~Rectangle() {}

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

		//We set the display mode is line
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glUseProgram(0);
	}

	void Shutdown() 
	{
		glDeleteProgram(program);
	}

private:

	void init_buffer();
	void init_shader();
	void init_vertexArray();
	void init_texture();

	GLuint tex1, tex2;
	GLuint tex1_loc, tex2_loc;
	GLuint  program;
	OGLShader RectangleShader;
};

}

#endif