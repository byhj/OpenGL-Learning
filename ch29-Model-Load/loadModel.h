#ifndef LOADMODEL_H
#define LOADMODEL_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using std::string; using std::vector;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
  public:
	  //mesh data
	  vector<Vertex> VertexData;
	  vector<GLuint> ElementData;
	  vector<Texture> TextureData;
	  //function
	  Mesh(vector<Vertex> v, vector<GLuint> e, vector<Texture> t);
	  void render(GLuint program);
private:
	GLuint vao, vbo, ebo;
	void initMesh();
};


class Model {
public:
	Model() { };
	void loadModel(string path);
	void Render(GLuint program);
private:
	vector<Mesh> MeshData;
	string directory;
	vector<Texture> Texture_load;
	//function
	vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTexture(aiMaterial *mat,
		aiTextureType type, string typeName);

};
#endif