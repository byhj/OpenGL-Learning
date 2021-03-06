#ifndef Scene_H
#define Scene_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "ogl/model.h"
#include "ogl/camera.h"

namespace byhj
{

	class Scene
	{
	public:
		Scene(): shadowFlag(false){}
		~Scene(){}

	public:
		void Init();
		void Render(const ogl::MvpMatrix &matrix, const ogl::Camera &camera);
		void Shutdown();
		void ChangeShadow();
		void init_fbo(int sw, int sh);
		GLuint GetDepthMap() const
		{
			return depth_tex;
		}
	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();
		void init_texture();

		void RenderQuad();
		void RenderCube();
		void RenderScene(GLuint program);

		GLuint cubeVAO, planeVAO, cubeVBO, planeVBO;
		GLuint woodTex;
		GLuint scene_prog, shadow_prog;
		GLuint fbo, depth_tex;
		GLboolean shadowFlag;
		ogl::Shader SceneShader, ShadowShader;
	};


}

#endif