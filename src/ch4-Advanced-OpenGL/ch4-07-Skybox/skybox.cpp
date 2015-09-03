#include "Skybox.h"
#include "ogl/loadTexture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
#pragma region VertexData

	const static GLfloat VertexData[] = {
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f

	};

#pragma endregion

	void Skybox::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Skybox::Render(const const ogl::MvpMatrix &matrix)
	{
		glUseProgram(program);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture); 

	// Remove any translation component of the view matrix
		glm::mat4 view  = glm::mat4( glm::mat3(matrix.view) );
		glm::mat4 proj  = matrix.proj;
		glm::mat4 model = matrix.model;
		glUniformMatrix4fv(view_loc, 1, GL_FALSE,  &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE,  &proj[0][0]);
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Skybox::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Skybox::init_shader()
	{
		SkyboxShader.init();
		SkyboxShader.attach(GL_VERTEX_SHADER,  "Skybox.vert");
		SkyboxShader.attach(GL_FRAGMENT_SHADER, "Skybox.frag");
		SkyboxShader.link();
		SkyboxShader.info();
		program = SkyboxShader.GetProgram();
		model_loc = glGetUniformLocation(program, "model");
		view_loc  = glGetUniformLocation(program, "view");
		proj_loc  = glGetUniformLocation(program, "proj");
		tex_loc   = glGetUniformLocation(program, "skybox");
	}

	void Skybox::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Skybox::init_vertexArray()
	{	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 3, (GLvoid*)(NULL));

		glBindVertexArray(0);
	}

	void Skybox::init_texture()
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