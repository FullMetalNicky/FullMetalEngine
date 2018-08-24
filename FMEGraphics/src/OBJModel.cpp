#include "OBJModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG
#define DEBUG 1
#endif
#ifndef _DEBUG
#define DEBUG 0
#endif


using namespace FME::Graphics;


OBJModel::OBJModel(const std::string& objPath)
{
	m_shaderName = "obj";

	loadModel(objPath);
}

void OBJModel::Draw()
{
	for (int i = 0; i < m_meshes.size(); ++i)
	{		
		m_meshes[i]->Draw(FME::Graphics::ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID());
	}
}


void OBJModel::loadModel(const std::string& objPath)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(objPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	m_directory = objPath.substr(0, objPath.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}


void OBJModel::processNode(aiNode *node, const aiScene *scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
		m_meshes[i]->SetName(node->mName.C_Str());
	}

	if (DEBUG) std::cout << node->mName.C_Str() << std::endl;
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}

}


std::shared_ptr<OBJMesh> OBJModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::shared_ptr<ITexture>>  textures;
	std::vector<std::string>  textureNames;


	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		if (mesh->mNormals) // does the mesh contain texture coordinates?
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		else vertex.Normal = glm::vec3(0.0f);

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	std::vector<std::string> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textureNames.insert(textureNames.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<std::string> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textureNames.insert(textureNames.end(), specularMaps.begin(), specularMaps.end());
	std::vector<std::string> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textureNames.insert(textureNames.end(), normalMaps.begin(), normalMaps.end());
	std::vector<std::string> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textureNames.insert(textureNames.end(), heightMaps.begin(), heightMaps.end());
	
	// return a mesh object created from the extracted mesh data
	std::shared_ptr<OBJMesh> objMesh(new OBJMesh(vertices, indices, textureNames));

	return objMesh;
}

std::vector<std::string> OBJModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName)
{
	std::vector<std::string> textureNames;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < m_textureNamesLoaded.size(); ++j)
		{
			if (std::strcmp(m_textureNamesLoaded[j].c_str(), str.C_Str()) == 0)
			{
				textureNames.push_back(m_textureNamesLoaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			std::string filename = str.C_Str();		
			ResourceManager::Instance()->LoadTexture(filename.c_str(), true, filename);

			std::shared_ptr<ITexture> texture = ResourceManager::Instance()->GetTexture(filename);
			texture->SetType(typeName);
			texture->SetPath(filename);
			texture->SetName(filename);

			textureNames.push_back(filename);
			m_textureNamesLoaded.push_back(filename); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textureNames;
}

