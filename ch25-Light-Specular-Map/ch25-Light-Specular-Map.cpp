#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <camera.h>
#include <SOIL/SOIL.h>

    // Set up vertex data (and buffer(s)) and attribute pointers
static const  GLfloat VertexData[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

void key_callback(GLFWwindow * window,  int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void do_movement();

const GLuint WIDTH = 1300, HEIGHT = 900;
Camera camera( glm::vec3(0.0f, 0.0f, 4.0f) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

glm::vec3 lightPos(1.0f, 0.5f, 1.0f);
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

Shader lightShader("Light");
Shader cubeShader("Cube");
GLuint cube_prog, cube_vao, diffuse_tex, specular_tex;
GLuint light_prog, light_vao, vbo;

void init_shader()
{
	lightShader.init();
	lightShader.attach(GL_VERTEX_SHADER, "light.vert");
	lightShader.attach(GL_FRAGMENT_SHADER, "light.frag");
	lightShader.link();
	light_prog = lightShader.program;

	cubeShader.init();
	cubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	cubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	cubeShader.link();
	cube_prog = cubeShader.program;

}

void init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	//light data
	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//cube data
	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

GLuint init_texture(const char * textureFile)
{
	int width, height;
	unsigned char*image = SOIL_load_image(textureFile, &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Faile to load the texture" << std::endl;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		         width, height,
		         0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); 
	return texture;
}

void init()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	init_shader();
	init_buffer();
	init_vertexArray();
	diffuse_tex = init_texture("../media/Texture/container2.png");
	specular_tex = init_texture("../media/Texture/container2_specular.png");

}

void render()
{		
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       //draw cube
	   glUseProgram(cube_prog);
	   glUniform1i(glGetUniformLocation(cube_prog, "material.diffuse"), 0);
	   glUniform1i(glGetUniformLocation(cube_prog, "material.specular"), 1);
       GLint matShineLoc = glGetUniformLocation(cube_prog, "material.shininess"); 
       glUniform1f(matShineLoc,    32.0f);

	   GLint lightAmbientLoc  = glGetUniformLocation(cube_prog, "light.ambient");
       GLint lightDiffuseLoc  = glGetUniformLocation(cube_prog, "light.diffuse");
       GLint lightSpecularLoc = glGetUniformLocation(cube_prog, "light.specular");
       glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
       glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f); // Let's darken the light a bit to fit the scene
       glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);   

		glUniform3f(glGetUniformLocation(cube_prog, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(camera.Zoom, (GLfloat) WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), 60.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(cube_prog, "mvp"), 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(cube_prog, "model"), 1, GL_FALSE, &model[0][0]);
		glBindVertexArray(cube_vao);
	        // Bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_tex);
        // Bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_tex);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

	//draw light
		glUseProgram(light_prog);
	    model = glm::translate(glm::mat4(1.0f), lightPos)
			            * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2) );
		mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(light_prog, "mvp"), 1, GL_FALSE, &mvp[0][0]);
		glBindVertexArray(light_vao);
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