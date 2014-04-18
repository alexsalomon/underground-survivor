#include "stdafx.h"
#include "Character.h"
#include "GraphicRepresentation.h"
#include "BoundaryManager.h"
#include "Location.h"
#include "Attributes.h"
#include "Timer.h"

Character::Character()
	: m_graphic_representation_p(NULL), m_boundary_p(NULL), m_location_p(NULL), m_attributes_p(NULL), m_attacking_rate_timer_p(NULL)
{
	m_attacking_rate_timer_p = new Timer();
	m_attacking_rate_timer_p->start(0);
}

Character::~Character()
{
	if(m_graphic_representation_p){ delete m_graphic_representation_p; }
	if(m_boundary_p){ delete m_boundary_p; }
	if(m_location_p){ delete m_location_p; }
	if(m_attributes_p){ delete m_attributes_p; }
	if(m_attacking_rate_timer_p){ delete m_attacking_rate_timer_p; }
}

Boundary* Character::get_boundary()
{
	return m_boundary_p;
}

Location* Character::get_location()
{
	return m_location_p;
}

void Character::stand()
{
	m_graphic_representation_p->set_current_action("Stand");
}

void Character::walk()
{
	m_graphic_representation_p->set_current_action("Walk");
}

unsigned int Character::attack()
{
	unsigned int damage = 0;
	m_graphic_representation_p->set_current_action("Attack");

	if(m_attacking_rate_timer_p->is_timeout())
	{
		damage = m_attributes_p->attack_power;
		m_attacking_rate_timer_p->start(m_attributes_p->attack_speed);
	}

	return damage;
}

bool Character::take_damage(unsigned int damage)
{
	unsigned int actual_damage = damage - m_attributes_p->resistency;
	bool is_dead = m_attributes_p->inflict_damage(actual_damage);
	set_hit_or_dead_animation(is_dead);
	return is_dead;
}

void Character::set_hit_or_dead_animation(bool is_dead)
{
	if(is_dead)
	{
		m_graphic_representation_p->set_current_action("Dead");
	}
	else
	{ 
		//TODO: a damaged player will still have the same animations but a red blinking image on it
		// Can do that by changing the texture colour - or drawing something on top of it with openGL that does something similar
		// Basically, change the colour for like a second, than change it back for annother second an so on until damaged timer is up
		m_graphic_representation_p->set_current_action("Damaged");
	}
}
