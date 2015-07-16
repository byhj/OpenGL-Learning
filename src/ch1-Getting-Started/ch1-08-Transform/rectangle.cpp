#include "rectangle.h"

#include "ogl/loadTexture.h"

namespace byhj
{

void Rectangle::init_shader()
{
	RectangleShader.init();
	RectangleShader.attach(GL_VERTEX_SHADER,   "texture.vert");
	RectangleShader.attach(GL_FRAGMENT_SHADER, "texture.frag");
	RectangleShader.link();
	RectangleShader.use();
	RectangleShader.interfaceInfo();
	program = RectangleShader.GetProgram();

	tex1_loc = glGetUniformLocation(program, "tex1");
	tex2_loc = glGetUniformLocation(program, "tex2");
	transform_loc = glGetUniformLocation(program, "transform");
	//Set the uniform should call glUseProgram();
	//Set tex1 is TEXTURE0 of GL_TEXTURE_2D, tex2 is TEXTURE2;
	glUniform1i(tex1_loc, 0);
	glUniform1i(tex2_loc, 1);
}

void Rectangle::init_buffer()
{

}

void Rectangle::init_vertexArray()
{

}

void Rectangle::init_texture()
{
	tex1 = loadTexture("../../../media/textures/container.jpg");
	tex2 = loadTexture("../../../media/textures/awesomeface.png");
}


}//Namespace
