#ifndef PANEL_H
#define PANEL_H

#include "Rectangle.h"
#include "Colour.h"

class Location;
class Colour;

class Panel
{
	public:
		Panel(Rectangle_int* panel_coordinates);
		virtual ~Panel();

		virtual void update(int damage);
		virtual void draw();
		virtual Colour* get_panel_drawing_colour() = 0;

	protected:
		Location* translate_position(int x_position, int y_position);

		Rectangle_int* m_panel_coordinates_p;
		Location* m_panel_origin_p;
		unsigned int m_panel_width;
		unsigned int m_panel_height;
};

#endif
