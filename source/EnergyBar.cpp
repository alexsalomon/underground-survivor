#include "stdafx.h"
#include "EnergyBar.h"
#include "Colour.h"
#include "Location.h"

EnergyBar::EnergyBar(Location* location_p, unsigned int energy, int width, int height)
	: m_location_p(location_p), m_energy(energy), m_outter_rect_p(NULL), m_medium_rect_p(NULL), m_inner_rect_p(NULL)
{
	m_outer_bar_width = width;
	m_outer_bar_height = height;
	initialize();
}

EnergyBar::EnergyBar(Location* location_p, unsigned int energy)
	: m_location_p(location_p), m_energy(energy), m_outter_rect_p(NULL), m_medium_rect_p(NULL), m_inner_rect_p(NULL)
{
	m_outer_bar_width = DEFAULT_OUTER_BAR_WIDTH;
	m_outer_bar_height = DEFAULT_OUTER_BAR_HEIGHT;
	initialize();
}

EnergyBar::EnergyBar()
	: m_location_p(NULL), m_energy(0), m_outer_bar_width(0), m_outer_bar_height(0), m_outter_rect_p(NULL), m_medium_rect_p(NULL), m_inner_rect_p(NULL)
{
}

void EnergyBar::initialize()
{
	int top = m_location_p->y_position;
	int bottom = top + m_outer_bar_height;
	int left = m_location_p->x_position;
	int right = left + m_outer_bar_width;

	m_inner_bar_full_width = m_outer_bar_width - DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT*2;

	destroy_rectangles_if_applicable();

	m_outter_rect_p = new Rectangle_int(top, bottom, left, right);
	m_medium_rect_p = new Rectangle_int(top + DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT, bottom - DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT, left + DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT, right - DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT);
	m_inner_rect_p = new Rectangle_int(top + DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT, bottom - DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT, left + DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT, right - DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT);
}

EnergyBar::~EnergyBar()
{
	if(m_location_p){ delete m_location_p; }
	destroy_rectangles_if_applicable();
}

void EnergyBar::destroy_rectangles_if_applicable()
{
	if(m_inner_rect_p){ delete m_inner_rect_p; }
	if(m_medium_rect_p){ delete m_medium_rect_p; }
	if(m_outter_rect_p){ delete m_outter_rect_p; }
}

Rectangle_int* EnergyBar::get_rectangle()
{
	return new Rectangle_int(*m_outter_rect_p);
}

void EnergyBar::set_location(Location* location_p)
{
	if(m_location_p){ delete m_location_p; }
	m_location_p = location_p;
	initialize();
}

void EnergyBar::update_offset(const Location& offset)
{
	m_outter_rect_p->offset_rectangle(offset.x_position, offset.y_position);
	m_medium_rect_p->offset_rectangle(offset.x_position, offset.y_position);
	m_inner_rect_p->offset_rectangle(offset.x_position, offset.y_position);
}

void EnergyBar::update(unsigned int damage)
{
	m_energy -= damage;
	unsigned int new_width = (int)(m_inner_bar_full_width*((double)m_energy / 100.00));
	m_inner_rect_p->right = m_inner_rect_p->left + (m_inner_bar_full_width - (m_inner_bar_full_width - new_width));

	if(m_inner_rect_p->right < m_inner_rect_p->left)
	{
		m_inner_rect_p->right = m_inner_rect_p->left;
	}

	assert(m_inner_rect_p->is_valid());
}

void EnergyBar::draw()
{
	Colour* inner_bar_colour = get_colour_based_on_energy();

	draw_rectangle(*m_outter_rect_p, Colour(0, 0, 0));
	draw_rectangle(*m_medium_rect_p, Colour(0, 0, 0));
	draw_rectangle(*m_inner_rect_p, *inner_bar_colour);

	delete inner_bar_colour;
}

Colour* EnergyBar::get_colour_based_on_energy()
{
	Colour* bar_colour = new Colour(34, 177, 76);

	if(m_energy <= MAXIMUM_ENERGY*0.25)
	{
		bar_colour->set_colour(255, 0, 0);
	}
	else if(m_energy <= MAXIMUM_ENERGY*0.50)
	{
		bar_colour->set_colour(255, 217, 0);
	}

	return bar_colour;
}

void EnergyBar::draw_rectangle(const Rectangle_int& rect_coordinates, const Colour& colour_p)
{
	glDisable(GL_TEXTURE_2D);
	glColor3ub(colour_p.red, colour_p.green, colour_p.blue);
	glBegin(GL_QUADS);
		glVertex3i(rect_coordinates.left, rect_coordinates.top, 0);
		glVertex3i(rect_coordinates.left, rect_coordinates.bottom, 0);
		glVertex3i(rect_coordinates.right, rect_coordinates.bottom, 0);
		glVertex3i(rect_coordinates.right, rect_coordinates.top, 0);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}
