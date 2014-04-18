#ifndef CHARACTER_H
#define CHARACTER_H

#include "Collisiable.h"
#include "Renderable.h"

class GraphicRepresentation;
class Boundary;
class Location;
class Attributes;
class Timer;

class Character : public Collisiable, public Renderable
{
	public:
		Character();
		virtual ~Character();

		void stand();
		void walk();
		unsigned int attack();
		bool take_damage(unsigned int damage);

		Location* get_location();
		Boundary* get_boundary();

	protected:	
		GraphicRepresentation* m_graphic_representation_p;
		Boundary* m_boundary_p;
		Location* m_location_p;	
		Attributes* m_attributes_p;

	private:
		void set_hit_or_dead_animation(bool is_dead);

		Timer* m_attacking_rate_timer_p;
};

#endif