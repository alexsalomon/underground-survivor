#ifndef BULLET_H
#define BULLET_H

#include "Collisiable.h"
#include "Renderable.h"

class Location;
class Boundary;
class AnimatedSprite;

class Bullet : public Collisiable, public Renderable
{
	static const unsigned int BULLET_MOVING_SPEED = 25;
	static const unsigned int ANIMATION_WIDTH = 16;
	static const unsigned int ANIMATION_HEIGHT = 16;
	static const unsigned int BOUNDARY_WIDTH = 16;
	static const unsigned int BOUNDARY_HEIGHT = 16;

	public:
		Bullet(Location* initial_location_p, Location* destination_p);
		Bullet();
		virtual ~Bullet();

		void set_destination(Location* destination_p);
		void set_location(Location* location_p);
		Boundary* get_boundary();
		void update();
		void draw();

	private:
		int calculate_angle(Location* destination_p);
		void load_animation_based_on_angle(int angle);		
		void calculate_offset(Location* destination_p);
		void create_boundary();
		void update_location();
		void draw_boundary_if_applicable(bool is_draw_boundary_enabled);

		AnimatedSprite* m_animated_sprite_p;
		Location* m_location_p;
		Location* m_bullet_offset;
		Boundary* m_boundary_p;
};

#endif