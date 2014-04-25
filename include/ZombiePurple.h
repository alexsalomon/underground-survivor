#ifndef ZOMBIE_PURPLE_H
#define ZOMBIE_PURPLE_H

#include "Enemy.h"

class ZombiePurple : public Enemy
{
	static const unsigned int INITIAL_ENERGY = 50;
	static const unsigned int INITIAL_RESISTENCY = 0;
	static const unsigned int INITIAL_ATTACK_POWER = 25;
	static const unsigned int INITIAL_MOVING_SPEED = 2;
	static const unsigned int INITIAL_ATTACK_SPEED = 1;

	public:
		ZombiePurple();
		virtual ~ZombiePurple();
};

#endif