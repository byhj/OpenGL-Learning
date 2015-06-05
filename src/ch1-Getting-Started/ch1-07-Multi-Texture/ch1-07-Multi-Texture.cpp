#include <common/loadTexture.h>
#include <common/oglApp.h>
#include <common/shader.h>

class TextureApp: public byhj::Application
{
public:
	TextureApp():program(0), TriangleShader("Triangle Shader") {};
	~TextureApp() {};

	void vInit()
	{		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		init_shader();
		init_texture();
	}

	void vRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glUseProgram(program);

	}

	void vShutdown()
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
	GLuint tex1_loc, tex2_loc;
};

CALL_MAIN(TextureApp);

void TextureApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "texture.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "texture.frag");
	TriangleShader.link();
	program = TriangleShader.GetProgram();

	tex1_loc = glGetUniformLocation(program, "tex1");
	tex2_loc = glGetUniformLocation(program, "tex2");
	
	//Set tex1 is TEXTURE0 of GL_TEXTURE_2D, tex2 is TEXTURE2;
	glUniform1i(tex1_loc, 0);
	glUniform1i(tex2_loc, 1);

	TriangleShader.interfaceInfo();
}


void TextureApp::init_texture()
{		
	tex1 = loadTexture("../../../media/textures/container.jpg");
	tex2 = loadTexture("../../../media/textures/awesomeface.png");
}
