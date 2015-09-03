#ifndef Planet_H
#define Planet_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "ogl/model.h"

namespace byhj
{

	class Planet
	{
	public:
		Planet(): vao(0), vbo(0), program(0) {}
		~Planet(){}

	public:
		void Init();
		void Render(const ogl::MvpMatrix &matrix);
		void Shutdown();

	private:

		void init_buffer();
		void init_vertexArray();
		void init_shader();

		GLuint vao, vbo, instanceVBO;
		GLuint program;
		ogl::Shader PlanetShader;
		byhj::Model planetObj;
	};


}

#endif