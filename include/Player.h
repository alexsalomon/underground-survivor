#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

typedef enum key
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
}KEY;

class Background;
class Bullet;
class Weapon;

class Player : public Character
{
	static const unsigned int INITIAL_ENERGY = 100;
	static const unsigned int INITIAL_RESISTENCY = 0;
	static const unsigned int INITIAL_ATTACK_POWER = 0; //depends on weapon
	static const unsigned int INITIAL_MOVING_SPEED = 8;
	static const unsigned int INITIAL_ATTACK_SPEED = 0; //depends on weapon

	static const unsigned int BOUNDARY_WIDTH = 47;
	static const unsigned int BOUNDARY_HEIGHT = 52;
	static const unsigned int NUMBER_OF_DIRECTION_KEYS = 4;

	public:
		Player();
		~Player();

		Bullet* shoot(WPARAM x_coordinate, WPARAM y_coordinate);
		unsigned int get_total_inflicted_damage();

		void on_keyup(KEY key);
		void on_keydown(KEY key);
		void update(Background* background_p);
		void draw();

	private:
		void initialize_pressed_keys_array_to_false();
		void create_boundary();
		void move_location_to_center_of_image();
		Location* calculate_character_offset();
		void update_character_location(const Location& character_offset);
		bool was_any_key_pressed() const;
		void draw_boundary_if_applicable(bool is_draw_boundary_enabled);
				
		Weapon* m_weapon_p;
		bool m_keys_down[NUMBER_OF_DIRECTION_KEYS];
};

#endif