#ifndef CUBE_H
#define CUBE_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

namespace byhj
{

class Cube
{
public:
	Cube() {}
	~Cube() {}

public:
	void Init();
	void Render(float aspect);
	void Shutdown();

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();


	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint faceTex          = byhj::OGL_VALUE;
	GLuint containerTex     = byhj::OGL_VALUE;
	GLuint faceTex_loc      = byhj::OGL_VALUE;
	GLuint containerTex_loc = byhj::OGL_VALUE;
	GLuint mvp_loc    = byhj::OGL_VALUE;
	GLuint program          = byhj::OGL_VALUE;

	byhj::Shader CubeShader ={ "Cube Shader" };		
};

}

#endif