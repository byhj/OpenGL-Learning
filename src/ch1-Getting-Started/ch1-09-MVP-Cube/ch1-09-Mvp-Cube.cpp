/*
 *                      Model Matrix              View Matrix
 * Local(Object) Space ------------->World Space------------>
 *                       Proj Matrix                 
 * Camera(View)  Space ------------->Clip  Space(change data to (-1.0, 1.0) 
 * which is NDC, frustum clip , then take the  perspective division 
 * Viewport
 * ----------> Screen Space( Map to Window Screen Width and Height)
 */

#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MANY_CUBES

glm::vec3 cubePositions[] = {
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

class MvpApp: public byhj::Application
{
public:
	MvpApp():program(0), TriangleShader("Triangle Shader") {};
	~MvpApp() {};

	void v_Init()
	{			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);  

		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		glUniform1i(glGetUniformLocation(program, "tex1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2);
		glUniform1i(glGetUniformLocation(program, "tex2"), 1);

		float time = glfwGetTime();

#ifdef MANY_CUBES
		for(GLuint i = 0; i < 10; i++) 
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * (i+1); 
			model = glm::rotate(model, glm::radians(time * angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 proj = glm::perspective(45.0f, 720.0f / 640.0f, 0.1f, 1000.0f);
			glm::mat4 mvp = proj * view * model;

			glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
#else
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;

		model = glm::rotate(model, glm::radians(time * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		proj  = glm::perspective(45.0f, GetAspect(), 0.1f, 100.0f);
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
#endif
		glBindVertexArray(0);
	}

	void v_Shutdown()
	{
		glDeleteProgram(program);
	}

private:
	void init_shader();
	void init_texture();
	void init_buffer();
	void init_vertexArray();

private:
	GLuint program;
	Shader TriangleShader;
	GLuint tex1, tex2;
	GLuint tex1_loc, tex2_loc, mvp_loc;
	GLuint vao, vbo, ibo;
};

CALL_MAIN(MvpApp);

#pragma region VertexData

const static GLfloat VertexData[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f 
};

#pragma endregion

void MvpApp::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "cube.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	TriangleShader.link();
	program = TriangleShader.GetProgram();
	mvp_loc = glGetUniformLocation(program, "mvp_matrix");
    
}

void MvpApp::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void MvpApp::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); 
	glBindVertexArray(0);
}

void MvpApp::init_texture()
{
	tex1 = loadTexture("../../../media/textures/container.jpg");
	tex2 = loadTexture("../../../media/textures/awesomeface.png");
}
