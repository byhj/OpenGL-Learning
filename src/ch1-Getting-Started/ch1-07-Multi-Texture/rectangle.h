#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/App.h"
#include "ogl/Shader.h"
#include "ogl/Utility.h"

namespace byhj
{

class Rectangle
{
public:
	Rectangle() = default;
	~Rectangle() = default;

public:

	void Init();
	void Render();
	void Shutdown();

private:

	void init_buffer();
	void init_shader();
	void init_vertexArray();
	void init_texture();

	GLuint faceTex          = ogl::VALUE;
	GLuint containerTex     = ogl::VALUE;
	GLuint faceTex_loc      = ogl::VALUE;
	GLuint containerTex_loc = ogl::VALUE;
	GLuint program          = ogl::VALUE;

	ogl::Shader RectangleShader = { "Rectangle Shader" };
};

}

#endif