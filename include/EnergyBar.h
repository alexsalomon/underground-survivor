#ifndef ENERGY_BAR_H
#define ENERGY_BAR_H

#include "Rectangle.h"

class Colour;
class Location;

class EnergyBar
{
	static const int DEFAULT_OUTER_BAR_WIDTH = 540;
	static const int DEFAULT_OUTER_BAR_HEIGHT = 40;
	static const int DISTANCE_BETWEEN_OUTTER_AND_INNER_RECT = 4;
	static const int MAXIMUM_ENERGY = 100;

	public:
		EnergyBar(Location* location_p, unsigned int energy, int width, int height);
		EnergyBar(Location* location_p, unsigned int energy);
		EnergyBar();
		~EnergyBar();

		void set_location(Location* location_p);
		Rectangle_int* get_rectangle();
		void update_offset(const Location& offset);
		void update(unsigned int damage);
		void draw();

	private:
		void initialize();
		void draw_rectangle(const Rectangle_int& rect_coordinates, const Colour& colour_p);
		Colour* get_colour_based_on_energy();
		void destroy_rectangles_if_applicable();

		Location* m_location_p;
		Rectangle_int* m_outter_rect_p;
		Rectangle_int* m_medium_rect_p;
		Rectangle_int* m_inner_rect_p;
		unsigned int m_outer_bar_width;
		unsigned int m_outer_bar_height;
		unsigned int m_inner_bar_full_width;
		unsigned int m_energy;
};

#endif
