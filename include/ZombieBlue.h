#ifndef ZOMBIE_BLUE_H
#define ZOMBIE_BLUE_H

#include "Enemy.h"

class ZombieBlue : public Enemy
{
	static const unsigned int INITIAL_ENERGY = 100;
	static const unsigned int INITIAL_RESISTENCY = 0;
	static const unsigned int INITIAL_ATTACK_POWER = 50;
	static const unsigned int INITIAL_MOVING_SPEED = 3;
	static const unsigned int INITIAL_ATTACK_SPEED = 1;

	public:
		ZombieBlue();
		virtual ~ZombieBlue();
};

#endif