#ifndef CUBE_H
#define CUBE_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"

namespace byhj
{

class Cube
{
public:
	Cube(): vao(0), vbo(0), ibo(0), ubo(0),  program(0) {}
	~Cube(){}

public:
	void Init();
	void Render(const ogl::MvpMatrix &matrix);
	void Shutdown();

private:

	void init_buffer();
	void init_vertexArray();
	void init_shader();

	GLuint vao, vbo, ibo, ubo;
	GLuint program;
	ogl::Shader CubeShader;
};


}

#endif