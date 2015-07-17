

		// 1. Draw scene as normal in multisampled buffers
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Create transformations
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		float time = glfwGetTime();
		model = glm::rotate(model, glm::radians( 50.0f), glm::vec3(0.5f, 1.0f, 1.0f));
		view  = camera.GetViewMatrix();
		proj  = glm::perspective(camera.Zoom, GetAspect(), 0.1f, 100.0f);
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

		glBindVertexArray(0);


		// 2. Now blit multisampled buffer(s) to default framebuffers
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);				
		glBlitFramebuffer(0, 0, GetScreenWidth(), GetScreenWidth(), 0, 0, GetScreenWidth(), GetScreenWidth(), GL_COLOR_BUFFER_BIT, GL_NEAREST);     

	

}
