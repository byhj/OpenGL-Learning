#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <SOIL/SOIL.h>

Shader CubeShader("Cube");
Shader LightShader("Light");

GLfloat VertexData[] = {
	// Positions           // Normals           // Texture Coords
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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

GLuint vbo, vao_light, vao_cube, mvp_matrix_loc, model_matrix_loc;
GLuint vertex_loc, cube_prog, light_prog;
GLuint objectColor_loc = 0, lightColor_loc = 0;
GLuint light_mvp_matrix_loc;

struct Material {
	GLuint diffuse;
	GLuint specular;
	float     shininess;
};
Material material;
GLint lightSpecularLoc, lightDiffuseLoc, lightAmbientLoc;

void init_shader()
{
	CubeShader.init();
	CubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	CubeShader.link();
	cube_prog = CubeShader.program;
	CubeShader.use();
	GLint matDiffuseLoc = glGetUniformLocation(cube_prog, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(cube_prog, "material.specular");
	GLint matShineLoc = glGetUniformLocation(cube_prog, "material.shininess");
	GLint lightSpotCutOffLoc = glGetUniformLocation(cube_prog, "light.cutOff");
	GLint lightSpotdirLoc = glGetUniformLocation(cube_prog, "light.direction");
	glUniform3f(lightSpotdirLoc, 0.0, 0.0, 3.0);
	glUniform1f(lightSpotCutOffLoc, glm::cos(glm::radians(12.5f)));
	glUniform1i(matSpecularLoc, 1);
	glUniform1f(matShineLoc, 64.0f);
	glUniform1i(matDiffuseLoc, 0);
	lightAmbientLoc = glGetUniformLocation(cube_prog, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(cube_prog, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(cube_prog, "light.specular");
	glUniform1f(glGetUniformLocation(cube_prog, "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(cube_prog, "light.linear"), 0.09);
	glUniform1f(glGetUniformLocation(cube_prog, "light.quadratic"), 0.032);
	mvp_matrix_loc = glGetUniformLocation(cube_prog, "mvp_matrix");
	model_matrix_loc = glGetUniformLocation(cube_prog, "model_matrix");
	
	LightShader.init();
	LightShader.attach(GL_VERTEX_SHADER, "cube.vert");
	LightShader.attach(GL_FRAGMENT_SHADER, "cube1.frag");
	LightShader.link();
	light_prog = LightShader.program;
	LightShader.use();
	light_mvp_matrix_loc = glGetUniformLocation(light_prog, "mvp_matrix");
}

GLuint texture1, texture2;

void init_texture()
{
	// Load and create a texture 
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("../media/texture/container2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	image = SOIL_load_image("../media/texture/container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

}

void init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	init_shader();
	init_texture();
	init_buffer();
	init_vertexArray();
}
float aspect = 1.0f;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(cube_prog);
	glBindVertexArray(vao_cube);
	glm::vec3 diffuseColor = glm::vec3(0.2f); // Decrease the influence
	glm::vec3 ambientColor = glm::vec3(0.5f); // Low influence
	glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glm::mat4 proj_matrix = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mvp_matrix, model_matrix;

	for (GLuint i = 0; i < 10; i++)
	{
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0), cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model_matrix *= glm::rotate(glm::mat4(1.0), angle, glm::vec3(1.0f, 0.3f, 0.5f));
		mvp_matrix = proj_matrix * view_matrix * model_matrix;
		glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glUseProgram(light_prog);
	glBindVertexArray(vao_light);
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.5f, 1.2f))
		* glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
	mvp_matrix = proj_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(light_mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glutSwapBuffers();
	glutPostRedisplay();
	glBindVertexArray(0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	if (w > h)
		aspect = static_cast<float>(w) / static_cast<float>(h);
	else
	    aspect = static_cast<float>(h) / static_cast<float>(w);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(720, 640);
	glutInitWindowPosition(300, 0);
	glutCreateWindow("Cube");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}