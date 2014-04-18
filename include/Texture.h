#ifndef TEXTURE_H
#define TEXTURE_H

class Colour;

class Texture
{
	friend class TextureManager; //make sure that only the TextureManager class can create textures

	struct TextureData
	{
		unsigned int width;
		unsigned int height;
		unsigned char* data;
	};

	public:
		~Texture();
		unsigned int get_width() const;
		unsigned int get_height() const;

		void make_texture_active_in_openGL() const;
		void set_color_key(const Colour& colour_key);
		void scale(ILint width, ILint height, ILint depth);
		void add_reference();
		void release_reference();

	private:
		Texture(std::string texture_name, int desired_width, int desired_height);
		void load_texture_file(const std::string& filename, int desired_width, int desired_height);
		void set_new_image_id(ILuint& image_id);
		void load_file_to_current_image(const std::string& filename);
		void store_image_data_to_texture();
		void delete_image_data_from_DevIL_library(ILuint* image_id);
		void delete_texture_from_openGL();

		TextureData m_texture_data;
		mutable GLuint m_image_openGL_id;
		int m_reference_count;
		std::string m_texture_filename;
};

#endif