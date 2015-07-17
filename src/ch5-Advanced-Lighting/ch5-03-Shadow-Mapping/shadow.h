#ifndef Shadow_H
#define Shadow_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/model.h"
#include "ogl/camera.h"

namespace byhj
{

	class Shadow
	{
	public:
		Shadow(): vao(0), vbo(0), program(0), blinn(false) {}
		~Shadow(){}

	public:
		void Init();
		void Render(byhj::MvpMatrix matrix, const byhj::Camera &camera);
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
		OGLShader ShadowShader;
		GLboolean blinn;
	};


}

#endif