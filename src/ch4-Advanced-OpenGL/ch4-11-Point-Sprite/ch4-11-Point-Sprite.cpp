#include <common/learnApp.h>
#include <common/shader.h>
#include <common/loadTexture.h>

#include <iostream>

class TriangleApp: public byhj::Application
{
public:
	TriangleApp() { }
	~TriangleApp() {}

public:
	void v_Init()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_BLEND); //¿ªÆô»ìºÏ
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		init_shader();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_POINT_SPRITE);

		glBindTexture(GL_TEXTURE_2D, sprite_texture);
		glUniform1i(glGetUniformLocation(program, "sprite_texture"), 0);

		//Draw the Triangle
		glDrawArrays(GL_POINTS, 0, 9);

		glUseProgram(0);
	}
	void v_Shutdown()
	{
		glDeleteProgram(program);

	}

private:
	void init_shader();

	GLuint program;
	Shader PointShader;
	GLuint sprite_texture;
};

CALL_MAIN(TriangleApp);


void TriangleApp::init_shader()
{
	PointShader.init();
	PointShader.attach(GL_VERTEX_SHADER, "point.vert");
	PointShader.attach(GL_FRAGMENT_SHADER, "point.frag");
	PointShader.link();
	program = PointShader.GetProgram();
	sprite_texture = loadTexture("../../../media/textures/awesomeface.png");

}

