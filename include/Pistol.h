#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon
{
	static const unsigned int WAITING_TIME_BETWEEN_FIRING_BULLETS = 1;
	static const unsigned int DAMAGE = 50;

	public:
		Pistol();
		~Pistol();

		BulletType get_bullet_type();
		unsigned int get_damage();
		void fire();
		bool is_ready_to_fire();		
};

#endif
