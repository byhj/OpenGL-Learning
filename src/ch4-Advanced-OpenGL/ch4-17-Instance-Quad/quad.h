#ifndef Quad_H
#define Quad_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

namespace byhj
{

class Quad
{
public:
	Quad(): vao(0), vbo(0), program(0) {}
	~Quad(){}

public:
	void Init();
	void Render(const byhj::MvpMatrix &matrix);
	void Shutdown();

private:

	void init_buffer();
	void init_vertexArray();
	void init_shader();

	GLuint vao, vbo, instanceVBO;
	GLuint program;
	byhj::Shader QuadShader;
};


}

#endif