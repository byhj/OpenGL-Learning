

#include "Triangle.h"
#include "ogl/loadTexture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>

namespace byhj
{
#pragma region VertexData

	const static GLfloat VertexData[] = 
	{
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

#pragma endregion

	void Triangle::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Triangle::Render(const const byhj::MvpMatrix &matrix, const GLuint &textureID)
	{
		glUseProgram(program);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);	

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Triangle::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Triangle::init_shader()
	{
		WindowShader.init();
		WindowShader.attach(GL_VERTEX_SHADER,   "Triangle.vert");
		WindowShader.attach(GL_FRAGMENT_SHADER, "Triangle.frag");
		WindowShader.link();
		WindowShader.info();
		program = WindowShader.GetProgram();

		tex_loc   = glGetUniformLocation(program, "tex");
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

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

		glBindVertexArray(0);
	}

	void Triangle::init_texture()
	{

	}



}//Namespace