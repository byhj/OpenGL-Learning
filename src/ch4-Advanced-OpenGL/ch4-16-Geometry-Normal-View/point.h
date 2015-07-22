#ifndef Point_H
#define Point_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/model.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Point
	{
	public:
		Point(): program(0), vao(0), vbo(0), modelShader("Model Shader") {}
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
		byhj::Shader modelShader;
		GLuint model_loc, view_loc, proj_loc;
		byhj::Model objModel;
		GLint lightSpecularLoc, lightDiffuseLoc, lightAmbientLoc;
	};

}

#endif