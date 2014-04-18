#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Enemy.h"

class Zombie : public Enemy
{
	static const unsigned int INITIAL_ENERGY = 50;
	static const unsigned int INITIAL_RESISTENCY = 0;
	static const unsigned int INITIAL_ATTACK_POWER = 25;
	static const unsigned int INITIAL_MOVING_SPEED = 2;
	static const unsigned int INITIAL_ATTACK_SPEED = 1;

	public:
		Zombie();
		virtual ~Zombie();

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