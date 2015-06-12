#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformApp: public byhj::Application
{
public:
	TransformApp():program(0), TriangleShader("Triangle Shader") {};
	~TransformApp() {};

	void v_Init()
	{		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		init_shader();
		init_texture();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2);

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, &trans[0][0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}

	void v_Shutdown()
	{
		glDeleteProgram(program);
	}

private:
	void init_shader();
	void init_texture();


private:
	GLuint program;
	Shader TriangleShader;
	GLuint tex1, tex2;
	GLuint tex1_loc, tex2_loc, transform_loc;
	GLuint vao, vbo, ibo;
};

CALL_MAIN(TransformApp);

void TransformApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "texture.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "texture.frag");
	TriangleShader.link();
	TriangleShader.use();
	program = TriangleShader.GetProgram();

	tex1_loc = glGetUniformLocation(program, "tex1");
	tex2_loc = glGetUniformLocation(program, "tex2");
	transform_loc = glGetUniformLocation(program, "transform");

	glUniform1i(tex1_loc, 0);
	glUniform1i(tex2_loc, 1);

	TriangleShader.interfaceInfo();
}


void TransformApp::init_texture()
{		
	tex1 = loadTexture("../../../media/textures/container.jpg");
	tex2 = loadTexture("../../../media/textures/awesomeface.png");
}

