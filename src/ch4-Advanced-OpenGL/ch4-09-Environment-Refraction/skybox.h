#ifndef Skybox_H
#define Skybox_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Skybox
	{
	public:
		Skybox(): program(0), vao(0), vbo(0), SkyboxShader("Skybox Shader") {}
		~Skybox() {}

	public:
		void Init();
		void Render(const const ogl::MvpMatrix &matrix);
		void Shutdown();

	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();
		void init_texture();

		GLuint vao, vbo, program;
		GLuint cubemap_texture, tex_loc;
		GLuint model_loc, view_loc, proj_loc;
		ogl::Shader SkyboxShader;			
	};

}

#endif