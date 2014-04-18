#include "stdafx.h"
#include "Player.h"
#include "PlayerGraphicRepresentation.h"
#include "Attributes.h"
#include "GameSettings.h"
#include "CollisionDetector.h"
#include "BoundaryManager.h"
#include "Bullet.h"
#include "Pistol.h"
#include "BulletFactory.h"
#include "Background.h"

Player::Player()
{
	m_location_p = new Location((int)(GameSettings::get_window_width()/2), (int)(GameSettings::get_window_height()*0.662));
	m_graphic_representation_p = new PlayerGraphicRepresentation();	
	m_graphic_representation_p->set_animation_position(m_location_p);
	m_attributes_p = new Attributes(INITIAL_ENERGY, INITIAL_RESISTENCY, INITIAL_ATTACK_POWER, INITIAL_MOVING_SPEED, INITIAL_ATTACK_SPEED);
	m_weapon_p = new Pistol();

	initialize_pressed_keys_array_to_false();
	create_boundary();
	move_location_to_center_of_image();
}

Player::~Player()
{
	if(m_weapon_p){	delete m_weapon_p; }
}

void Player::initialize_pressed_keys_array_to_false()
{
	for(int i = 0; i < NUMBER_OF_DIRECTION_KEYS; i++)
	{
		m_keys_down[i] = false;
	}
}

void Player::create_boundary()
{
	BoundaryManager* boundary_manager_p = BoundaryManager::get_instance();
	m_boundary_p = boundary_manager_p->choose_strategy(BOUNDING_BOX);

	int top = m_location_p->y_position + (int)(GameSettings::get_window_height()*0.015);
	int bottom = m_location_p->y_position + (int)(GameSettings::get_window_height()*0.07);
	int left = m_location_p->x_position + (int)(GameSettings::get_window_width()*0.022);
	int right = m_location_p->x_position + (int)(GameSettings::get_window_width()*0.04);

	m_boundary_p->create_boundary(Rectangle_int(top, bottom, left, right));
}

void Player::move_location_to_center_of_image()
{
	Rectangle_int* boundary = m_boundary_p->get_rectangle();	
	m_location_p->x_position += (boundary->right - boundary->left);
	m_location_p->y_position += (boundary->bottom - boundary->top) / 2;
}

Bullet* Player::shoot(WPARAM x_coordinate, WPARAM y_coordinate)
{
	Bullet* bullet_p = NULL;

	if(m_weapon_p->is_ready_to_fire())
	{		
		Location* initial_position_p = new Location(m_location_p->x_position, m_location_p->y_position);
		Location* destination_p = new Location(x_coordinate, y_coordinate);
		bullet_p = BulletFactory::create_piece(m_weapon_p->get_bullet_type(), initial_position_p, destination_p);
		m_weapon_p->fire();
	}

	return bullet_p;
}

unsigned int Player::get_total_inflicted_damage()
{
	return m_attributes_p->attack_power + m_weapon_p->get_damage();
}

void Player::on_keydown(KEY key)
{
	m_keys_down[key] = true;
	was_any_key_pressed() ? walk() : stand();
}

void Player::on_keyup(KEY key)
{
	m_keys_down[key] = false;
	was_any_key_pressed() ? walk() : stand();
}

void Player::update(Background* background_p)
{
	Location* character_offset = calculate_character_offset();
	m_boundary_p->update_boundary(character_offset->x_position, character_offset->y_position);

	if(!CollisionDetector::collide(background_p, this))
	{
		update_character_location(*character_offset);
		m_graphic_representation_p->update(*character_offset);
	}
	else
	{
		m_boundary_p->update_boundary( (-1)*character_offset->x_position, (-1)*character_offset->y_position );
	}

	delete character_offset;
}

Location* Player::calculate_character_offset()
{
	Location* character_offset = new Location();
	int horizontal_offset = 0;
	int vertical_offset = 0;

	if (m_keys_down[KEY_UP])
	{
		vertical_offset -= m_attributes_p->moving_speed;
	}
	if (m_keys_down[KEY_DOWN])
	{
		vertical_offset += m_attributes_p->moving_speed;
	}
	if (m_keys_down[KEY_LEFT])
	{
		horizontal_offset -= m_attributes_p->moving_speed;
	}
	if (m_keys_down[KEY_RIGHT])
	{
		horizontal_offset += m_attributes_p->moving_speed;
	}

	character_offset->x_position = horizontal_offset;
	character_offset->y_position = vertical_offset;

	return character_offset;
}

void Player::update_character_location(const Location& character_offset)
{
	m_location_p->x_position += character_offset.x_position;
	m_location_p->y_position += character_offset.y_position;
}

bool Player::was_any_key_pressed() const
{
	bool was_pressed = false;
	int index = 0;

	while(was_pressed == false && index < NUMBER_OF_DIRECTION_KEYS)
	{
		if (m_keys_down[index])
		{
			was_pressed = true;
		}
		index++;
	}

	return was_pressed;
}

void Player::draw()
{
	m_graphic_representation_p->draw();
	draw_boundary_if_applicable(GameSettings::get_settings(GameSettings::Debug::DRAW_BOUNDARIES));

	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
		glVertex3i(m_location_p->x_position, m_location_p->y_position, 0);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}

void Player::draw_boundary_if_applicable(bool is_draw_boundary_enabled)
{
	if(is_draw_boundary_enabled)
	{
		m_boundary_p->draw_boundary();
	}
}
