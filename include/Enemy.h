#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
	public:
		Enemy();
		virtual ~Enemy();

		void update(const Location& destination, bool should_move);
		void draw();
		void set_location(Location* location_p);

	private:
		void create_boundary();
		void move_location_to_center_of_image();
		Location* calculate_character_offset(const Location& destination);
		void update_character_location(const Location& character_offset);
		void draw_boundary_if_applicable(bool is_draw_boundary_enabled);
};

#endif