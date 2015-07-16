#include "cube.h"

namespace byhj
{

#pragma region VertexData

	static const glm::vec3 Pos[4] = 
	{
		glm::vec3(-0.75f,  0.75f, 0.0f),
		glm::vec3( 0.75f,  0.75f, 0.0f),
		glm::vec3(-0.75f, -0.75f, 0.0f),
		glm::vec3( 0.75f, -0.75f, 0.0f),
	};

	const static GLfloat VertexData[] = {
		// front
		-0.25, -0.25,  0.25,
		0.25, -0.25,  0.25,
		0.25,  0.25,  0.25,
		-0.25,  0.25,  0.25,
		// back
		-0.25, -0.25, -0.25,
		0.25, -0.25, -0.25,
		0.25,  0.25, -0.25,
		-0.25,  0.25, -0.25,
	};
	const static GLushort ElementData[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		3, 2, 6,
		6, 7, 3,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// left
		4, 0, 3,
		3, 7, 4,
		// right
		1, 5, 6,
		6, 2, 1,
	};


#pragma endregion

void Cube::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

void Cube::Render(byhj::MvpMatrix matrix)
{
	glBindVertexArray(vao);
	glUseProgram(program);

	glm::mat4 proj = matrix.proj;
    glm::mat4 view = matrix.view;

	// binding -- ubo -- 
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &proj[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);

	//we render four cube with different position
	for (int i = 0; i != 4; ++i)
	{
		glm::mat4 model;
		model = glm::translate(model, Pos[i]);	// Move top-left
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glUniform1i(glGetUniformLocation(program, "color"), i);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	}

	glUseProgram(0);
	glBindVertexArray(0);

}

void Cube::Shutdown()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ubo);
}

void Cube::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);    //load the vertex data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElementData), ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Cube::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(0);
}

void Cube::init_shader()
{
	CubeShader.init();
	CubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	CubeShader.link();
	CubeShader.use();
	program = CubeShader.GetProgram();
}

}