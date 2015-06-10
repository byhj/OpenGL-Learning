#include <common/learnApp.h>
#include <common/shader.h>
#include <iostream>


class ShaderApp: public byhj::Application
{
public:
	ShaderApp(){};
	~ShaderApp(){};

	void ShaderApp::v_Init()
	{		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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

	GLuint vbo, vao, program;
	Shader TriangleShader;
};

CALL_MAIN(ShaderApp);


const static GLfloat VertexData[] = {
	// Positions    // Colors
	0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   // Bottom Right
   -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   // Bottom Left
	0.0f,  0.5f,   0.0f, 0.0f, 1.0f    // Top 
};

void ShaderApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "triangle.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "triangle.frag");
	TriangleShader.link();
	TriangleShader.use();
	TriangleShader.interfaceInfo();
	program = TriangleShader.GetProgram();
}

void ShaderApp::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ShaderApp::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}
