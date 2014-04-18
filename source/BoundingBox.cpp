#include "stdafx.h"
#include "Image.h"
#include "Rectangle.h"
#include "Collisiable.h"
#include "Location.h"
#include "BoundaryManager.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
	: m_rectangle(NULL)
{
}

BoundingBox::~BoundingBox()
{
	if(m_rectangle)
	{
		delete m_rectangle;
	}
}

Rectangle_int* BoundingBox::get_rectangle()
{
	return m_rectangle;
}

void BoundingBox::create_boundary(Rectangle_int& rect_position)
{
	m_rectangle = new Rectangle_int(rect_position);
}

void BoundingBox::update_boundary(int x_offset, int y_offset)
{
	m_rectangle->offset_rectangle(x_offset, y_offset);
}

void BoundingBox::draw_boundary()
{
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glVertex3i(m_rectangle->left, m_rectangle->top, 0);
		glVertex3i(m_rectangle->left, m_rectangle->bottom, 0);
		glVertex3i(m_rectangle->right, m_rectangle->bottom, 0);
		glVertex3i(m_rectangle->right, m_rectangle->top, 0);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}

bool BoundingBox::is_there_collision_with(Boundary* boundary)
{
	return m_rectangle->does_rectangle_intersect( *(boundary->get_rectangle()) );
}
