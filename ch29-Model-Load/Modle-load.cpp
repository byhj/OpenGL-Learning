using namespace std;
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"

Shader modelShader("Model");
GLuint mvp_matrix_loc, model_matrix_loc, program;
Model model;
struct Material {
	GLuint diffuse;
	GLuint specular;
	float     shininess;
};
Material material;
GLint lightSpecularLoc, lightDiffuseLoc, lightAmbientLoc;

void init_shader()  // initial the shader 
{
	modelShader.init();
	modelShader.attach(GL_VERTEX_SHADER, "model.vert");
	//modelShader.attach(GL_GEOMETRY_SHADER, "model.geo");
	modelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
	modelShader.link();
	program = modelShader.program;
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	model_matrix_loc = glGetUniformLocation(program, "model_matrix");
	GLint matDiffuseLoc = glGetUniformLocation(program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(program, "material.shininess");
	glUniform3fv(matSpecularLoc, 1, &glm::vec3(0.5f, 0.5f, 0.5f)[0]);
	glUniform1f(matShineLoc, 64.0f);
	glUniform1i(matDiffuseLoc, 0);
	lightAmbientLoc = glGetUniformLocation(program, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(program, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(program, "light.specular");

}

void init()
{
	init_shader();
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	model.loadModel("./nanosuit.obj");
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -8.0f, -15.0f))
		* glm::rotate(glm::mat4(1.0f),glm::radians(time* 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -10.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 proj_matrix = glm::perspective(45.0f, 720.0f / 640.0f, 0.1f, 1000.0f);
	glm::mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glm::vec3 diffuseColor = glm::vec3(0.8f); // Decrease the influence
	glm::vec3 ambientColor = glm::vec3(0.8f); // Low influence
	glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
	model.Draw(program);
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch29-Load Model");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
