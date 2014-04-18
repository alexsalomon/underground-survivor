#include "stdafx.h"
#include "EnemyGraphicRepresentation.h"
#include "GameSettings.h"
#include "EnergyBar.h"

EnemyGraphicRepresentation::EnemyGraphicRepresentation(int enemys_energy, int animation_width, int animation_height)
	: GraphicRepresentation()
{
	m_energy_bar_p = new EnergyBar(new Location(), enemys_energy, animation_width, (int)(animation_height*0.20));
}

EnemyGraphicRepresentation::~EnemyGraphicRepresentation()
{
	if(m_energy_bar_p){ delete m_energy_bar_p; }
}

void EnemyGraphicRepresentation::set_animation_position(Location* location_p)
{
	GraphicRepresentation::set_animation_position(location_p);

	Location* energy_location_p = new Location();
	energy_location_p->x_position = (int)(location_p->x_position);
	energy_location_p->y_position = (int)(location_p->y_position*2.65);
	m_energy_bar_p->set_location(energy_location_p);
}

void EnemyGraphicRepresentation::update(const Location& offset, unsigned int damage, bool should_update_offset)
{
	GraphicRepresentation::update(offset, should_update_offset);
	m_energy_bar_p->update_offset(offset);
	//m_energy_bar_p->update(damage);
}

void EnemyGraphicRepresentation::draw()
{
	GraphicRepresentation::draw();
	draw_energy_bar();
}

void EnemyGraphicRepresentation::draw_energy_bar()
{
	if(GameSettings::get_settings(GameSettings::Debug::DRAW_ENERGY_BARS))
	{
		m_energy_bar_p->draw();
	}
}
