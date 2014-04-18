#include "stdafx.h"
#include "Image.h"
#include "ImageList.h"
#include "AnimationLoader.h"

AnimationLoader::AnimationLoader(const std::string& filename, unsigned images_per_row, unsigned number_of_rows, unsigned image_width, unsigned image_height)
	: m_filename(filename), m_images_per_row(images_per_row), m_image_width(image_width), m_image_height(image_height), m_number_of_rows(number_of_rows)
{

}

AnimationLoader::~AnimationLoader()
{

}

ImageList AnimationLoader::get_animation(unsigned start_index, unsigned stop_index)
{
	ImageList new_image_list;

	for (unsigned i = start_index; i <= stop_index; i++)
	{
		unsigned row = i / m_images_per_row;
		unsigned col = i % m_images_per_row;

		Rectangle_int image_rectangle( (row*m_image_height), ((row+1)*m_image_height), (col*m_image_width), ((col+1)*m_image_width) );
		new_image_list.append_image(Image::create_image(m_filename, m_image_width*m_images_per_row, m_image_height*m_number_of_rows, image_rectangle));
	}

	return new_image_list;
}
