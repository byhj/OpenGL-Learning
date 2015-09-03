#ifndef Asteroid_H
#define Asteroid_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "ogl/model.h"

namespace byhj
{

	class Asteroid
	{
	public:
		Asteroid(): vao(0), vbo(0), program(0) {}
		~Asteroid(){}

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
		ogl::Shader AsteroidShader;
		byhj::Model rockObj;

	};


}

#endif