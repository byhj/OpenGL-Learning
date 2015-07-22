#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/oglApp.h"
#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

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

	GLuint faceTex          = byhj::OGL_VALUE;
	GLuint containerTex     = byhj::OGL_VALUE;
	GLuint faceTex_loc      = byhj::OGL_VALUE;
	GLuint containerTex_loc = byhj::OGL_VALUE;
	GLuint program          = byhj::OGL_VALUE;

	byhj::Shader RectangleShader = { "Rectangle Shader" };
};

}

#endif