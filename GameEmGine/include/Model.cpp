#include "Model.h" 

using namespace std;
Model::Model()
{}

Model::Model(const char * path)
{
	loadModel(path);
}

Model::~Model()
{}

void Model::render(GLSLCompiler shader)
{
	for(GLuint a = 0; a < meshes.size(); a++)
		meshes[a].render(shader);
}

void Model::loadModel(const char * path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("Load Model Failed: %s\n",importer.GetErrorString());
		return;
	}
	dir = string(path).substr(0, strrchr(path, '/') - path);
	printf("%s\n", dir.c_str());

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for(GLuint a = 0; a < node->mNumMeshes; a++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[a]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for(GLuint a = 0; a < node->mNumChildren; a++)
		processNode(node->mChildren[a], scene);

}

GLuint Model::textureFromFile(const char * path)
{
	GLuint texID;
	int width, height;

	unsigned char *image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	if(image == nullptr)
	{
		printf("failed\n");
		return NULL;
	}

	//Bind texture to model
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return texID;
}

std::map<string, Texture2D> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType texType, string typeName)
{
	map<string, Texture2D> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(texType); i++)
	{
		aiString str;
		mat->GetTexture(texType, i, &str);
		Texture2D texture;
		texture = ResourceManager::getTexture2D((string(dir) + '/' + str.C_Str()).c_str());
		texture.type = typeName;
		texture.path = str.C_Str();
		textures.insert({texture.path,texture});
		printf("loaded Material: %s\n", str.C_Str());
	}

	return textures;
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)

{
	std::vector<Vertex3D> verts;
	std::vector<GLuint> indecies;
	std::vector<Texture2D> textures;
	for(int a = 0; a < mesh->mNumVertices; a++)
	{
		Vertex3D vert;
		Coord3D vec;

		vec.x = mesh->mVertices[a].x;
		vec.y = mesh->mVertices[a].y;
		vec.z = mesh->mVertices[a].z;
		vert.coord = vec;


		vec.x = mesh->mNormals[a].x;
		vec.y = mesh->mNormals[a].y;
		vec.z = mesh->mNormals[a].z;
		vert.norm = vec;

		if(mesh->mTextureCoords[0])
		{
			UV uv;

			uv.u = mesh->mTextureCoords[0][a].x;
			uv.v = mesh->mTextureCoords[0][a].y;

			vert.uv = uv;

		}

		verts.push_back(vert);
	}
	for(int a = 0; a < mesh->mNumFaces; a++)
	{
		aiFace norm = mesh->mFaces[a];
		for(int b = 0; b < norm.mNumIndices; b++)
			indecies.push_back(norm.mIndices[b]);
	}

	if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		//some stuff about speular and dufused textures
		std::map<string, Texture2D>
			diffuseMaps = loadMaterialTextures(material,
											   aiTextureType_DIFFUSE, "diffuseTexture"),

			specularMaps = loadMaterialTextures(material,
												aiTextureType_SPECULAR, "specularTexture");

		for(auto &a : diffuseMaps)
			textures.insert(textures.end(), a.second);
		for(auto &a : specularMaps)
			textures.insert(textures.end(), a.second);
	}
	return Mesh(verts, indecies, textures);
}
