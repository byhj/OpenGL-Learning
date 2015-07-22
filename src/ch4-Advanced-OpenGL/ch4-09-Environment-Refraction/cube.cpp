#include "cube.h"
#include "ogl/loadTexture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
	void Cube::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Cube::Render(const const byhj::MvpMatrix &matrix)
	{
		glUseProgram(program);
		glBindVertexArray(vao);

		glUniform1i(tex_loc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);

		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;
		glm::mat4 model = matrix.model;
		glUniformMatrix4fv(view_loc, 1, GL_FALSE,  &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE,  &proj[0][0]);
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);

		objModel.Draw(program);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Cube::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Cube::init_shader()
	{
		CubeShader.init();
		CubeShader.attach(GL_VERTEX_SHADER,   "model.vert");
		CubeShader.attach(GL_FRAGMENT_SHADER, "model.frag");
		CubeShader.link();
		CubeShader.info();
		program = CubeShader.GetProgram();
		model_loc = glGetUniformLocation(program, "model");
		view_loc  = glGetUniformLocation(program, "view");
		proj_loc  = glGetUniformLocation(program, "proj");
		tex_loc   = glGetUniformLocation(program, "skybox");
	}

	void Cube::init_buffer()
	{
		objModel.loadModel("../../../media/objects/nanosuit/nanosuit.obj");
	}

	void Cube::init_vertexArray()
	{	

	}

	void Cube::init_texture()
	{
		// Cubemap (Skybox)
		std::vector<std::string> faces;
		faces.push_back("../../../media/textures/skybox/right.jpg");
		faces.push_back("../../../media/textures/skybox/left.jpg");
		faces.push_back("../../../media/textures/skybox/top.jpg");
		faces.push_back("../../../media/textures/skybox/bottom.jpg");
		faces.push_back("../../../media/textures/skybox/back.jpg");
		faces.push_back("../../../media/textures/skybox/front.jpg");
		cubemap_texture = loadCubeMap(faces);
	}



}//Namespace