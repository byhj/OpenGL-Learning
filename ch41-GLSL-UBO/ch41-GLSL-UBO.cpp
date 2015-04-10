#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

static const GLfloat VertexData[] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,

	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,

	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,

	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f
};
Shader uboShader("UBO");
GLuint program, vbo, vao, ubo;
GLuint mvp_matrix_loc;
GLuint red_ubo_index, green_ubo_index,
       blue_ubo_index, yellow_ubo_index;

void init_shader()
{
	uboShader.init();
	uboShader.attach(GL_VERTEX_SHADER, "ubo.vert");
	uboShader.attach(GL_FRAGMENT_SHADER, "ubo.frag");
	uboShader.link();
	program = uboShader.program;
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	red_ubo_index = glGetUniformBlockIndex(program, "transform");
	green_ubo_index = glGetUniformBlockIndex(program, "transform");
	blue_ubo_index = glGetUniformBlockIndex(program, "transform");
	yellow_ubo_index = glGetUniformBlockIndex(program, "transform");
	glUniformBlockBinding(program, red_ubo_index, 0);
	glUniformBlockBinding(program, green_ubo_index, 0);
	glUniformBlockBinding(program, blue_ubo_index, 0);
	glUniformBlockBinding(program, yellow_ubo_index, 0);

}
void init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4),NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glm::mat4 proj_matrix = glm::perspective(45.0f, 720.0f / 640.0f, 1.0f, 1000.0f);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &proj_matrix[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


}
void init()
{	
	init_shader();
	init_buffer();
	init_vertexArray();
	// Clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0));
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Draw 4 cubes 
	// RED
	glBindVertexArray(vao);
	glUseProgram(program);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));	// Move top-left
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform1i(glGetUniformLocation(program, "color"), 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// GREEN
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));		// Move top-right
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform1i(glGetUniformLocation(program, "color"), 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// BLUE
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));	// Move bottom-left
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform1i(glGetUniformLocation(program, "color"), 2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// YELLOW
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));	// Move bottom-right
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform1i(glGetUniformLocation(program, "color"), 3);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("Point size");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}