#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <shader.h>
#include <SOIL/SOIL.h>

struct Vertex {
	Vertex(const glm::vec3 &pos, const glm::vec2 &tc) :
		  position(pos), texCoord(tc) {};

	glm::vec3 position;
	glm::vec2 texCoord;
};

const static GLsizei VertexCount(3);
const static GLsizeiptr VertexSize = sizeof(Vertex) * VertexCount;
const static Vertex VertexData[VertexCount] = { //vertex data
	Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.0f, 0.5f, 0.0f),   glm::vec2(0.5f, 1.0f))
};

const char *texture_file("wall.jpg");
GLuint vbo, vao, program, color_loc;
Shader triangleShader("Triangle");
GLuint texture, brick_loc;

void init_shader()  // initial the shader 
{
	triangleShader.init();
	triangleShader.attach(GL_VERTEX_SHADER, "brick.vert");
	triangleShader.attach(GL_FRAGMENT_SHADER, "brick.frag");
	triangleShader.link();
	program = triangleShader.program;
	brick_loc = glGetUniformLocation(program, "brick");
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(NULL));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(NULL + sizeof(glm::vec3)) );
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void init_texture()
{
	int width, height;
	unsigned char*image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Faile to load the file" << std::endl;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		         width, height,
		         0, GL_RGB, GL_UNSIGNED_BYTE, image);
   // glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void init()
{
	init_shader();
	init_texture();
	init_buffer();
	init_vertexArray();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao); 
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(brick_loc, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); //draw the triangle
	glutSwapBuffers();
	glutPostRedisplay();
	glBindVertexArray(0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch6-shader-attribute");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
