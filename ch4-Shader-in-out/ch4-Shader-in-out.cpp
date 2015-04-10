/*
A vertex array object stores the following:
   glbindbuffer();
   Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
   Vertex attribute configurations via glVertexAttribPointer.
   Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <shader.h>

const static GLsizei VertexCount(3);
const static GLsizeiptr VertexSize = sizeof(glm::vec3) * VertexCount;
const static glm::vec3 VertexData[VertexCount] = {  //vertex data
	glm::vec3(-0.5f, -0.5f, 0.0f),
	glm::vec3(0.5f, -0.5f, 0.0f),
	glm::vec3(0.0f, 0.5f, 0.0f)
};

GLuint vbo, vao, program;
Shader triangleShader("Triangle");

void init_shader()  // initial the shader 
{
	triangleShader.init();
	triangleShader.attach(GL_VERTEX_SHADER, "triangle.vert");
	triangleShader.attach(GL_FRAGMENT_SHADER, "triangle.frag");
	triangleShader.link();
	program = triangleShader.program;
}

void init_buffer()
{
	glGenBuffers(1, &vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);  //initial the vertex array object
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  //tranform the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		                  sizeof(glm::vec3), (GLvoid*)(NULL));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void init()
{
	init_shader();
	init_buffer();
	init_vertexArray();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao);    
	glDrawArrays(GL_TRIANGLES, 0, 3); //draw the triangle
	glBindVertexArray(0);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch4-shader-in-out");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
