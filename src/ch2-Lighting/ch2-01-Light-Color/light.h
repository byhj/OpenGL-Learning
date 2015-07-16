#ifndef Light_H
#define Light_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Light
	{
	public:
		Light(): program(0), vao(0), vbo(0), LightShader("Light Shader"){}
		~Light() {}

	public:
		void Init();
		void Render(const byhj::MvpMatrix matrix);
		void Shutdown();

	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();
		void init_texture();

		GLuint vao, vbo, program;
		GLuint  mvp_loc;
		OGLShader LightShader;			
	};

}

#endif