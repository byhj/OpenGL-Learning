#ifndef Scene_H
#define Scene_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/model.h"
#include "ogl/camera.h"

namespace byhj
{

	class Scene
	{
	public:
		Scene(): vao(0), vbo(0), program(0){}
		~Scene(){}

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


		GLuint cubeVAO, planeVAO, cubeVBO, planeVBO;
		GLuint woodTex, woodTex_loc;
		GLuint program;
		OGLShader SceneShader;
	};


}

#endif