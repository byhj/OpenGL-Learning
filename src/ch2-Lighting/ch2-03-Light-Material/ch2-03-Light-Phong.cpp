#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma region VertexData

static const  GLfloat VertexData[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
#pragma endregion

glm::vec3 g_lightPos(1.0f, 0.5f, 1.0f);

class TextureApp: public byhj::Application
{
public:
	TextureApp():prog_app(0),prog_light(0), AppShader("Cube Shader"), LightShader("Light Shader")
	{
		camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);  

		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//////////////////////////////Draw Base Scene////////////////////////////////
		glUseProgram(prog_app);
		glBindVertexArray(vao_app);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//////////////////////////////Set Material//////////////////////////////
		GLint matAmbientLoc  = glGetUniformLocation(prog_app, "material.ambient");
		GLint matDiffuseLoc  = glGetUniformLocation(prog_app, "material.diffuse");
		GLint matSpecularLoc = glGetUniformLocation(prog_app, "material.specular");
		GLint matShineLoc    = glGetUniformLocation(prog_app, "material.shininess"); 
		glUniform3f(matAmbientLoc,  1.0f, 0.5f, 0.31f);
		glUniform3f(matDiffuseLoc,  1.0f, 0.5f, 0.31f);
		glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
		glUniform1f(matShineLoc,    32.0f);

		///////////////////Light /////////////////////////////////
		GLint lightAmbientLoc  = glGetUniformLocation(prog_app, "light.ambient");
		GLint lightDiffuseLoc  = glGetUniformLocation(prog_app, "light.diffuse");
		GLint lightSpecularLoc = glGetUniformLocation(prog_app, "light.specular");
		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // Decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence
		glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);  
		glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);  
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);  

		/////////////////////////////Other//////////////////////////////////////////
		glUniform3fv(glGetUniformLocation(prog_app, "viewPos"), 1, &camera.Position[0]);
		glUniform3fv(glGetUniformLocation(prog_app, "lightPos"), 1, &g_lightPos[0]);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), GetAspect(), 0.1f, 100.0f);
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), 60.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(prog_app, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(prog_app, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(prog_app, "proj"), 1, GL_FALSE, &proj[0][0]);
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		///////////////////////////////Draw Light/////////////////////////////////
		glUseProgram(prog_light);
		glBindVertexArray(vao_light);

		model = glm::translate(glm::mat4(1.0f), g_lightPos)
			  * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2) );
		mvp = proj * view * model;
		glUniformMatrix4fv(glGetUniformLocation(prog_light, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

	}

	void v_Shutdown()
	{
		glDeleteProgram(prog_app);
		glDeleteProgram(prog_light);
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

	//
	GLuint prog_light, prog_app;
	Shader LightShader, AppShader;
	GLuint tex1, tex2;
	GLuint tex1_loc, tex2_loc, mvp_loc;
	GLuint vao_light, vao_app, vbo, ibo;
};

CALL_MAIN(TextureApp);


void TextureApp::init_shader()
{
	LightShader.init();
	LightShader.attach(GL_VERTEX_SHADER, "light.vert");
	LightShader.attach(GL_FRAGMENT_SHADER, "light.frag");
	LightShader.link();
	prog_light = LightShader.GetProgram();

	AppShader.init();
	AppShader.attach(GL_VERTEX_SHADER, "cube.vert");
	AppShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	AppShader.link();
	prog_app = AppShader.GetProgram();

}

void TextureApp::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void TextureApp::init_vertexArray()
{
	//light data
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//cube data
	glGenVertexArrays(1, &vao_app);
	glBindVertexArray(vao_app);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
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
