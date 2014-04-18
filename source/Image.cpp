#include "stdafx.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Image.h"
#include "GameSettings.h"
#include "Location.h"

Image::Image(const std::string& filename, int desired_width, int desired_height)
  : m_texture_p(NULL), m_rect_texture_coordinates()
{
	try
	{
		TextureManager* texture_manager_p = TextureManager::get_instance();
		m_texture_p = texture_manager_p->create_texture(filename, desired_width, desired_height); 
		m_texture_p->add_reference();

		m_rect_texture_coordinates.top = 0;
		m_rect_texture_coordinates.left = 0;
		m_rect_texture_coordinates.bottom = m_texture_p->get_height();
		m_rect_texture_coordinates.right = m_texture_p->get_width();
	}
	catch(Exception& message)
	{
		throw message;
	}
}

Image::Image(const std::string& filename, int desired_width, int desired_height, const Rectangle_int& texture_coordinates)
  : m_texture_p(NULL), m_rect_texture_coordinates(texture_coordinates)
{
	try
	{
		TextureManager* texture_manager_p = TextureManager::get_instance();
		m_texture_p = texture_manager_p->create_texture(filename, desired_width, desired_height); 
		m_texture_p->add_reference();
	}
	catch(Exception& message)
	{
		throw message;
	}
}

Image_ptr Image::create_image(const std::string& filename, int desired_width, int desired_height)
{
	return new Image(filename, desired_width, desired_height);
}

Image_ptr Image::create_image(const std::string& filename, int desired_width, int desired_height, const Rectangle_int& texture_coordinates)
{
	return new Image(filename, desired_width, desired_height, texture_coordinates);
}

Image::~Image()
{
	if (m_texture_p)
		m_texture_p->release_reference();
}

Texture* Image::get_texture() const
{
	return m_texture_p;
}

void Image::draw_image(const Location& location)
{
	if (m_texture_p)
	{
		m_texture_p->make_texture_active_in_openGL();
		float* coordinates = calculate_coordinates_of_image(m_rect_texture_coordinates);
		draw_textured_rectangle(coordinates, location.x_position, location.y_position, m_rect_texture_coordinates);
	}
}

void Image::draw_image(const Location& location, const Rectangle_int& rect)
{
	validate_rectangle_argument(rect);

	if (m_texture_p)
	{
		m_texture_p->make_texture_active_in_openGL();
		Rectangle_int new_texture_rectangle = rect;
		new_texture_rectangle.offset_rectangle(m_rect_texture_coordinates.left, m_rect_texture_coordinates.top);
		float* coordinates = calculate_coordinates_of_image(new_texture_rectangle);
		draw_textured_rectangle(coordinates, location.x_position, location.y_position, new_texture_rectangle);
	}
}

float* Image::calculate_coordinates_of_image(const Rectangle_int& rect) const
{
	float* coordinates = new float[4];

	coordinates[0] = ((float)rect.top) / m_texture_p->get_height();
	coordinates[1] = ((float)rect.bottom) / m_texture_p->get_height();
	coordinates[2] = ((float)rect.left) / m_texture_p->get_width();
	coordinates[3] = ((float)rect.right) / m_texture_p->get_width();

	return coordinates;
}

void Image::draw_textured_rectangle(float coordinates[], int x_position, int y_position, const Rectangle_int& rect) const
{
	float top = coordinates[0];
	float bottom = coordinates[1];
	float left = coordinates[2];
	float right = coordinates[3];

	glBegin(GL_QUADS);
		glTexCoord2f(left,top);		glVertex3i(x_position, y_position, 0);
		glTexCoord2f(left,bottom);	glVertex3i(x_position, y_position + rect.get_height(), 0);
		glTexCoord2f(right,bottom);	glVertex3i(x_position + rect.get_width(), y_position + rect.get_height(), 0);
		glTexCoord2f(right,top);	glVertex3i(x_position + rect.get_width(), y_position, 0);
	glEnd();

	delete coordinates;
}

void Image::validate_rectangle_argument(const Rectangle_int& rect) const
{
	assert(rect.top >= 0);
	assert(rect.bottom <= m_rect_texture_coordinates.get_height());
	assert(rect.left >= 0);
	assert(rect.right <= m_rect_texture_coordinates.get_width());
}
