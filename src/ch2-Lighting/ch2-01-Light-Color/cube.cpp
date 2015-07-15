#include "cube.h"
#include "ogl/loadTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
#pragma region VertexData

	const static GLfloat VertexData[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

#pragma endregion

void Cube::Init()
{
	glEnable(GL_DEPTH_TEST);  

	init_shader();
	init_buffer();
	init_vertexArray();
	init_texture();
}

void Cube::Render(const glm::mat4 &viewMat, float zoom, float aspect)
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glUniform3f(glGetUniformLocation(prog_app, "objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(prog_app, "lightColor"), 1.0f, 1.0f, 1.0f);

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 proj = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 100.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), 60.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mvp = proj * view * model;
	glUniformMatrix4fv(glGetUniformLocation(prog_app, "mvp"), 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Cube::Shutdown()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Cube::init_shader()
{
	CubeShader.init();
	CubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	CubeShader.link();
	CubeShader.use();
	CubeShader.interfaceInfo();

	program = CubeShader.GetProgram();
	mvp_loc = glGetUniformLocation(program, "mvp_matrix");
	faceTex_loc = glGetUniformLocation(program, "faceTex");
	contaninerTex_loc = glGetUniformLocation(program, "contaninerTex");
	
	glUniform1i(contaninerTex_loc, 0);
	glUniform1i(faceTex_loc, 1);

	glUseProgram(0);
}

void Cube::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::init_vertexArray()
{	
	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	glGenVertexArrays(1, &vao_app);
	glBindVertexArray(vao_app);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

    glBindVertexArray(0);
}

void Cube::init_texture()
{

}



}//Namespace