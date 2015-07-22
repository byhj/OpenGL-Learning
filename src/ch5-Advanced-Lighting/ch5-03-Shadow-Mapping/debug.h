#ifndef Debug_H
#define Debug_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/model.h"
#include "ogl/camera.h"

namespace byhj
{

	class Debug
	{
	public:
		Debug(): vao(0), vbo(0), program(0){}
		~Debug(){}

	public:
		void Init();
		void Render(const byhj::MvpMatrix &matrix, const GLuint &depth_tex);
		void Shutdown();

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();
		void init_texture();

		GLuint vao, vbo;
		GLuint program;
		byhj::Shader DebugShader;
	};


}

#endif