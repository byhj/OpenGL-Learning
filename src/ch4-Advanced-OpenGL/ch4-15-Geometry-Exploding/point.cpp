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

	void Point::Render(const const ogl::MvpMatrix &matrix)
	{
		glUseProgram(program);

		float time = glfwGetTime();
		glUniform1f(glGetUniformLocation(program, "time"), time);

		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -8.0f, -15.0f))
		              	* glm::rotate(glm::mat4(1.0f),glm::radians(time* 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &proj[0][0]);


		//set the light unfirom
		glm::vec3 diffuseColor = glm::vec3(0.8f); // Decrease the influence
		glm::vec3 ambientColor = glm::vec3(0.8f); // Low influence
		glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
		glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

		objModel.Draw(program);

		glUseProgram(0);
	}

	void Point::Shutdown()
	{
		glDeleteProgram(program);
	}

	void Point::init_shader()
	{
		modelShader.init();
		modelShader.attach(GL_VERTEX_SHADER,  "model.vert");
		modelShader.attach(GL_GEOMETRY_SHADER, "model.geom");
		modelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
		modelShader.link();
		modelShader.use();
		modelShader.info();

		program = modelShader.GetProgram();

		model_loc = glGetUniformLocation(program,  "model");
		view_loc  = glGetUniformLocation(program,  "view");
		proj_loc  = glGetUniformLocation(program,  "proj");

		GLint matDiffuseLoc = glGetUniformLocation(program, "material.diffuse");
		GLint matSpecularLoc = glGetUniformLocation(program, "material.specular");
		GLint matShineLoc = glGetUniformLocation(program, "material.shininess");
		glUniform3fv(matSpecularLoc, 1, &glm::vec3(0.5f, 0.5f, 0.5f)[0]);
		glUniform1f(matShineLoc, 64.0f);
		glUniform1i(matDiffuseLoc, 0);
		lightAmbientLoc = glGetUniformLocation(program, "light.ambient");
		lightDiffuseLoc = glGetUniformLocation(program, "light.diffuse");
		lightSpecularLoc = glGetUniformLocation(program,"light.specular");
	}

	void Point::init_buffer()
	{
		objModel.loadModel("../../../media/objects/nanosuit/nanosuit.obj");
	}

	void Point::init_vertexArray()
	{	
	}

	void Point::init_texture()
	{

	}



}//Namespace