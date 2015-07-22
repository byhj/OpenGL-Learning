#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/oglApp.h"
#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

namespace byhj
{

class Triangle
{
public:
	Triangle() = default;
	~Triangle() = default;

public:

	void Init()	   ;
	void Render()  ;
	void Shutdown();

private:

	void update();
	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint vbo     = byhj::OGL_VALUE;
	GLuint vao     = byhj::OGL_VALUE;
	GLuint program = byhj::OGL_VALUE;
	GLuint color_loc = byhj::OGL_VALUE;

	byhj::Shader TriangleShader = { "Triangle Shader" };
};

}

#endif