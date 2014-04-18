#ifndef WEAPON_H
#define WEAPON_H

typedef enum BulletType
{
	PISTOL_BULLET = 0		
}BULLET_TYPE;

#include "Timer.h"

class Weapon
{
	public:
		virtual ~Weapon(){  }

		virtual BulletType get_bullet_type() = 0;
		virtual unsigned int get_damage() = 0;
		virtual void fire() = 0;
		virtual bool is_ready_to_fire() = 0;
		
	protected:
		Timer* m_fire_weapon_timer_p;
};

#endif