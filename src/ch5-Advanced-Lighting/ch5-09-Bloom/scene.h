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
		Scene(): bloom(true), exposure(1.0f) {}
		~Scene(){}

	public:
		void Init();
		void Render(const byhj::MvpMatrix &matrix, const byhj::Camera &camera);
		void Shutdown();
		void ChangeShadow();
		void init_fbo(int sw, int sh);

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();
		void init_texture();

		void RenderQuad();
		void RenderCube();

		GLuint cubeVAO, planeVAO, cubeVBO, planeVBO;
		GLuint woodTex , containerTex;
		GLuint light_prog, bloom_prog, blur_prog, final_prog;
		OGLShader lightShader, bloomShader, blurShader, finalShader;

		GLuint pingpongFBO[2];
		GLuint pingpongColorbuffers[2];
		GLuint colorBuffers[2];
		GLuint hdrFBO;
		GLboolean bloom; // Change with 'Space'
		GLfloat exposure; // Change with Q and E
	};


}

#endif