#include "Plane.h"
#include "ogl/loadTexture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
	void Plane::Init()
	{
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void Plane::Render(const byhj::MvpMatrix matrix, const byhj::Camera camera)
	{
		glUseProgram(program);

		glm::mat4 model = matrix.model; 
		glm::mat4 view  = matrix.view;
		glm::mat4 proj  = matrix.proj;

		glUniformMatrix4fv(view_loc, 1, GL_FALSE,  &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE,  &proj[0][0]);
		// Render normal-mapped quad

		glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
	    glm::vec3 camPos = camera.GetPos();

		// Render normal-mapped quad
		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * -10), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // Rotates the quad to show normal mapping works in all directions
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		
		glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(program, "viewPos"), 1, &camPos[0]);
		glUniform1f(glGetUniformLocation(program, "height_scale"), height_scale);
		glUniform1i(glGetUniformLocation(program, "parallax"), parallax_mapping);
		glUniform1i(glGetUniformLocation(program, "diffuseMap"), 0);
		glUniform1i(glGetUniformLocation(program, "normalMap"), 1);
		glUniform1i(glGetUniformLocation(program, "depthMap"), 2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, heightMap);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
		//model = glm::mat4();
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.1f));
		//glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);

		//glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glBindVertexArray(0);

		glUseProgram(0);
	}

	void Plane::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Plane::init_shader()
	{
		PlaneShader.init();
		PlaneShader.attach(GL_VERTEX_SHADER,   "parallax_mapping.vert");
		PlaneShader.attach(GL_FRAGMENT_SHADER, "parallax_mapping.frag");
		PlaneShader.link();
		PlaneShader.info();
		program = PlaneShader.GetProgram();

		model_loc = glGetUniformLocation(program, "model");
		view_loc  = glGetUniformLocation(program, "view");
		proj_loc  = glGetUniformLocation(program, "proj");
	}

	void Plane::init_buffer()
	{
		// positions
		glm::vec3 pos1(-1.0, 1.0, 0.0);
		glm::vec3 pos2(-1.0, -1.0, 0.0);
		glm::vec3 pos3(1.0, -1.0, 0.0);
		glm::vec3 pos4(1.0, 1.0, 0.0);
		// texture coordinates
		glm::vec2 uv1(0.0, 1.0);
		glm::vec2 uv2(0.0, 0.0);
		glm::vec2 uv3(1.0, 0.0);
		glm::vec2 uv4(1.0, 1.0);
		// normal vector
		glm::vec3 nm(0.0, 0.0, 1.0);

		// calculate tangent/bitangent vectors of both triangles
		glm::vec3 tangent1, bitangent1;
		glm::vec3 tangent2, bitangent2;
		// - triangle 1
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent1 = glm::normalize(tangent1);

		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent1 = glm::normalize(bitangent1);

		// - triangle 2
		edge1 = pos3 - pos1;
		edge2 = pos4 - pos1;
		deltaUV1 = uv3 - uv1;
		deltaUV2 = uv4 - uv1;

		f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent2 = glm::normalize(tangent2);


		bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent2 = glm::normalize(bitangent2);


		GLfloat quadVertices[] = {
			// Positions            // normal         // TexCoords  // Tangent                          // Bitangent
			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
			pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
			pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
		};

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	}

	void Plane::init_vertexArray()
	{	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));

		glBindVertexArray(0);
	}

	void Plane::init_texture()
	{
		diffuseMap = loadTexture("../../../media/textures/brickwall.jpg");
		normalMap = loadTexture("../../../media/textures/brickwall_normal.jpg");
		heightMap = loadTexture("../../../resources/textures/bricks2_disp.jpg");
		//GLuint diffuseMap = loadTexture("../../../resources/textures/wood.png");
		//GLuint normalMap = loadTexture("../../../resources/textures/toy_box_normal.png");
		//GLuint heightMap = loadTexture("../../../resources/textures/toy_box_disp.png");
	}



}//Namespace