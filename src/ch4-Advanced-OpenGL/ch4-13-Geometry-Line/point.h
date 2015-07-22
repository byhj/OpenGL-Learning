#ifndef Point_H
#define Point_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Point
	{
	public:
		Point(): program(0), vao(0), vbo(0), PointShader("Point Shader") {}
		~Point() {}

	public:
		void Init();
		void Render(const const byhj::MvpMatrix &matrix);
		void Shutdown();

	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();
		void init_texture();

		GLuint vao, vbo, program;
		byhj::Shader PointShader;			
	};

}

#endif