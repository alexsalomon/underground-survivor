#include "stdafx.h"
#include "Image.h"
#include "Rectangle.h"
#include "Collisiable.h"
#include "Location.h"
#include "BoundaryManager.h"
#include "InvertedBoundingBox.h"

InvertedBoundingBox::InvertedBoundingBox()
	: m_rectangle(NULL)
{
}

InvertedBoundingBox::~InvertedBoundingBox()
{
	if(m_rectangle)
	{
		delete m_rectangle;
	}
}

Rectangle_int* InvertedBoundingBox::get_rectangle()
{
	return m_rectangle;
}

void InvertedBoundingBox::create_boundary(Rectangle_int& rect_position)
{
	m_rectangle = new Rectangle_int(rect_position);
}

void InvertedBoundingBox::update_boundary(int x_offset, int y_offset)
{
	m_rectangle->offset_rectangle(x_offset, y_offset);
}

void InvertedBoundingBox::draw_boundary()
{
	glDisable(GL_TEXTURE_2D);
	glColor4ub(248, 236, 90, 127);
	glBegin(GL_QUADS);
		glVertex3i(m_rectangle->left, m_rectangle->top, 0);
		glVertex3i(m_rectangle->left, m_rectangle->bottom, 0);
		glVertex3i(m_rectangle->right, m_rectangle->bottom, 0);
		glVertex3i(m_rectangle->right, m_rectangle->top, 0);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}

bool InvertedBoundingBox::is_there_collision_with(Boundary* boundary)
{
	bool is_inside_rectangle = true;
	Rectangle_int* rect_2 = boundary->get_rectangle();

	if((m_rectangle->left < rect_2->left) && (m_rectangle->right > rect_2->right))
	{
		if((m_rectangle->top < rect_2->top) && (m_rectangle->bottom > rect_2->bottom))
		{
			is_inside_rectangle = false;
		}
	}

	return is_inside_rectangle;
}