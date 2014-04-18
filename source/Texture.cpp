#include "stdafx.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Colour.h"
#include "GameSettings.h"

Texture::Texture(std::string texture_name, int desired_width, int desired_height)
	: m_texture_data(), m_image_openGL_id(0), m_reference_count(0), m_texture_filename(texture_name)
{
	m_texture_data.width = 0;
	m_texture_data.height = 0;
	m_texture_data.data = NULL;

	load_texture_file(texture_name, desired_width, desired_height);
}

Texture::~Texture()
{
	if (m_texture_data.data)
	{
		delete[] m_texture_data.data;
		m_texture_data.data = NULL;
	}
}

unsigned int Texture::get_width() const
{
	return m_texture_data.width;
}

unsigned int Texture::get_height() const
{
	return m_texture_data.height;
}

void Texture::load_texture_file(const std::string& filename, int desired_width, int desired_height)
{
	ILuint image_id;
	set_new_image_id(image_id);
	load_file_to_current_image(filename);
	scale(desired_width, desired_height, ilGetInteger(IL_IMAGE_DEPTH));
	store_image_data_to_texture();
	delete_image_data_from_DevIL_library(&image_id);
}

void Texture::set_new_image_id(ILuint& image_id)
{
	ilGenImages(1, &image_id);
	ilBindImage(image_id);
}

void Texture::load_file_to_current_image(const std::string& filename)
{
    ILboolean retval = ilLoadImage(filename.c_str());
    if (!retval) {
        ILenum error;
        while ((error = ilGetError()) != IL_NO_ERROR) {
            std::string error_message = iluErrorString(error);
			throw error_message;
        }
	}
}

void Texture::store_image_data_to_texture()
{
	m_texture_data.width = ilGetInteger(IL_IMAGE_WIDTH);
	m_texture_data.height  = ilGetInteger(IL_IMAGE_HEIGHT);

	unsigned int size = m_texture_data.width * m_texture_data.height * 4;
	m_texture_data.data = new unsigned char[size];
	ilCopyPixels(0, 0, 0, m_texture_data.width, m_texture_data.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, m_texture_data.data);
}

void Texture::delete_image_data_from_DevIL_library(ILuint* image_id)
{
	ilDeleteImage(*image_id);
}

void Texture::make_texture_active_in_openGL() const
{
	if(!m_image_openGL_id)
	{
		glGenTextures(1, &m_image_openGL_id);
		glBindTexture(GL_TEXTURE_2D, m_image_openGL_id);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, m_texture_data.width, m_texture_data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture_data.data);
	}

	glBindTexture(GL_TEXTURE_2D, m_image_openGL_id);
}

void Texture::set_color_key(const Colour& colour_key)
{
	delete_texture_from_openGL();

	unsigned long count = m_texture_data.width * m_texture_data.height * 4;

	for (unsigned long i = 0; i < count; i+=4)
	{
		if ( (m_texture_data.data[i] == colour_key.red) && (m_texture_data.data[i+1] == colour_key.green) && (m_texture_data.data[i+2] == colour_key.blue) )
		{
			m_texture_data.data[i+3] = 0;
		}
		else
		{
			m_texture_data.data[i+3] = 255;
		}
	}
}

void Texture::scale(ILint width, ILint height, ILint depth)
{
    ILboolean retval = iluScale(width, height, depth);
    if (!retval) {
        ILenum error;
        while ((error = ilGetError()) != IL_NO_ERROR) {
            std::string error_message = iluErrorString(error);
			throw error_message;
        }
	}
}

void Texture::delete_texture_from_openGL()
{
	if (m_image_openGL_id)
	{
		glDeleteTextures(1, &m_image_openGL_id);
		m_image_openGL_id = 0;
	}
}

void Texture::add_reference()
{
	m_reference_count++;
}

void Texture::release_reference()
{
	m_reference_count--;

	if(m_reference_count == 0)
	{
		TextureManager* texture_manager_p = TextureManager::get_instance();
		texture_manager_p->release_texture(m_texture_filename);
	}
}
