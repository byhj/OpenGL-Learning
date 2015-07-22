#include "Point.h"
#include "ogl/loadTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{

	void Point::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Point::Render(const const byhj::MvpMatrix &matrix)
	{

		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;
		glm::mat4 model = matrix.model;
		glm::mat4 mvp   = proj * view * model;

		glUseProgram(program);
		glBindVertexArray(vao);

		glBindTexture(GL_TEXTURE_2D, sprite_texture);
		glUniform1i(glGetUniformLocation(program, "sprite_texture"), 0);

		glDrawArrays(GL_POINTS, 0, 9);

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
		PointShader.attach(GL_VERTEX_SHADER,  "Point.vert");
		PointShader.attach(GL_FRAGMENT_SHADER, "Point.frag");
		PointShader.link();
		PointShader.info();
		program = PointShader.GetProgram();
	}

	void Point::init_buffer()
	{
	}

	void Point::init_vertexArray()
	{	
	}

	void Point::init_texture()
	{
		//Notice to use texture alpha value
		sprite_texture = loadTexture("../../../media/textures/awesomeface.png", true);
	}



}//Namespace