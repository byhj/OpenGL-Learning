#ifndef Window_H
#define Window_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Triangle
	{
	public:
		Triangle(): program(0), vao(0), vbo(0), WindowShader("Triangle Shader") {}
		~Triangle() {}

	public:
		void Init();
		void Render(const const byhj::MvpMatrix &matrix, const GLuint &textureID);
		void Shutdown();

	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();
		void init_texture();

		GLuint vao, vbo, program;
		GLuint texture, tex_loc;
		OGLShader WindowShader;			
	};

}

#endif