#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>

class TextureApp: public byhj::Application
{
public:
	TextureApp():program(0), TriangleShader("Triangle Shader") {};
	~TextureApp() {};

	void v_Init()
	{		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		init_shader();
		init_texture();
//		init_buffer();
//		init_vertexArray();
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
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}

	void v_Shutdown()
	{
		glDeleteProgram(program);
	}

private:
	void init_shader();
	void init_texture();
	//void init_buffer();
	//void init_vertexArray();

private:
	GLuint program;
	Shader TriangleShader;
	GLuint tex1, tex2;
	GLuint tex1_loc, tex2_loc;
	GLuint vao, vbo, ibo;
};

CALL_MAIN(TextureApp);

/*
const static GLfloat VertexData[] = {
	// Positions          // Colors      // Texture Coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f,    0.0f, 1.0f, 1.0f,   // Top Right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f,    0.0f, 1.0f, 0.0f,   // Bottom Right
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,    1.0f, 0.0f, 0.0f,   // Bottom Left
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f,    0.0f, 0.0f, 1.0f
};
const static GLsizei VertexSize = sizeof(VertexData);

const static GLuint IndexData[] = {  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};
const static GLsizei IndexSize = sizeof(IndexData);

void TextureApp::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);    //load the vertex data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexData), IndexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TextureApp::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Position  attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

*/
void TextureApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "texture.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "texture.frag");
	TriangleShader.link();
	TriangleShader.use();
	program = TriangleShader.GetProgram();

	tex1_loc = glGetUniformLocation(program, "tex1");
	tex2_loc = glGetUniformLocation(program, "tex2");
	
	//Set the uniform should call glUseProgram();
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

