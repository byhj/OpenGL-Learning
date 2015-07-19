#include "Scene.h"

#include "ogl/loadTexture.h"

namespace byhj
{
#pragma region VertexData

	GLfloat planeVertices[] = {
		// Positions          // Normals         // Texture Coords
		25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
		-25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
		-25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
		25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f,
		- 25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f
	};

	GLfloat cubeVertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
		// Front face
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
		// Left face
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
		// Right face
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
		// Top face
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left     
	};
#pragma endregion

	void Scene::Init()
	{
		init_buffer();
		init_vertexArray();
		init_shader();
		init_texture();
	}

	// RenderQuad() Renders a 1x1 quad in NDC, best used for framebuffer color targets
	// and post-processing effects.
	void Scene::RenderQuad()
	{
		glBindVertexArray(planeVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void  Scene::RenderCube()
	{
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	void Scene::RenderScene(GLuint program)
	{
		// Floor
		glm::mat4 model;
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
		glBindVertexArray(planeVAO);    
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// Cubes
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0] );
		RenderCube();
		
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0] );
	    RenderCube();
		
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
		model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(0.5));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0] );
		RenderCube();
	}

	void Scene::Render(byhj::MvpMatrix matrix, const byhj::Camera &camera)
	{		
		
		glm::mat4 model = matrix.model;
	    glm::mat4 view  = matrix.view;
	    glm::mat4 proj  = matrix.proj;

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		GLfloat near_plane = 1.0f, far_plane = 7.5f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

		glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
		glm::vec3 camPos = camera.GetPos();
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(1.0));
		lightSpaceMatrix = lightProjection * lightView;

		glUseProgram(shadow_prog);

		glUniformMatrix4fv(glGetUniformLocation(shadow_prog, "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0] );
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_DEPTH_BUFFER_BIT);
		RenderScene(shadow_prog);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glUseProgram(0);

		//////////////////////////////////////////////////////////////////////////////////////
		glUseProgram(scene_prog);

		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "view"),  1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "proj"),  1, GL_FALSE, &proj[0][0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "lightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "viewPos"), 1, &camPos[0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		// Enable/Disable shadows by pressing 'SPscene_progACE'
		glUniform1i(glGetUniformLocation(scene_prog, "shadows"), shadowFlag);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTex);
		glUniform1i(glGetUniformLocation(scene_prog, "diffuseTexture"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glUniform1i(glGetUniformLocation(scene_prog, "shadowMap"), 1);

		RenderScene(scene_prog);

		glUseProgram(0);

	}

	void Scene::Shutdown()
	{
	}

	void Scene::init_buffer()
	{
		glGenBuffers(1, &planeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &cubeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Scene::init_vertexArray()
	{
		glGenVertexArrays(1, &planeVAO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glBindVertexArray(0);

		glGenVertexArrays(1, &cubeVAO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glBindVertexArray(0);
	}

	void Scene::init_shader()
	{
		SceneShader.init();
		SceneShader.attach(GL_VERTEX_SHADER,   "scene.vert");
		SceneShader.attach(GL_FRAGMENT_SHADER, "scene.frag");
		SceneShader.link();
		SceneShader.info();
		scene_prog = SceneShader.GetProgram();

		ShadowShader.init();
		ShadowShader.attach(GL_VERTEX_SHADER,   "shadow.vert");
		ShadowShader.attach(GL_FRAGMENT_SHADER, "shadow.frag");
		ShadowShader.link();
		ShadowShader.info();
		shadow_prog = ShadowShader.GetProgram();
	}

	void Scene::init_texture()
	{
		woodTex = loadTexture("../../../media/textures/wood.png");
	}

	void Scene::init_fbo(int sw, int sh)
	{
		glGenTextures(1, &depth_tex);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, sw, sh, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Scene::ChangeShadow()
	{
		shadowFlag = !shadowFlag;
	}

}