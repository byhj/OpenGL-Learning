#include "ObjModel.h"

namespace byhj
{

void ObjModel::Init()
{
	init_buffer();
	init_shader();
}

void ObjModel::Render(const byhj::MvpMatrix matrix)
{

	glUseProgram(program);

	glm::mat4 model = matrix.model; 
	glm::mat4 view  = matrix.view;
	glm::mat4 proj  = matrix.proj;
	glm::mat4 mvp = proj * view * model;
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &proj[0][0]);

	modelLoad.Draw(program);

	glUseProgram(0);
}

void ObjModel::Shutdown()
{
	glDeleteProgram(program);
}

void ObjModel::init_buffer()
{
	modelLoad.loadModel("../../../media/objects/nanosuit/nanosuit.obj");
}

void ObjModel::init_shader()
{
	ObjShader.init();
	ObjShader.attach(GL_VERTEX_SHADER, "model.vert");
	ObjShader.attach(GL_FRAGMENT_SHADER, "model.frag");
	ObjShader.link();
	ObjShader.use();
	ObjShader.interfaceInfo();
	program = ObjShader.GetProgram();

	view_loc = glGetUniformLocation(program, "view");
	model_loc = glGetUniformLocation(program, "model");
	proj_loc = glGetUniformLocation(program, "proj");


	ambient_loc  = glGetUniformLocation(program, "light.ambient");
	diffuse_loc  = glGetUniformLocation(program, "light.diffuse");
	specular_loc = glGetUniformLocation(program, "light.specular");

	//set the light unfirom
	glm::vec3 diffuseColor = glm::vec3(0.8f); // Decrease the influence
	glm::vec3 ambientColor = glm::vec3(0.8f); // Low influence
	glUniform3f(ambient_loc, ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(diffuse_loc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(specular_loc, 1.0f, 1.0f, 1.0f);
}

}