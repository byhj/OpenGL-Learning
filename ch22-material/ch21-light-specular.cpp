#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

Shader CubeShader("Cube");
Shader LightShader("Light");

const static GLfloat VertexData[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};
GLuint vbo, vao_light, vao_cube, mvp_matrix_loc, model_matrix_loc;
GLuint vertex_loc, cube_prog, light_prog;
GLuint objectColor_loc = 0, lightColor_loc = 0;
GLuint light_mvp_matrix_loc;

struct Material{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};
Material material;

void init_shader()
{
	CubeShader.init();
	CubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	CubeShader.link();
	cube_prog = CubeShader.program;
	CubeShader.use();
	GLint matAmbientLoc = glGetUniformLocation(cube_prog, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(cube_prog, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(cube_prog, "material.specular");
	GLint matShineLoc = glGetUniformLocation(cube_prog, "material.shininess");
	glUniform3fv(matAmbientLoc,1, &glm::vec3(1.0f, 0.5f, 0.31f)[0]);
	glUniform3fv(matDiffuseLoc,1, &glm::vec3(1.0f, 0.5f, 0.31f)[0]);
	glUniform3fv(matSpecularLoc,1, &glm::vec3(0.5f, 0.5f, 0.5f)[0]);
	glUniform1f(matShineLoc, 32.0f);

	objectColor_loc = glGetUniformLocation(cube_prog, "objectColor");
	lightColor_loc = glGetUniformLocation(cube_prog, "lightColor");
	mvp_matrix_loc = glGetUniformLocation(cube_prog, "mvp_matrix");
	model_matrix_loc = glGetUniformLocation(cube_prog, "model_matrix");
	glUniform3f(objectColor_loc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColor_loc, 1.0f, 1.0f, 1.0f); // Also set light's color (white)
	LightShader.init();
	LightShader.attach(GL_VERTEX_SHADER, "cube.vert");
	LightShader.attach(GL_FRAGMENT_SHADER, "cube1.frag");
	LightShader.link();
	light_prog = LightShader.program;
	LightShader.use();
	light_mvp_matrix_loc = glGetUniformLocation(light_prog, "mvp_matrix");
}

void init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	init_shader();
	init_buffer();
	init_vertexArray();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 proj_matrix = glm::perspective(45.0f, 720.0f / 640.0f, 0.1f, 100.0f);
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model_matrix = glm::rotate(glm::mat4(1.0f), 60.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
	glUseProgram(cube_prog);
	glBindVertexArray(vao_cube);
	glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glUseProgram(light_prog);
	glBindVertexArray(vao_light);
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.2f))
		* glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
	mvp_matrix = proj_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(light_mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(720, 640);
	glutInitWindowPosition(300, 0);
	glutCreateWindow("Cube");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}