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
	faceTex_loc = glGetUniformLocation(program, "faceTex");

	assert(containerTex_loc != byhj::OGL_VALUE);
	assert(faceTex_loc != byhj::OGL_VALUE);

}

void Rectangle::init_buffer()
{

}

void Rectangle::init_vertexArray()
{

}

void Rectangle::init_texture()
{
	containerTex = loadTexture("../../../media/textures/container.jpg");
	faceTex = loadTexture("../../../media/textures/awesomeface.png");
}


}//Namespace
