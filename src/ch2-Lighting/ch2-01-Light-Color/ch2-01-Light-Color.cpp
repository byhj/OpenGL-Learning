

glm::vec3 g_lightPos(1.0f, 0.5f, 1.0f);


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



void LightColorApp::init_shader()
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

void LightColorApp::init_buffer()
{


}

void LightColorApp::init_vertexArray()
{
	//light data
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//cube data
	glGenVertexArrays(1, &vao_app);
	glBindVertexArray(vao_app);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

