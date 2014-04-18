#include "stdafx.h"
#include "Bullet.h"
#include "Location.h"
#include "GameSettings.h"
#include "AnimatedSprite.h"
#include "AnimationLoader.h"
#include "BoundaryManager.h"

Bullet::Bullet(Location* initial_location_p, Location* destination_p)
	: m_location_p(), m_bullet_offset(NULL), m_boundary_p(NULL) 
{
	m_animated_sprite_p = new AnimatedSprite();
	set_location(initial_location_p);
	int angle = calculate_angle(destination_p);
	load_animation_based_on_angle(angle);
	calculate_offset(destination_p);
	create_boundary();
}

Bullet::Bullet()
	: m_animated_sprite_p(NULL), m_location_p(NULL), m_bullet_offset(NULL), m_boundary_p(NULL) 
{
	Bullet(new Location(0,0), new Location(0,0));
}

Bullet::~Bullet()
{
	if(m_location_p){ delete m_location_p; }
	if(m_boundary_p){ delete m_boundary_p; }
	if(m_animated_sprite_p){ delete m_animated_sprite_p; }
	if(m_bullet_offset)	{ delete m_bullet_offset; }
}

Boundary* Bullet::get_boundary()
{
	return m_boundary_p;
}

void Bullet::set_location(Location* location_p)
{
	if(m_location_p)
	{
		delete m_location_p;
	}

	m_location_p = location_p;
	m_animated_sprite_p->set_position(m_location_p->x_position, m_location_p->y_position);
}

int Bullet::calculate_angle(Location* destination_p)
{	
	return 0;
}

void Bullet::load_animation_based_on_angle(int angle)
{
	//TODO: rotate the image using the angle, then load image:
	//HOW: screen resolution = 1280 x 768 (738 because of bar on top). Equation: rate = desired_width / window_width. x = 16 / 1280
	AnimationLoader animation_loader("images/ball.bmp", 2, 2, (int)(GameSettings::get_window_width()*0.0125), (int)(GameSettings::get_window_height()*0.0217));
	m_animated_sprite_p->add_animation("MovingBullet", animation_loader.get_animation(0, 1));
	m_animated_sprite_p->play_animation("MovingBullet");
}

void Bullet::calculate_offset(Location* destination_p)
{
	Location* bullet_offset = new Location();

	float direction_x = (float)(m_location_p->x_position - destination_p->x_position);
	float direction_y = (float)(m_location_p->y_position - destination_p->y_position);
	float vector_length = sqrt( direction_x*direction_x + direction_y*direction_y );
	bullet_offset->x_position = (int)(-1* ((direction_x / vector_length) * BULLET_MOVING_SPEED));
	bullet_offset->y_position = (int)(-1* ((direction_y / vector_length) * BULLET_MOVING_SPEED));

	m_bullet_offset = bullet_offset;
}

void Bullet::create_boundary()
{
	BoundaryManager* boundary_manager_p = BoundaryManager::get_instance();
	m_boundary_p = boundary_manager_p->choose_strategy(BOUNDING_BOX);
	m_boundary_p->create_boundary(Rectangle_int((m_location_p->y_position), (m_location_p->y_position + BOUNDARY_HEIGHT), (m_location_p->x_position), (m_location_p->x_position + BOUNDARY_WIDTH)));
}

void Bullet::update()
{
	update_location();
	m_boundary_p->update_boundary(m_bullet_offset->x_position, m_bullet_offset->y_position);
	m_animated_sprite_p->update_offset(m_bullet_offset->x_position, m_bullet_offset->y_position);
}

void Bullet::update_location()
{
	m_location_p->x_position += m_bullet_offset->x_position;
	m_location_p->y_position += m_bullet_offset->y_position;
}

void Bullet::draw()
{
	m_animated_sprite_p->draw_sprite();
	m_animated_sprite_p->next_frame();
	draw_boundary_if_applicable(GameSettings::get_settings(GameSettings::Debug::DRAW_BOUNDARIES));
}

void Bullet::draw_boundary_if_applicable(bool is_draw_boundary_enabled)
{
	if(is_draw_boundary_enabled)
	{
		m_boundary_p->draw_boundary();
	}
}

