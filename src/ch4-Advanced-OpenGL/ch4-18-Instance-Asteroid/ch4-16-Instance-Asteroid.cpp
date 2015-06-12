#include <common/loadTexture.h>
#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>
#include <common/model.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint amount = 100000;

class TextureApp: public byhj::Application
{
public:
	TextureApp(): camera(glm::vec3(100.0f, 100.0f, 1000.0f))
	{
		lastX = GetScreenWidth() / 2.0f;
		lastY = GetScreenHeight() / 2.0f;
		firstMouse = true;
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		for (int i = 0; i != 1024; ++ i)
			keys[i] = false;
	};
	~TextureApp() {};

	void v_Init()
	{			
		glClearColor(0.03f, 0.03f, 0.03f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);  

		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Draw Planet
		glm::mat4 proj = glm::perspective(camera.Zoom, GetAspect(), 1.0f, 10000.0f);
		glUseProgram(planet_prog);
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(planet_prog, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
		planet.Draw(planet_prog);

		// Draw meteorites
		glUseProgram(asteroid_prog);
		glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // Note we also made the textures_loaded vector public (instead of private) from the model class.
		glUniformMatrix4fv(glGetUniformLocation(asteroid_prog, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
		for (GLuint i = 0; i < rock.meshes.size(); i++)
		{
			glBindVertexArray(rock.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, amount);
			glBindVertexArray(0);
		}
	}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void do_movement();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void v_Shutdown()
	{
	}
	void v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void v_Movement(GLFWwindow *window);
	void v_MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	void init_shader();
	void init_buffer();
	void init_vertexArray();

private:

	// Camera
	Camera camera;
	bool keys[1024];
	GLfloat lastX, lastY ;
	bool firstMouse;
	GLfloat deltaTime;
	GLfloat lastFrame;

	GLuint vbo, vao, color_loc;
	Shader AsteroidShader;
	Shader PlanetShader;
	GLuint asteroid_prog, planet_prog;
	GLuint mvp_matrix_loc;
	Model rock;
	Model planet;
	GLuint instanceVBO;
};

CALL_MAIN(TextureApp);

#pragma region VertexData

const static GLsizei VertexCount(30);
const static GLsizeiptr VertexSize = sizeof(GLfloat)* VertexCount;
const static GLfloat VertexData[VertexCount] = { //vertex data
	// Positions   // Colors
	-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
	0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
	-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

	-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
	0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
	0.05f, 0.05f, 0.0f, 1.0f, 1.0f
};

#pragma endregion

void TextureApp::init_shader()
{
	AsteroidShader.init();
	AsteroidShader.attach(GL_VERTEX_SHADER, "asteroid.vert");
	AsteroidShader.attach(GL_FRAGMENT_SHADER, "asteroid.frag");
	AsteroidShader.link();
	asteroid_prog = AsteroidShader.GetProgram();

	PlanetShader.init();
	PlanetShader.attach(GL_VERTEX_SHADER, "Planet.vert");
	PlanetShader.attach(GL_FRAGMENT_SHADER, "Planet.frag");
	PlanetShader.link();
	planet_prog = PlanetShader.GetProgram();

}

void TextureApp::init_buffer()
{
	rock.loadModel("../../../media/objects/rock/rock.obj");
	planet.loadModel("../../../media/objects/planet/planet.obj");

	glm::mat4* modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed	
	GLfloat radius = 150.0f;
	GLfloat offset = 25.0f;

	for (GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y = -2.5f + displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. Scale: Scale between 0.05 and 0.25f
		GLfloat scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. Now add to list of matrices
		modelMatrices[i] = model;
	}

	for (GLuint i = 0; i < rock.meshes.size(); i++)
	{
		GLuint VAO = rock.meshes[i].VAO;
		GLuint buffer;
		glBindVertexArray(VAO);
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

		// Set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
	delete[] modelMatrices;

}

void TextureApp::init_vertexArray()
{
}


// Moves/alters the camera positions based on user input
void TextureApp::v_Movement(GLFWwindow *window)
{
	// Camera controls
	if(keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if(keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if(keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if(keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_C])
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.ctr = false;
	}
}

// Is called whenever a key is pressed/released via GLFW
void TextureApp::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << std::endl;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if(action == GLFW_PRESS)
		keys[key] = true;
	else if(action == GLFW_RELEASE)
		keys[key] = false;	
}

void TextureApp::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
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


void TextureApp::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

	camera.ProcessMouseScroll(yoffset);
}