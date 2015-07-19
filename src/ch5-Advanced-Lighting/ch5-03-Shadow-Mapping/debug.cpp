#include "Debug.h"

#include "ogl/loadTexture.h"

namespace byhj
{
#pragma region VertexData

	GLfloat DebugVertices[] = 
	{
		// Positions             // Texture Coords
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	};
#pragma endregion

	void Debug::Init()
	{
		init_buffer();
		init_vertexArray();
		init_shader();
	}

	void Debug::Render(byhj::MvpMatrix matrix, const GLuint &depth_tex)
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
	    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Debug::Shutdown()
	{
		glDeleteProgram(program);
	}

	void Debug::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(DebugVertices), &DebugVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Debug::init_vertexArray()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		glBindVertexArray(0);
	}

	void Debug::init_shader()
	{
		DebugShader.init();
		DebugShader.attach(GL_VERTEX_SHADER,   "debug.vert");
		DebugShader.attach(GL_FRAGMENT_SHADER, "debug.frag");
		DebugShader.link();
		DebugShader.use();
		program = DebugShader.GetProgram();
	}

	void Debug::init_texture()
	{
	}

}