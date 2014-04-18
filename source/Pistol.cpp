#include "stdafx.h"
#include "Pistol.h"

Pistol::Pistol()
{
	m_fire_weapon_timer_p = new Timer();
	m_fire_weapon_timer_p->start(0);
}

Pistol::~Pistol()
{
}

BulletType Pistol::get_bullet_type()
{
	return PISTOL_BULLET;
}

unsigned int Pistol::get_damage()
{
	return DAMAGE;
}

void Pistol::fire()
{
	m_fire_weapon_timer_p->start(WAITING_TIME_BETWEEN_FIRING_BULLETS);
}

bool Pistol::is_ready_to_fire()
{
	bool ready_to_fire = false;

	if(m_fire_weapon_timer_p->is_timeout())
	{
		ready_to_fire = true;
	}

	return ready_to_fire;
}
