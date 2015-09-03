#include "Plane.h"

#include "ogl/loadTexture.h"

namespace byhj
{
#pragma region VertexData

	GLfloat planeVertices[] = {
		// Positions          // Normals         // Texture Coords
		8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
		-8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,

		8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
		-8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
		8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
	};
#pragma endregion

	void Plane::Init()
	{
		init_buffer();
		init_vertexArray();
		init_shader();
		init_texture();
	}

	void Plane::Render(const ogl::MvpMatrix &matrix, const ogl::Camera &camera)
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glm::mat4 model = matrix.model;
		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;

		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"),  1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "proj"),  1, GL_FALSE, &proj[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTex);
		glUniform1i(woodTex_loc, 0);

		// Set light uniforms
		glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 camPos = camera.GetPos();

		glUniform3fv( glGetUniformLocation(program,  "lightPos"), 1, &lightPos[0]);
		glUniform3fv( glGetUniformLocation(program,  "viewPos"), 1,  &camPos[0]);
		glUniform1i(  glGetUniformLocation(program, "blinn"), blinn);
		glUniform1i(  glGetUniformLocation(program, "tex"), 0);
	
		// Floor
		glDrawArrays(GL_TRIANGLES, 0, 6);	

		glUseProgram(0);
		glBindVertexArray(0);

	}

	void Plane::Shutdown()
	{
		glDeleteProgram(program);
	}

	void Plane::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Plane::init_vertexArray()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

		glBindVertexArray(0);
	}

	void Plane::init_shader()
	{
		PlaneShader.init();
		PlaneShader.attach(GL_VERTEX_SHADER, "light.vert");
		PlaneShader.attach(GL_FRAGMENT_SHADER, "light.frag");
		PlaneShader.link();
		PlaneShader.use();
		program = PlaneShader.GetProgram();
		woodTex_loc  = glGetUniformLocation(program, "woodTex");
	}

	void Plane::init_texture()
	{
		woodTex = ogl::loadTexture("../../../media/textures/wood.png");
	}

	void Plane::ChangeLight()
	{
		blinn = !blinn;
	}

}