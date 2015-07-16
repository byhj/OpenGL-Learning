#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/oglApp.h"
#include "ogl/oglShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, &trans[0][0]);

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
	GLuint tex1_loc, tex2_loc,  transform_loc;
	GLuint  program;
	OGLShader RectangleShader;
};

}

#endif