#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <SOIL/SOIL.h>
#include "shader.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <algorithm>

using std::string; using std::vector;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void do_movement();

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

GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};
const GLuint WIDTH = 1300, HEIGHT = 900;
Camera camera( glm::vec3(0.0f, 0.0f, 10.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLuint cube_vbo, cube_vao, cube_program, cube_tex_loc;
Shader cubeShader("Cube");
Shader skyboxShader("Skybox");
GLuint skybox_vbo, skybox_vao, skybox_program;
GLuint cube_mvp_loc, skybox_mvp_loc, skybox_tex_loc;
GLuint cubemap_texture, cube_texture;

void init_shader()  // initial the shader 
{
	cubeShader.init();
	cubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	cubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	cubeShader.link();
	cube_program = cubeShader.program;
	cube_tex_loc = glGetUniformLocation(cube_program, "tex");
	cube_mvp_loc = glGetUniformLocation(cube_program, "mvp_matrix");

	skyboxShader.init();
	skyboxShader.attach(GL_VERTEX_SHADER, "skybox.vert");
	skyboxShader.attach(GL_FRAGMENT_SHADER, "skybox.frag");
	skyboxShader.link();
	skybox_program = skyboxShader.program;
	skybox_tex_loc = glGetUniformLocation(skybox_program, "skybox");
	skybox_mvp_loc = glGetUniformLocation(skybox_program, "mvp_matrix");
}

void init_buffer()
{
	glGenBuffers(1, &cube_vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &skybox_vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	//cube data
	glGenVertexArrays(1, &cube_vao);  //initial the vertex array object
	glBindVertexArray(cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);  //tranform the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(NULL + sizeof(GLfloat)* 3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

    //skybox data
	glGenVertexArrays(1, &skybox_vao);  
	glBindVertexArray(skybox_vao);
	glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 3, (GLvoid*)(NULL));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}
GLuint loadCubeMap(const vector<string> &faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char *image;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); ++i) {
		image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (!image)
			std::cout << "Cannot load the cube map texture" << std::endl;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return textureID;
}

GLuint loadTexture(GLchar* path)
{
	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Cannot load the 2d texture" << std::endl;
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}


void init_texture()
{
	//cube texture
	cube_texture = loadTexture("../media/texture/container.jpg");
	// Cubemap (Skybox)
	vector<string> faces;
	faces.push_back("../media/texture/skybox/right.jpg");
	faces.push_back("../media/texture/skybox/left.jpg");
	faces.push_back("../media/texture/skybox/top.jpg");
	faces.push_back("../media/texture/skybox/bottom.jpg");
	faces.push_back("../media/texture/skybox/back.jpg");
	faces.push_back("../media/texture/skybox/front.jpg");
	cubemap_texture = loadCubeMap(faces);
}


void init()
{
	// Setup some OpenGL options
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	init_shader();
	init_texture();
	init_buffer();
	init_vertexArray();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
	glClearDepth(1.0f);
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw skybox first
	glDepthMask(GL_FALSE);
	// Remove any translation component of the view matrix
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	glm::mat4 proj = glm::perspective(camera.Zoom, 1300.0f / 900.0f, 0.1f, 100.0f);
	glUseProgram(skybox_program);
	glm::mat4 mvp =  view * proj;
	glUniformMatrix4fv(glGetUniformLocation(skybox_program, "mvp_matrix"), 1, GL_FALSE, glm::value_ptr(mvp));
	glBindVertexArray(skybox_vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
    
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS); // Set depth function back to default
	GLfloat time = glfwGetTime() / 1000.0;
	glUseProgram(cube_program);
	glBindVertexArray(cube_vao);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f))
		            * glm::rotate(glm::mat4(1.0f), time * 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	view = camera.GetViewMatrix();
	mvp = proj * view * model;
	glUniformMatrix4fv(glGetUniformLocation(cube_program, "mvp_matrix"), 1, GL_FALSE, glm::value_ptr(mvp));
	glBindVertexArray(cube_vao);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetWindowPos(window, 300, 100);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Fail to initial the GLEW:"  << std::endl;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	init();

	while(!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		do_movement();

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}