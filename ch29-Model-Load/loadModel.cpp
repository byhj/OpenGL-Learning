#include "loadModel.h"
#include <sstream>
#include <iostream>
#include <SOIL/SOIL.h>

using std::stringstream;


Mesh::Mesh(vector<Vertex> v, vector<GLuint> e, vector<Texture> t)
{
	VertexData = v;
	ElementData = e;
	TextureData = t;
	initMesh();
}

void Mesh::initMesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(Vertex),
		         &VertexData[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementData.size() * sizeof(GLuint),
		        &ElementData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(NULL));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(NULL+sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(NULL + sizeof(glm::vec3) +sizeof(glm::vec3)));
	glBindVertexArray(0);
}

void Mesh::render(GLuint program)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < TextureData.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		stringstream ss;
		string number;
		string name = TextureData[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();
		glUniform1i(glGetUniformLocation(program, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, TextureData[i].id);
	}
	// Draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, ElementData.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < TextureData.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Model::Render(GLuint program)
{
	for (GLuint i = 0; i < MeshData.size(); i++)
		MeshData[i].render(program);
}

void Model::loadModel(string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error::Assimp::" << import.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; ++i) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		MeshData.push_back(processMesh(mesh, scene));
	}
	//// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; ++i)
		processNode(node->mChildren[i], scene);
}


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> VertexData;
	vector<GLuint> ElementData;
	vector<Texture> TextureData;
	for (GLuint i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;
		glm::vec3 temp;
		temp.x = mesh->mVertices[i].x;
		temp.y = mesh->mVertices[i].y;
		temp.z = mesh->mVertices[i].z;
		vertex.Position = temp;
		temp.x = mesh->mNormals[i].x;
		temp.y = mesh->mNormals[i].y;
		temp.z = mesh->mNormals[i].z;
		vertex.Normal = temp;
		if (mesh->mTextureCoords[0]) {
			glm::vec2 tc;
			tc.x = mesh->mTextureCoords[0][i].x;
			tc.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoord = tc;
		}
		else
			vertex.TexCoord = glm::vec2(0.0f, 0.0f);
		VertexData.push_back(vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; ++j)
			ElementData.push_back(face.mIndices[j]);
	}
	//material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		// 1. Diffuse maps
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		TextureData.insert(TextureData.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		TextureData.insert(TextureData.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(VertexData, ElementData, TextureData);
}

GLint TextureFromFile(const char* path, string dire)
{
	//Generate texture ID and load texture data 
	string filename = string(path);
	filename = dire + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

// Checks all material textures of a given type and loads the textures if they're not loaded yet.
// The required info is returned as a Texture struct.
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean skip = false;
		for (GLuint j = 0; j < Texture_load.size(); j++)
		{
			if (Texture_load[j].path == str)
			{
				textures.push_back(Texture_load[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
			Texture_load.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

