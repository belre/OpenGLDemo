#include "Model.h"

#include <iostream>


Model::Model()
{
	
}

void Model::LoadModel(const std::string& file_name)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file_name, 
	aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals |
				aiProcess_JoinIdenticalVertices);

	if( !scene ) 
	{
		std::cerr << "Scene" << importer.GetErrorString() << "failed to load:"
			<< file_name << std::endl;
		return;
	}

	LoadNode(scene->mRootNode, scene);
	LoadMaterials(scene);
}

void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	for( size_t i = 0 ; i < node->mNumMeshes; i++ ) 
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for(size_t i = 0; i < mesh->mNumVertices; i++) 
	{
		vertices.insert(vertices.end(), { 
			mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z
		});

		if(mesh->mTextureCoords[0]) 
		{
			vertices.insert(vertices.end(), {
				mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y
			});
		}
		else 
		{
			vertices.insert(vertices.end(), {
				0.0f, 0.0f
			});
		}

		vertices.insert(vertices.end(), {
			-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z
		});
	}

	for(size_t i = 0 ; i < mesh->mNumFaces; i++) 
	{
		aiFace face = mesh->mFaces[i];

		for(size_t j = 0 ; j < face.mNumIndices; j++) 
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* new_mesh = new Mesh();
	new_mesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());

	_meshList.push_back(new_mesh);
	_meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene* scene)
{
	_textureList.resize(scene->mNumMaterials, nullptr);

	for(size_t i = 0 ; i < scene->mNumMaterials; i++ ) 
	{
		aiMaterial* material = scene->mMaterials[i];


		if(material->GetTextureCount(aiTextureType_DIFFUSE)) 
		{
			aiString path;
			if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) 
			{
				int idx = std::string(path.data).rfind("\\");
				std::string file_name = std::string(path.data).substr(idx + 1);
				std::string tex_path = "./Textures/" + file_name;

				_textureList[i] = new Texture(tex_path);

				if(!_textureList[i]->LoadTexture()) 
				{
					std::cerr << "Failed to load.texture at " << tex_path << std::endl;
					delete _textureList[i];
					_textureList[i] = nullptr;
				}
			}

			if(!_textureList[i]) 
			{
				_textureList[i] = new Texture("./Textures/plain.png");
				_textureList[i]->LoadTextureAlpha();
			}
		}

	}
}

void Model::RenderModel()
{
	for (size_t i = 0; i < _meshList.size(); i++)
	{
		unsigned int material_index = _meshToTex[i];

		if(material_index < _textureList.size() && _textureList[material_index]) 
		{
			_textureList[material_index]->UseTexture();
		}

		_meshList[i]->RenderMesh();
	}
}

void Model::ClearModel()
{
	for (size_t i = 0; i < _meshList.size(); i++)
	{
		if (_meshList[i])
		{
			delete _meshList[i];
			_meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < _textureList.size(); i++)
	{
		if (_textureList[i])
		{
			delete _textureList[i];
			_textureList[i] = nullptr;
		}
	}
}


Model::~Model()
{
	
}

