#include "ResourceManager.h"

Texture2DCache ResourceManager::_cache2D;
Texture3DCache ResourceManager::_cache3D;

Texture2D& Texture2DCache::getTexture(const char * path)
{
	auto it = _texture.find(path);

	if(it == _texture.end())
	{
			Texture2D tmp= ImageLoader::loadImage2D(path);
			_texture.insert({path,tmp});
			return tmp;
	}
	//printf("cashed image loaded\n\n");
	return it->second;
}

Texture3D & Texture3DCache::getTexture(const char *path)
{
	auto it = _texture.find(path);

	if(it == _texture.end())
	{
		Texture3D tmp = ImageLoader::loadImage3D(path);
		_texture.insert({path,tmp});
		return tmp;
	}
	return it->second;
}

Texture2D ResourceManager::getTexture2D(const char *path)
{
	return _cache2D.getTexture(path);
}
Texture3D ResourceManager::getTexture3D(const char *path)
{
	return _cache3D.getTexture(path);
}

