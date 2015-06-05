#include <common/oglApp.h>
#include <common/shader.h>

#include <iostream>

const static GLfloat VertexData[] = {
	// Positions  
	0.5f, -0.5f,  
	-0.5f, -0.5f, 
	0.0f,  0.5f,  
};

class ShaderApp: public byhj::Application
{
public:
	 ShaderApp(){};
	 ~ShaderApp(){};

	 void ShaderApp::vInit()
	 {		
		 glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		 init_shader();
		 init_buffer();
		 init_vertexArray();
	 }

	 void vRender()
	 {
		 glClear(GL_COLOR_BUFFER_BIT);

		 glUseProgram(program);
		 glBindVertexArray(vao);

		 GLfloat time = glfwGetTime();
		 GLfloat redValue   = (sin(time) / 2) + 0.5;
		 GLfloat greenValue = (cos(time) / 2) + 0.5;
		 GLfloat blueValue  = (sin(time) / 2) + (cos(time) / 2);

		 glUniform4f(color_loc, redValue, greenValue, blueValue, 1.0f);
		 glDrawArrays(GL_TRIANGLES, 0, 3);

		 glBindVertexArray(0);
	 }

	 void vShutdown()
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
	GLuint color_loc;
};

CALL_MAIN(ShaderApp);

void ShaderApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "triangle.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "triangle.frag");
	TriangleShader.link();
	TriangleShader.use();
	program = TriangleShader.GetProgram();
	color_loc = glGetUniformLocation(program, "color");
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0 , 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

