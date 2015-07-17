#ifndef Plane_H
#define Plane_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/camera.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Plane
	{
	public:
		Plane(): program(0), vao(0), vbo(0), height_scale(0.1f), parallax_mapping(true), 
			    PlaneShader("Plane Shader") {}
		~Plane() {}

	public:
		void Init();
		void Render(const byhj::MvpMatrix matrix, const byhj::Camera camera);
		void Shutdown();

		void AddHeightScale()
		{
			height_scale += 0.001f;
		}
		void MinusHeightScale()
		{
			height_scale -= 0.001f;
		}
		void ChangeMapping()
		{
			parallax_mapping = !parallax_mapping;
		}
	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();
		void init_texture();

		GLuint vao, vbo, program;
		GLuint texture, tex_loc;
		GLuint model_loc, view_loc, proj_loc;
		OGLShader PlaneShader;	
		GLuint diffuseMap, heightMap, normalMap; 
		GLboolean parallax_mapping;
		GLfloat height_scale;
	};

}

#endif