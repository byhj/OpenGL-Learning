#include <common/learnApp.h>
#include <common/shader.h>
#include <glm/glm.hpp>

#include <iostream>

class TriangleApp: public byhj::Application
{
public:
	TriangleApp() { }
	~TriangleApp() {}

public:
	void v_Init()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
		glClearDepth(1.0f);

		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    glUseProgram(program);

	    glBindVertexArray(vao);
	    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
	    glBindVertexArray(0);
	}
	void v_Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

private:
	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint vbo, vao, program, color_loc;
	Shader triangleShader;
	GLuint mvp_matrix_loc;
	GLuint instanceVBO;
};

CALL_MAIN(TriangleApp);

const static GLsizei VertexCount(30);
const static GLsizeiptr VertexSize = sizeof(GLfloat)* VertexCount;
const static GLfloat VertexData[VertexCount] = 
{ //vertex data
	// Positions   // Colors
	-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
	0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
	-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

	-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
	0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
	0.05f, 0.05f, 0.0f, 1.0f, 1.0f
};

void TriangleApp::init_shader()
{
	triangleShader.init();
	triangleShader.attach(GL_VERTEX_SHADER, "quad.vert");
	triangleShader.attach(GL_FRAGMENT_SHADER, "quad.frag");
	triangleShader.link();
	program = triangleShader.GetProgram();
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
}

void TriangleApp::init_buffer()
{
	glGenBuffers(1, &vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
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

void TriangleApp::init_vertexArray()
{
	glGenVertexArrays(1, &vao);  //initial the vertex array object
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  //tranform the data to shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL + sizeof(GLfloat)* 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Also set instance data
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); //每个实例赋予不同属性
	glBindVertexArray(0);
}
