#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <SOIL/SOIL.h>

const static GLsizei VertexCount(180);
const static GLsizeiptr VertexSize = sizeof(GLfloat)* VertexCount;
const static GLfloat VertexData[VertexCount] = { //vertex data
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};

const char *texture_file("container.jpg");
GLuint vbo, vao, ebo, program, color_loc;
Shader triangleShader("Triangle");
GLuint texture1, texture2, tex1_loc, tex2_loc;
GLuint model_matrix_loc, view_matrix_loc, proj_matrix_loc;

void init_shader()  // initial the shader 
{
	triangleShader.init();
	triangleShader.attach(GL_VERTEX_SHADER, "cube.vert");
	triangleShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	triangleShader.link();
	program = triangleShader.program;
	tex1_loc = glGetUniformLocation(program, "tex1");
	tex2_loc = glGetUniformLocation(program, "tex2");
	model_matrix_loc = glGetUniformLocation(program, "model_matrix");
	view_matrix_loc = glGetUniformLocation(program, "view_matrix");
	proj_matrix_loc = glGetUniformLocation(program, "proj_matrix");
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL + sizeof(GLfloat)* 3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void init_texture()
{
	int width, height;
	unsigned char*image = SOIL_load_image("../media/texture/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Faile to load the file" << std::endl;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); //绑定到texture0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	image = SOIL_load_image("../media/texture/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Faile to load the file" << std::endl;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); //绑定到texture0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	init_shader();
	init_texture();
	init_buffer();
	init_vertexArray();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
	glClearDepth(1.0f);
}
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat currentTime = 0.0f;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao);
	glUniform1i(tex1_loc, 0);
	glUniform1i(tex2_loc, 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	deltaTime = currentTime - lastTime; //每一帧的时间
	lastTime = currentTime;
	for (GLuint i = 0; i < 10; i++) {
		GLfloat angle = 20.0f * i;
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), cubePositions[i]);
		model_matrix *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.3f, 0.5f));
		glm::mat4 view_matrix = glm::lookAt(camPos, camPos + camFront, camUp);
		glm::mat4 proj_matrix = glm::perspective(45.0f, 720.0f / 640.0f, 0.1f, 1000.0f);
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
		glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);
		glUniformMatrix4fv(proj_matrix_loc, 1, GL_FALSE, &proj_matrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
	glutSwapBuffers();
}

void keyBoard(unsigned char key, int x, int y)
{
	glm::vec3 camDir = glm::normalize(camPos + camFront);
	GLfloat camSpeed = 0.5f;
	switch (key){
	case 'w': camPos += camSpeed * camFront;
		break;
	case 's': camPos -= camSpeed * camFront;
		break;
	case 'a': camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
		break;
	case 'd': camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch6-shader-attribute");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutKeyboardFunc(keyBoard);
	glutMainLoop();
}
