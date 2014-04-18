#include "stdafx.h"
#include "Image.h"
#include "ImageList.h"
#include "AnimatedSprite.h"
#include "Location.h"

AnimatedSprite::AnimatedSprite()
	: m_x_pos(0), m_y_pos(0)
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::add_animation(const std::string& animation_name, const ImageList& animation)
{
	m_animation_map[animation_name] = animation;
}

void AnimatedSprite::play_animation(const std::string& animation_name)
{
	m_animation_map_iter = m_animation_map.find(animation_name);

	if (m_animation_map_iter == m_animation_map.end())
	{
		std::string error_message = "Unable to play: " + animation_name;
		error_message += ". Animation not found.";
		throw Exception(error_message);
	}
}

void AnimatedSprite::draw_sprite()
{
	if (m_animation_map_iter != m_animation_map.end())
	{
		Image_ptr image_p = m_animation_map_iter->second.get_current_image();
		image_p->draw_image(Location(m_x_pos, m_y_pos));
	}
}

void AnimatedSprite::next_frame()
{
	if (m_animation_map_iter != m_animation_map.end())
	{
		m_animation_map_iter->second.go_to_next_image();
	}
}

void AnimatedSprite::set_position(int x_pos, int y_pos) 
{
	m_x_pos = x_pos;
	m_y_pos = y_pos;
}

void AnimatedSprite::update_offset(int x_offset, int y_offset) 
{
	m_x_pos += x_offset;
	m_y_pos += y_offset;
}
