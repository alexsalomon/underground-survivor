#ifndef ZOMBIE_GRUNT_PURPLE_H
#define ZOMBIE_GRUNT_PURPLE_H

#include "Enemy.h"

class ZombieGruntPurple : public Enemy
{
	static const unsigned int INITIAL_ENERGY = 400;
	static const unsigned int INITIAL_RESISTENCY = 0;
	static const unsigned int INITIAL_ATTACK_POWER = 75;
	static const unsigned int INITIAL_MOVING_SPEED = 1;
	static const unsigned int INITIAL_ATTACK_SPEED = 1;

	public:
		ZombieGruntPurple();
		virtual ~ZombieGruntPurple();
};

#endif