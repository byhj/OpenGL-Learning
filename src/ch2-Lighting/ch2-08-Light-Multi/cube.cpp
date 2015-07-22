#include "cube.h"
#include "ogl/loadTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MANY_CUBES

namespace byhj
{
#pragma region VertexData

	// Positions of the point lights
	const static glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f)
	};

	const static glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};
	// Positions all containers
	const static glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	const static GLfloat VertexData[] = {
		// Positions          // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

#pragma endregion

void Cube::Init()
{
	init_shader();
	init_buffer();
	init_vertexArray();
	init_texture();
}

void Cube::Render(const const byhj::MvpMatrix &matrix, const byhj::Camera camera)
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glm::vec3 camPos = camera.GetPos();
	glm::vec3 camFront = camera.GetFront();

	glUniform1i(glGetUniformLocation(program, "material.diffuse"),  0);
	glUniform1i(glGetUniformLocation(program, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(program, "material.shininess"), 32.0f);
	GLint viewPosLoc = glGetUniformLocation(program, "viewPos");
	glUniform3fv(viewPosLoc, 1, &camPos[0]);

	// Directional light
	glUniform3f(glGetUniformLocation(program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
							
	// Point light 1				 program
	glUniform3f(glGetUniformLocation(program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);		
	glUniform3f(glGetUniformLocation(program, "pointLights[0].ambient"), pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);		
	glUniform3f(glGetUniformLocation(program, "pointLights[0].diffuse"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
	glUniform3f(glGetUniformLocation(program, "pointLights[0].specular"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
	glUniform1f(glGetUniformLocation(program, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[0].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(program, "pointLights[0].quadratic"), 0.032f);		
	// Point light 2				 program
	glUniform3f(glGetUniformLocation(program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);		
	glUniform3f(glGetUniformLocation(program, "pointLights[1].ambient"), pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);		
	glUniform3f(glGetUniformLocation(program, "pointLights[1].diffuse"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z); 
	glUniform3f(glGetUniformLocation(program, "pointLights[1].specular"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
	glUniform1f(glGetUniformLocation(program, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[1].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(program, "pointLights[1].quadratic"), 0.032f);		
	// Point light 3				 program
	glUniform3f(glGetUniformLocation(program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);		
	glUniform3f(glGetUniformLocation(program, "pointLights[2].ambient"), pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);		
	glUniform3f(glGetUniformLocation(program, "pointLights[2].diffuse"), pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z); 
	glUniform3f(glGetUniformLocation(program, "pointLights[2].specular") ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
	glUniform1f(glGetUniformLocation(program, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[2].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(program, "pointLights[2].quadratic"), 0.032f);		
	// Point light 4				 program
	glUniform3f(glGetUniformLocation(program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);		
	glUniform3f(glGetUniformLocation(program, "pointLights[3].ambient"), pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);		
	glUniform3f(glGetUniformLocation(program, "pointLights[3].diffuse"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z); 
	glUniform3f(glGetUniformLocation(program, "pointLights[3].specular"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
	glUniform1f(glGetUniformLocation(program, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[3].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(program, "pointLights[3].quadratic"), 0.032f);	
								
	// SpotLight					 program

	glUniform3fv(glGetUniformLocation(program, "spotLight.position"), 1, &camPos[0]);
	glUniform3fv(glGetUniformLocation(program, "spotLight.direction"), 1, &camFront[0]);
	glUniform3f(glGetUniformLocation(program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(program, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse_tex);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular_tex);

#ifdef MANY_CUBES
	for(GLuint i = 0; i < 10; i++) 
	{
		GLfloat angle = 20.0f * (i+1); 
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;
		glm::mat4 mvp = proj * view * model;

		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &proj[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
#else
	glm::mat4 model = matrix.model; 
	glm::mat4 view  = matrix.view;
	glm::mat4 proj  = matrix.proj;
	glm::mat4 mvp = proj * view * model;
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &proj[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
#endif

	glBindVertexArray(0);

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
	CubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	CubeShader.link();
	CubeShader.info();
	program = CubeShader.GetProgram();

	model_loc = glGetUniformLocation(program, "model");
	view_loc  = glGetUniformLocation(program, "view");
	proj_loc  = glGetUniformLocation(program, "proj");
}

void Cube::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::init_vertexArray()
{	
	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Cube::init_texture()
{
	diffuse_tex = loadTexture("../../../media/textures/container2.png");
	specular_tex = loadTexture("../../../media/textures/container2_specular.png");
}



}//Namespace