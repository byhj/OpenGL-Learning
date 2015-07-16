#ifndef CUBE_H
#define CUBE_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/camera.h"

#include <glfw/glfw3.h>

namespace byhj
{

class Cube
{
public:
	Cube(): program(0), vao(0), vbo(0), CubeShader("Cube Shader") {}
	~Cube() {}

public:
	void Init();
	void Render(const byhj::MvpMatrix matrix, const byhj::Camera camera);
	void Shutdown();

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();

	GLuint vao, vbo, program;
	GLuint model_loc ,view_loc, proj_loc;
	GLuint diffuse_tex, specular_tex;
    OGLShader CubeShader;			
};

}

#endif