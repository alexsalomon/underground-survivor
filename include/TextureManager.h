#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class Texture;
class TextureManager
{
	typedef std::map<std::string, Texture*> TextureMap;

	public:
		static TextureManager* get_instance();
		~TextureManager();

		Texture* create_texture(std::string texture_name, int desired_width, int desired_height);
		bool release_texture(std::string texture_name);
		Texture* get_texture(std::string texture_name);

	private:
		TextureManager();
		Texture* load_texture_to_memory(std::string texture_name, int desired_width, int desired_height);

		static TextureManager* m_texture_manager_p;
		TextureMap m_texture_map;
};

#endif