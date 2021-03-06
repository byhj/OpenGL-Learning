#ifndef Plane_H
#define Plane_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "ogl/model.h"
#include "ogl/camera.h"

namespace byhj
{

	class Plane
	{
	public:
		Plane(): vao(0), vbo(0), program(0), blinn(false) {}
		~Plane(){}

	public:
		void Init();
		void Render(const ogl::MvpMatrix &matrix, const ogl::Camera &camera);
		void Shutdown();
		void ChangeLight();

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();
		void init_texture();


		GLuint vao, vbo;
		GLuint woodTex, woodTex_loc;
		GLuint program;
		ogl::Shader PlaneShader;
		GLboolean blinn;
	};


}

#endif