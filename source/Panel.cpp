#include "stdafx.h"
#include "Panel.h"
#include "GameSettings.h"
#include "Location.h"

Panel::Panel(Rectangle_int* panel_coordinates_p)
	: m_panel_coordinates_p(panel_coordinates_p)
{
	m_panel_origin_p = new Location(m_panel_coordinates_p->left, m_panel_coordinates_p->top);
	m_panel_width = m_panel_coordinates_p->right - m_panel_coordinates_p->left;
	m_panel_height = m_panel_coordinates_p->bottom - m_panel_coordinates_p->top;
}

Panel::~Panel()
{
	if(m_panel_origin_p){ delete m_panel_origin_p; }
	if(m_panel_coordinates_p){ delete m_panel_coordinates_p; }
}

Location* Panel::translate_position(int x_position, int y_position)
{
	Location* new_location_p = new Location();
	new_location_p->x_position = m_panel_coordinates_p->left + x_position;
	new_location_p->y_position = m_panel_coordinates_p->top + y_position;

	return new_location_p;
}

void Panel::update(int damage)
{
}

void Panel::draw()
{
	if(GameSettings::get_settings(GameSettings::Debug::DRAW_PANELS))
	{
		Colour* colour_p = get_panel_drawing_colour();

		glDisable(GL_TEXTURE_2D);
		glColor4ub(colour_p->red, colour_p->green, colour_p->blue, 127);
		glBegin(GL_QUADS);
			glVertex3i(m_panel_coordinates_p->left, m_panel_coordinates_p->top, 0);
			glVertex3i(m_panel_coordinates_p->left, m_panel_coordinates_p->bottom, 0);
			glVertex3i(m_panel_coordinates_p->right, m_panel_coordinates_p->bottom, 0);
			glVertex3i(m_panel_coordinates_p->right, m_panel_coordinates_p->top, 0);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);

		delete colour_p;
	}
}
