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

const static GLsizei VertexCount(4);
const static GLsizeiptr VertexSize = sizeof(glm::vec3) * VertexCount;
const static glm::vec3 VertexData[VertexCount] = {  //vertex data
    glm::vec3( 0.5f,  0.5f, 0.0f),  // Top Right
    glm::vec3( 0.5f, -0.5f, 0.0f),  // Bottom Right
    glm::vec3(-0.5f, -0.5f, 0.0f),  // Bottom Left
    glm::vec3(-0.5f,  0.5f, 0.0f)   // Top Left 
};

const static GLsizei ElementCount(6);
const static GLsizeiptr ElementSize = sizeof(GLushort) * ElementCount;
const static GLushort ElementData[ElementCount] = {  
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
};  

GLuint vbo, vao, ebo, program;
Shader rectangleShader("Rectangle");

void init_shader()  // initial the shader 
{
	rectangleShader.init();
	rectangleShader.attach(GL_VERTEX_SHADER, "rectangle.vert");
	rectangleShader.attach(GL_FRAGMENT_SHADER, "rectangle.frag");
	rectangleShader.link();
	program = rectangleShader.program;
}

void init_buffer()
{
	glGenBuffers(1, &vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);  //initial the vertex array object
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  //tranform the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		                  sizeof(glm::vec3), (GLvoid*)(NULL));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch3-Rectangle");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
