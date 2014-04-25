#include "stdafx.h"
#include "Enemy.h"
#include "Location.h"
#include "Attributes.h"
#include "GameSettings.h"
#include "BoundaryManager.h"
#include "GraphicRepresentation.h"

Enemy::Enemy()
{
	m_location_p = new Location();
	create_boundary();
	move_location_to_center_of_image();
}

Enemy::~Enemy()
{
}

void Enemy::create_boundary()
{
	BoundaryManager* boundary_manager_p = BoundaryManager::get_instance();
	m_boundary_p = boundary_manager_p->choose_strategy(BOUNDING_BOX);

	int top = (m_location_p->y_position + (int)(GameSettings::get_window_height()*0.01));
	int bottom = (m_location_p->y_position + (int)(GameSettings::get_window_height()*0.08));
	int left = (m_location_p->x_position + (int)(GameSettings::get_window_width()*0.008));
	int right = (m_location_p->x_position + (int)(GameSettings::get_window_width()*0.028));

	m_boundary_p->create_boundary(Rectangle_int(top, bottom, left, right));
}

void Enemy::move_location_to_center_of_image()
{
	Rectangle_int* boundary = m_boundary_p->get_rectangle();	
	m_location_p->x_position += (boundary->right - boundary->left) / 2;
	m_location_p->y_position += (boundary->bottom - boundary->top) / 2;
}

void Enemy::set_location(Location* location_p)
{
	if(m_location_p){ delete m_location_p; }
	if(m_boundary_p){ delete m_boundary_p; }

	m_location_p = location_p;
	m_graphic_representation_p->set_animation_position(m_location_p);
	create_boundary();
	move_location_to_center_of_image();
}

void Enemy::update(const Location& destination, bool should_move)
{
	Location* character_offset = calculate_character_offset(destination);
	m_graphic_representation_p->update(*character_offset, m_attributes_p->energy, should_move);

	if(should_move)
	{
		update_character_location(*character_offset);
		m_boundary_p->update_boundary(character_offset->x_position, character_offset->y_position);
	}
	delete character_offset;
}

Location* Enemy::calculate_character_offset(const Location& destination)
{
	Location* character_offset = new Location();

	if (m_location_p->x_position > destination.x_position)
	{
		character_offset->x_position -= m_attributes_p->moving_speed;
	}
	if (m_location_p->x_position < destination.x_position)
	{
		character_offset->x_position += m_attributes_p->moving_speed;
	}
	if (m_location_p->y_position > destination.y_position)
	{
		character_offset->y_position -= m_attributes_p->moving_speed;
	}
	if (m_location_p->y_position < destination.y_position)
	{
		character_offset->y_position += m_attributes_p->moving_speed;
	}

	return character_offset;
}

void Enemy::update_character_location(const Location& character_offset)
{
	m_location_p->x_position += character_offset.x_position;
	m_location_p->y_position += character_offset.y_position;
}

void Enemy::draw()
{
	m_graphic_representation_p->draw();
	draw_boundary_if_applicable(GameSettings::get_settings(GameSettings::Debug::DRAW_BOUNDARIES));
}

void Enemy::draw_boundary_if_applicable(bool is_draw_boundary_enabled)
{
	if(is_draw_boundary_enabled)
	{
		m_boundary_p->draw_boundary();
	}
}
