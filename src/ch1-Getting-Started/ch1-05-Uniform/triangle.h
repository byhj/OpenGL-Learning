#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/App.h"
#include "ogl/Shader.h"
#include "ogl/Utility.h"

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

	GLuint vbo     = ogl::VALUE;
	GLuint vao     = ogl::VALUE;
	GLuint program = ogl::VALUE;
	GLuint color_loc = ogl::VALUE;

	ogl::Shader TriangleShader = { "Triangle Shader" };
};

}

#endif