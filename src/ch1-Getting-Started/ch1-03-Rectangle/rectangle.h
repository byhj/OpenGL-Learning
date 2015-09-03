#ifndef WINDOW_H
#define WINDOW_H

#include "ogl/App.h"
#include "ogl/Shader.h"
#include "ogl/Utility.h"

namespace byhj
{

class Rectangle
{
public:
	Rectangle() = default;
	~Rectangle() = default;

public:

	void Init()	   ;
	void Render()  ;
	void Shutdown();


private:

	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint vao = ogl::VALUE;
	GLuint vbo = ogl::VALUE;
	GLuint ibo = ogl::VALUE;
	GLuint program = ogl::VALUE;

	ogl::Shader RectangleShader = { "Rectangle Shader" };
};

}

#endif