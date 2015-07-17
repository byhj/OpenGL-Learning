#include "Quad.h"

namespace byhj
{

#pragma region VertexData

	const static GLfloat VertexData[] = {
		// Positions   // Colors
		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		0.05f, 0.05f, 0.0f, 1.0f, 1.0f
	};


#pragma endregion

void Quad::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

void Quad::Render(byhj::MvpMatrix matrix)
{
	glBindVertexArray(vao);
	glUseProgram(program);

	// 100 triangles of 6 vertices each
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); 

	glUseProgram(0);
	glBindVertexArray(0);

}

void Quad::Shutdown()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &instanceVBO);
}

void Quad::init_buffer()
{
	glGenBuffers(1, &vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glm::vec2 translations[100];
	int index = 0;
	GLfloat offset = 0.1f;
	for (GLint y = -10; y < 10; y += 2)
	{
		for (GLint x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (GLfloat)x / 10.0f + offset;
			translation.y = (GLfloat)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Quad::init_vertexArray()
{
	glGenVertexArrays(1, &vao);  //initial the vertex array object
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);  
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL + sizeof(GLfloat)* 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Also set instance data
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//send the different value Every instance
	glVertexAttribDivisor(2, 1); 

	glBindVertexArray(0);
}

void Quad::init_shader()
{
	QuadShader.init();
	QuadShader.attach(GL_VERTEX_SHADER, "Quad.vert");
	QuadShader.attach(GL_FRAGMENT_SHADER, "Quad.frag");
	QuadShader.link();
	QuadShader.use();
	program = QuadShader.GetProgram();
}

}