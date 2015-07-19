#include "Scene.h"

#include "ogl/loadTexture.h"

namespace byhj
{
#pragma region VertexData

	GLfloat planeVertices[] = {
		// Positions        // Texture Coords
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
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

	void Scene::Render(byhj::MvpMatrix matrix, const byhj::Camera &camera)
	{		
		
		// Light sources
		// - Positions
		std::vector<glm::vec3> lightPositions;
		lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f)); // back light
		lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
		lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
		lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));
		// - Colors
		std::vector<glm::vec3> lightColors;
		lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
		lightColors.push_back(glm::vec3(5.5f, 0.0f, 0.0f));
		lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
		lightColors.push_back(glm::vec3(0.0f, 1.5f, 0.0f));

		glm::mat4 model = matrix.model;
	    glm::mat4 view  = matrix.view;
	    glm::mat4 proj  = matrix.proj;

		///////////////////////Bloom//////////////////////////////////////
		// 1. Render scene into floating point framebuffer
		glUseProgram(bloom_prog);
		glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "view"),  1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "proj"),  1, GL_FALSE, &proj[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTex);

		// - set lighting uniforms
		for (GLuint i = 0; i < lightPositions.size(); i++)
		{
			glUniform3fv(glGetUniformLocation(bloom_prog, ("lights[" + std::to_string(i) + "].Position").c_str()), 1, &lightPositions[i][0]);
			glUniform3fv(glGetUniformLocation(bloom_prog, ("lights[" + std::to_string(i) + "].Color").c_str()), 1, &lightColors[i][0]);
		}
		glm::vec3 camPos = camera.GetPos();
		glUniform3fv(glGetUniformLocation(bloom_prog, "viewPos"), 1, &camPos[0]);

		// - create one large cube that acts as the floor
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 25.0f));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();

		// - then create multiple cubes as the scenery
		glBindTexture(GL_TEXTURE_2D, containerTex);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
		model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(2.0));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
		model = glm::rotate(model, 23.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(2.5));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog ,"model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
		model = glm::rotate(model, 124.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(2.0));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();
		RenderCube();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "model"), 1, GL_FALSE, &model[0][0]);
		RenderCube();
		glUseProgram(0);

		/////////////////////////////////////Light///////////////////////////////////////////////

		// - finally show all the light sources as bright cubes
		glUseProgram(light_prog);
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "view"),  1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(bloom_prog, "proj"),  1, GL_FALSE, &proj[0][0]);

		for (GLuint i = 0; i < lightPositions.size(); i++)
		{
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(lightPositions[i]));
			model = glm::scale(model, glm::vec3(0.5f));
			glUniformMatrix4fv(glGetUniformLocation(light_prog, "model"), 1, GL_FALSE, &model[0][0]);
			glUniform3fv(glGetUniformLocation(      light_prog, "lightColor"), 1, &lightColors[i][0]);
			RenderCube();
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/////////////////////////////////Blur/////////////////////////////////////
		// 2. Blur bright fragments w/ two-pass Gaussian Blur 

		glUseProgram(blur_prog);

		GLboolean horizontal = true, first_iteration = true;
		GLuint amount = 10;
		for (GLuint i = 0; i < amount; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]); 
			glUniform1i(glGetUniformLocation(blur_prog, "horizontal"), horizontal);

		    // bind texture of other framebuffer (or scene if first iteration)
			glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]); 
			RenderQuad();
			horizontal = !horizontal;
			if (first_iteration)
				first_iteration = false;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/////////////////////////////Final//////////////////////////////////
		// 3. Now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(final_prog);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);

		//glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
		glUniform1i(glGetUniformLocation(final_prog, "bloom"), bloom);
		glUniform1f(glGetUniformLocation(final_prog, "exposure"), exposure);
		RenderQuad();

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
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
		bloomShader.init();
		bloomShader.attach(GL_VERTEX_SHADER,   "bloom.vert");
		bloomShader.attach(GL_FRAGMENT_SHADER, "bloom.frag");
		bloomShader.link();
		bloomShader.interfaceInfo();
		bloom_prog =  bloomShader.GetProgram();

		lightShader.init();
		lightShader.attach(GL_VERTEX_SHADER,   "light.vert");
		lightShader.attach(GL_FRAGMENT_SHADER, "light.frag");
		lightShader.link();
		lightShader.interfaceInfo();
		light_prog =  lightShader.GetProgram();

		blurShader.init();
		blurShader.attach(GL_VERTEX_SHADER,   "blur.vert");
		blurShader.attach(GL_FRAGMENT_SHADER, "blur.frag");
		blurShader.link();
		blurShader.interfaceInfo();
		blur_prog =  blurShader.GetProgram();

		finalShader.init();
		finalShader.attach(GL_VERTEX_SHADER,   "final.vert");
		finalShader.attach(GL_FRAGMENT_SHADER, "final.frag");
		finalShader.link();
		finalShader.interfaceInfo();
		final_prog =  finalShader.GetProgram();
	}

	void Scene::init_texture()
	{
		woodTex = loadTexture("../../../media/textures/wood.png");
		containerTex = loadTexture("../../../media/textures/container2.png");
	}

	void Scene::init_fbo(int SCR_WIDTH, int SCR_HEIGHT)
	{
		// Set up floating point framebuffer to render scene to
		glGenFramebuffers(1, &hdrFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
		
		// - Create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
		glGenTextures(2, colorBuffers);
		for (GLuint i = 0; i < 2; i++) 
		{
			glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // We clamp to the edge as the blur filter would otherwise sample repeated texture values!
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// attach texture to framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
		}

		// - Create and attach depth buffer (renderbuffer)
		GLuint rboDepth;
		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
		// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
		GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		// - Finally check if framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Ping pong framebuffer for blurring
		glGenFramebuffers(2, pingpongFBO);
		glGenTextures(2, pingpongColorbuffers);
		for (GLuint i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
			glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // We clamp to the edge as the blur filter would otherwise sample repeated texture values!
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);

			// Also check if framebuffers are complete (no need for depth buffer)
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Framebuffer not complete!" << std::endl;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	}


}