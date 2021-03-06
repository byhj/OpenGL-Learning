#ifndef CUBE_H
#define CUBE_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"

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
	void Render(const const ogl::MvpMatrix &matrix);
	void Shutdown();

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();

	GLuint vao	   = ogl::VALUE;
	GLuint vbo	   = ogl::VALUE;
	GLuint program = ogl::VALUE;
	GLuint mvp_loc = ogl::VALUE;
	ogl::Shader CubeShader = {"Cube Shader" };
};

}

#endif