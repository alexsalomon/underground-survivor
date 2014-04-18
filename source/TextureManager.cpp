#include "stdafx.h"
#include "Texture.h"
#include "TextureManager.h"

TextureManager* TextureManager::m_texture_manager_p = NULL;

TextureManager* TextureManager::get_instance()
{
	if(m_texture_manager_p == NULL)
		m_texture_manager_p = new TextureManager();

	return m_texture_manager_p;
}

TextureManager::TextureManager()
	: m_texture_map() 
{
	ilInit();
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
	ilEnable(IL_ORIGIN_SET);
}

TextureManager::~TextureManager()
{
	TextureMap::iterator iter = m_texture_map.begin();

	for (iter; iter != m_texture_map.end(); iter++)
	{
		if (iter->second)
		{
			delete iter->second;
		}
	}
}

Texture* TextureManager::create_texture(std::string texture_name, int desired_width, int desired_height)
{
	Texture* texture_p = get_texture(texture_name);

	if(texture_p)
	{
		if(texture_p->get_width() != desired_width || texture_p->get_height() != desired_height)
		{
			release_texture(texture_name);
			texture_p = load_texture_to_memory(texture_name, desired_width, desired_height);
		}	
	}
	else
	{
		texture_p = load_texture_to_memory(texture_name, desired_width, desired_height);
	}

	return texture_p;
}

Texture* TextureManager::get_texture(std::string texture_name)
{
	Texture* texture_p = NULL;
	TextureMap::const_iterator iter = m_texture_map.find(texture_name);

	if(iter != m_texture_map.end())
	{
		texture_p = iter->second;
	}

	return texture_p;
}

Texture* TextureManager::load_texture_to_memory(std::string texture_name, int desired_width, int desired_height)
{
	Texture* texture_p = NULL;

	try
	{
		texture_p = new Texture(texture_name, desired_width, desired_height);
	}
	catch (Exception& message)
	{
		delete texture_p;
		throw message;
	}

	m_texture_map[texture_name] = texture_p;
	return texture_p;
}

bool TextureManager::release_texture(std::string texture_name)
{
	bool found = false;
	TextureMap::const_iterator iter = m_texture_map.find(texture_name);

	if(iter != m_texture_map.end())
	{
		if(iter->second)
		{
			delete iter->second;
		}

		m_texture_map.erase(iter);
		found = true;
	}

	return found;
}
