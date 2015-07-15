#ifndef CUBE_H
#define CUBE_H

#include "ogl/oglShader.h"
#include "ogl/camera.h"
#include <glfw/glfw3.h>

namespace byhj
{

class Cube
{
public:
	Cube(){}
	~Cube() {}

public:
	void Init();
	void Render(const glm::mat4 &viewMat, float zoom, float aspect);
	void Shutdown();

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();

	GLuint vao, vbo, program;
	GLuint faceTex, containerTex;
	GLuint faceTex_loc, contaninerTex_loc, mvp_loc;
    OGLShader CubeShader;			
};

}

#endif