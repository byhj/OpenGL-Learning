

#include "Grass.h"
#include "ogl/loadTexture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
#pragma region VertexData

	const static GLfloat VertexData[] = 
	{
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

#pragma endregion

	void Grass::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Grass::Render(const byhj::MvpMatrix matrix)
	{
		glUseProgram(program);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 model = matrix.model; 
		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;

		glUniformMatrix4fv(view_loc, 1, GL_FALSE,  &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE,  &proj[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		for (GLuint i = 0; i < vecPos.size(); i++)
		{
			model = glm::mat4();
			model = glm::translate(model, vecPos[i]);
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Grass::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Grass::init_shader()
	{
		GrassShader.init();
		GrassShader.attach(GL_VERTEX_SHADER,   "Grass.vert");
		GrassShader.attach(GL_FRAGMENT_SHADER, "Grass.frag");
		GrassShader.link();
		GrassShader.info();
		program = GrassShader.GetProgram();

		model_loc = glGetUniformLocation(program, "model");
		view_loc  = glGetUniformLocation(program, "view");
		proj_loc  = glGetUniformLocation(program, "proj");
		tex_loc   = glGetUniformLocation(program, "tex");
	}

	void Grass::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		vecPos.push_back(glm::vec3(-1.5f,  0.0f, -0.48f));
		vecPos.push_back(glm::vec3( 1.5f,  0.0f,  0.51f));
		vecPos.push_back(glm::vec3( 0.0f,  0.0f,  0.7f));
		vecPos.push_back(glm::vec3(-0.3f,  0.0f, -2.3f));
		vecPos.push_back(glm::vec3( 0.5f,  0.0f, -0.6f));
	}

	void Grass::init_vertexArray()
	{	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		glBindVertexArray(0);
	}

	void Grass::init_texture()
	{
		texture = loadTexture("../../../media/textures/grass.png", true);
	}



}//Namespace