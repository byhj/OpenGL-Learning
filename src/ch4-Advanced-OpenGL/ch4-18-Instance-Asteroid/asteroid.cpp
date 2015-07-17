#include "Asteroid.h"

#include <glfw/glfw3.h>


namespace byhj
{
	static const int AMOUNT = 100000;

	void Asteroid::Init()
	{
		init_buffer();
		init_vertexArray();
		init_shader();
	}

	void Asteroid::Render(byhj::MvpMatrix matrix)
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glBindTexture(GL_TEXTURE_2D, rockObj.textures_loaded[0].id); // Note we also made the textures_loaded vector public (instead of private) from the model class.
	
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glm::mat4 view = matrix.view;
		glm::mat4 proj = matrix.proj;
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, &mvp[0][0]);

		for (GLuint i = 0; i < rockObj.meshes.size(); i++)
		{
			glBindVertexArray(rockObj.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, rockObj.meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, AMOUNT);
			glBindVertexArray(0);
		}

		glUseProgram(0);
	}

	void Asteroid::Shutdown()
	{
		glDeleteProgram(program);
	}

	void Asteroid::init_buffer()
	{

		rockObj.loadModel("../../../media/objects/rock/rock.obj");

		glm::mat4* modelMatrices = new glm::mat4[AMOUNT];
		srand(glfwGetTime()); // initialize random seed	
		GLfloat radius = 150.0f;
		GLfloat offset = 25.0f;

		for (GLuint i = 0; i < AMOUNT; i++)
		{
			glm::mat4 model;
			// 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
			GLfloat angle = (GLfloat)i / (GLfloat)AMOUNT * 360.0f;
			GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
			GLfloat x = sin(angle) * radius + displacement;
			displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
			GLfloat y = -2.5f + displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
			displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
			GLfloat z = cos(angle) * radius + displacement;
			model = glm::translate(model, glm::vec3(x, y, z));

			// 2. Scale: Scale between 0.05 and 0.25f
			GLfloat scale = (rand() % 20) / 100.0f + 0.05;
			model = glm::scale(model, glm::vec3(scale));

			// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
			GLfloat rotAngle = (rand() % 360);
			model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

			// 4. Now add to list of matrices
			modelMatrices[i] = model;
		}

		for (GLuint i = 0; i < rockObj.meshes.size(); i++)
		{
			GLuint VAO = rockObj.meshes[i].VAO;
			GLuint buffer;
			glBindVertexArray(VAO);
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, AMOUNT * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

			// Set attribute pointers for matrix (4 times vec4)
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);

			glBindVertexArray(0);
		}
		delete[] modelMatrices;
	}

	void Asteroid::init_vertexArray()
	{

	}

	void Asteroid::init_shader()
	{
		AsteroidShader.init();
		AsteroidShader.attach(GL_VERTEX_SHADER, "Asteroid.vert");
		AsteroidShader.attach(GL_FRAGMENT_SHADER, "Asteroid.frag");
		AsteroidShader.link();
		AsteroidShader.use();
		program = AsteroidShader.GetProgram();
	}

}