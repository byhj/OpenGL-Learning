#ifndef CUBE_H
#define CUBE_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

#include <glfw/glfw3.h>

namespace byhj
{

class Cube
{
public:
	Cube() 	 = default;
	~Cube()	 = default;

public:
	void Init();
	void Render(const const byhj::MvpMatrix &matrix);
	void Shutdown();

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();

	GLuint vao	   = byhj::OGL_VALUE;
	GLuint vbo	   = byhj::OGL_VALUE;
	GLuint program = byhj::OGL_VALUE;
	GLuint mvp_loc = byhj::OGL_VALUE;
	byhj::Shader CubeShader = {"Cube Shader" };
};

}

#endif