#include "stdafx.h"
#include "Attributes.h"

Attributes::Attributes(int energy, int resistency, int attack_power, int moving_speed, int attack_speed) 
	: energy(energy), resistency(resistency), attack_power(attack_power), moving_speed(moving_speed), attack_speed(attack_speed)
{
}

Attributes::Attributes() 
	: energy(0), resistency(0), attack_power(0), moving_speed(0), attack_speed(0)
{
}

Attributes::~Attributes()
{
}

bool Attributes::inflict_damage(int damage)
{
	bool is_dead = false;

	energy -= damage;
	if(energy <= 0)
	{
		is_dead = true;
	}

	return is_dead;
}

bool Attributes::is_dead()
{
	return (energy <= 0);
}
