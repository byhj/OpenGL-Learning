#ifndef Asteroid_H
#define Asteroid_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
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
		void Render(const byhj::MvpMatrix &matrix);
		void Shutdown();

	private:

		void init_buffer();
		void init_vertexArray();
		void init_shader();

		GLuint vao, vbo, instanceVBO;
		GLuint program;
		OGLShader AsteroidShader;
		byhj::Model rockObj;

	};


}

#endif