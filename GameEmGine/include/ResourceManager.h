#pragma once
#include <GL\glew.h>
#include <unordered_map>
#include "Texture.h"
#include "ImageLoader.h"

struct Texture2DCache
{						 
	Texture2D& getTexture(const char*);

private:
	std::unordered_map<const char*, Texture2D> _texture;
};
		
struct Texture3DCache
{		 
	Texture3D& getTexture(const char*);

private:
	std::unordered_map<const char*, Texture3D> _texture;
};

class ResourceManager
{
public:
	static Texture2D getTexture2D(const char*);
	static Texture3D getTexture3D(const char*);

private:
	static Texture2DCache _cache2D;
	static Texture3DCache _cache3D;
};

