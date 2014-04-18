#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
	public:
		virtual ~Enemy(){ }

		virtual void set_location(Location* location_p) = 0;
		virtual void update(const Location& destination, bool should_move) = 0;
		virtual void draw() = 0;
};

#endif