#include <common/learnApp.h>
#include <common/shader.h>
#include <common/camera.h>
#include <common/loadTexture.h>
#include <common/glDebug.h>
#include <common/model.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class ModelApp: public byhj::Application
{
public:
	ModelApp()
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
	~ModelApp() {};

	void v_Init()
	{			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearDepth(1.0f);
        
		init_buffer();
		init_shader();

		glEnable(GL_DEPTH_TEST);
	}


	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		float time = glfwGetTime() / 1000.0f;

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//set the mvp matrix
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -8.0f, -15.0f));
		glm::mat4 view_matrix = camera.GetViewMatrix();
		glm::mat4 proj_matrix = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 1000.0f);
		glm::mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &proj_matrix[0][0]);
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_matrix[0][0]);
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model_matrix[0][0]);

		//set the light unfirom
		glm::vec3 diffuseColor = glm::vec3(0.8f); // Decrease the influence
		glm::vec3 ambientColor = glm::vec3(0.8f); // Low influence
		glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
		glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

		model.Draw(program);
	}

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
	void init_texture();

private:

	// Camera
	Camera camera;
	bool keys[1024];
	GLfloat lastX, lastY ;
	bool firstMouse;
	GLfloat deltaTime;
	GLfloat lastFrame;

	Shader modelShader;
	GLuint view_loc, proj_loc, model_loc, program;
	Model model;
	GLint lightSpecularLoc, lightDiffuseLoc, lightAmbientLoc;

};

CALL_MAIN(ModelApp);


void ModelApp::init_shader()
{
	modelShader.init();
	modelShader.attach(GL_VERTEX_SHADER, "model.vert");
	modelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
	modelShader.link();
	modelShader.use();
	program = modelShader.GetProgram();

	view_loc = glGetUniformLocation(program, "view");
	model_loc = glGetUniformLocation(program, "model");
	proj_loc = glGetUniformLocation(program, "proj");

	GLint matDiffuseLoc = glGetUniformLocation(program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(program, "material.shininess");
	glUniform3fv(matSpecularLoc, 1, &glm::vec3(0.5f, 0.5f, 0.5f)[0]);
	glUniform1f(matShineLoc, 64.0f);
	glUniform1i(matDiffuseLoc, 0);

	lightAmbientLoc = glGetUniformLocation(program, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(program, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(program,"light.specular");
}

void ModelApp::init_buffer()
{

	model.loadModel("../../../media/objects/nanosuit/nanosuit.obj");

}

void ModelApp::init_vertexArray()
{

}

void ModelApp::init_texture()
{

}

// Moves/alters the camera positions based on user input
void ModelApp::v_Movement(GLFWwindow *window)
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
void ModelApp::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if(action == GLFW_PRESS)
		keys[key] = true;
	else if(action == GLFW_RELEASE)
		keys[key] = false;	
}

void ModelApp::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
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


void ModelApp::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
