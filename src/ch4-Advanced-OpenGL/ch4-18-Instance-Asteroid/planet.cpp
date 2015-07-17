#include "Planet.h"

namespace byhj
{

	void Planet::Init()
	{
		init_buffer();
		init_vertexArray();
		init_shader();
	}

	void Planet::Render(byhj::MvpMatrix matrix)
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		glm::mat4 view = matrix.view;
		glm::mat4 proj = matrix.proj;

		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, &mvp[0][0]);
		planetObj.Draw(program);

		glUseProgram(0);
		glBindVertexArray(0);

	}

	void Planet::Shutdown()
	{
		glDeleteProgram(program);
	}

	void Planet::init_buffer()
	{
	   planetObj.loadModel("../../../media/objects/planet/planet.obj");
	}

	void Planet::init_vertexArray()
	{

	}

	void Planet::init_shader()
	{
		PlanetShader.init();
		PlanetShader.attach(GL_VERTEX_SHADER, "Planet.vert");
		PlanetShader.attach(GL_FRAGMENT_SHADER, "Planet.frag");
		PlanetShader.link();
		PlanetShader.use();
		program = PlanetShader.GetProgram();
	}

}