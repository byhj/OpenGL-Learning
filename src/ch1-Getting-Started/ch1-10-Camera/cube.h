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
	Cube():camera( glm::vec3(0.0f, 0.0f, 3.0f) ) 
	{
		lastX = 1000 / 2.0f;
		lastY = 800 / 2.0f;
		firstMouse = true;
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		for (int i = 0; i != 1024; ++ i)
			keys[i] = false;
	}
	~Cube() {}

public:
	void Init();
	void Render();
	void Shutdown();

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void movement(GLFWwindow *window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();
	void init_texture();

	// Camera
	Camera camera;
	bool keys[1024];
	GLfloat lastX, lastY ;
	bool firstMouse;
	GLfloat deltaTime;
	GLfloat lastFrame;


	GLuint vao, vbo, program;
	GLuint faceTex, containerTex;
	GLuint faceTex_loc, contaninerTex_loc, mvp_loc;
    OGLShader CubeShader;			
};

}

#endif