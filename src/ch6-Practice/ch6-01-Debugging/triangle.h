#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/App.h"
#include "ogl/Shader.h"


namespace byhj
{

class Triangle
{
public:
	Triangle() :program(0), vao(0), vbo(0) { }
	~Triangle() {}

public:

	void Init();
	void Render() ;
	void Shutdown() ;

private:

	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint vbo, vao, program;
	ogl::Shader TriangleShader;
};

}

#endif