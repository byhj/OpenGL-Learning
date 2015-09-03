#include "rectangle.h"

#include "ogl/loadTexture.h"

namespace byhj
{

void Rectangle::Init()
{
	init_shader();
	init_buffer();
	init_vertexArray();
	init_texture();
}

void Rectangle::Render()
{
	glUseProgram(program);

	//We set the display mode is line
	glUniform1i(containerTex_loc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerTex);

	glUniform1i(faceTex_loc, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, faceTex);

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, &trans[0][0]);

	

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUseProgram(0);
}

void Rectangle::Shutdown()
{
	glDeleteProgram(program);
}

void Rectangle::init_shader()
{
	RectangleShader.init();
	RectangleShader.attach(GL_VERTEX_SHADER,   "texture.vert");
	RectangleShader.attach(GL_FRAGMENT_SHADER, "texture.frag");
	RectangleShader.link();
	RectangleShader.info();
	program = RectangleShader.GetProgram();

	containerTex_loc = glGetUniformLocation(program, "containerTex");
	faceTex_loc      = glGetUniformLocation(program, "faceTex");
	transform_loc    = glGetUniformLocation(program, "transform");

	assert(containerTex_loc != ogl::VALUE);
	assert(faceTex_loc != ogl::VALUE);
	assert(transform_loc != ogl::VALUE);

}

void Rectangle::init_buffer()
{

}

void Rectangle::init_vertexArray()
{

}

void Rectangle::init_texture()
{
	containerTex = ogl::loadTexture("../../../media/textures/container.jpg");
	faceTex = ogl::loadTexture("../../../media/textures/awesomeface.png");
}


}//Namespace
