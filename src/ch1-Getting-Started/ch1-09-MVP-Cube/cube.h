#ifndef CUBE_H
#define CUBE_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"

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
	GLuint faceTex          = ogl::VALUE;
	GLuint containerTex     = ogl::VALUE;
	GLuint faceTex_loc      = ogl::VALUE;
	GLuint containerTex_loc = ogl::VALUE;
	GLuint mvp_loc    = ogl::VALUE;
	GLuint program          = ogl::VALUE;

	ogl::Shader CubeShader ={ "Cube Shader" };		
};

}

#endif