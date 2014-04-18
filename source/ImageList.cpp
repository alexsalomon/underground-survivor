#include "stdafx.h"
#include "Image.h"
#include "ImageList.h"

ImageList::ImageList()
	: m_image_list()
{
}

ImageList::ImageList(const ImageList& other_image)
{
	copy_list(other_image);
}

ImageList::~ImageList()
{
}

ImageList& ImageList::operator= (const ImageList& other_image)
{
	clear_list();
	copy_list(other_image);

	return *this;
}

void ImageList::copy_list(const ImageList& other_image)
{
	ImageList_type::const_iterator iter = other_image.m_image_list.begin();
	for (iter; iter != other_image.m_image_list.end(); iter++)
	{
		m_image_list.push_back(*iter);
	}
	m_current_image_iter = m_image_list.begin();
}

void ImageList::clear_list()
{
	m_image_list.clear();
	m_current_image_iter = m_image_list.end();
}

void ImageList::append_image(Image_ptr image_p)
{
	m_image_list.push_back(image_p);
	m_current_image_iter = m_image_list.begin();
}

unsigned ImageList::get_images_count() const
{
	return (unsigned)m_image_list.size();
}

void ImageList::go_to_first_image()
{
	m_current_image_iter = m_image_list.begin();
}

bool ImageList::go_to_next_image()
{
	if (m_current_image_iter != m_image_list.end() )
		m_current_image_iter++;
	else
		return false;

	if (m_current_image_iter == m_image_list.end() )
	{
		m_current_image_iter = m_image_list.begin();
		return true;
	}
	return false;
}

Image_ptr ImageList::get_current_image() const
{
	Image_ptr image_p = NULL;

	if (m_current_image_iter != m_image_list.end() )
	{
		image_p = *m_current_image_iter;
	}

	return image_p;
}

