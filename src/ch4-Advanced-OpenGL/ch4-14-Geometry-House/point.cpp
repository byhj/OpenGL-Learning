#include "Point.h"
#include "ogl/loadTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
	// Vertex data
	static const GLfloat VertexData[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // Bottom-left
	};

	void Point::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Point::Render(const byhj::MvpMatrix matrix)
	{

		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;
		glm::mat4 model = matrix.model;
		glm::mat4 mvp   = proj * view * model;

		glUseProgram(program);
		glBindVertexArray(vao);

		glDrawArrays(GL_POINTS, 0, 5);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Point::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Point::init_shader()
	{
		PointShader.init();
		PointShader.attach(GL_VERTEX_SHADER,  "house.vert");
		PointShader.attach(GL_GEOMETRY_SHADER, "house.geom");
		PointShader.attach(GL_FRAGMENT_SHADER, "house.frag");
		PointShader.link();
		program = PointShader.GetProgram();
	}

	void Point::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Point::init_vertexArray()
	{	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

		glBindVertexArray(0);
	}

	void Point::init_texture()
	{

	}



}//Namespace