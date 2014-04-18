#include "stdafx.h"
#include "GraphicRepresentation.h"

GraphicRepresentation::GraphicRepresentation()
{
	m_animated_sprite_p = new AnimatedSprite();
}

void GraphicRepresentation::initialize(int animation_width, int animation_height)
{
	m_animation_width = animation_width;
	m_animation_height = animation_height;
	load_animations();
	set_image_color_key();
	initialize_animation_defaults();
}

GraphicRepresentation::~GraphicRepresentation()
{
	if(m_animated_sprite_p){ delete m_animated_sprite_p; }
}

void GraphicRepresentation::set_image_color_key()
{
	TextureManager* texture_manager_p = TextureManager::get_instance();
	texture_manager_p->get_texture(get_texture_name())->set_color_key(get_color_key());	//Change the error message here!
}

void GraphicRepresentation::set_animation_position(Location* location_p)
{
	m_animated_sprite_p->set_position(location_p->x_position, location_p->y_position);
}

void GraphicRepresentation::set_current_action(std::string current_action)
{
	m_current_action = current_action;
}

void GraphicRepresentation::update(const Location& offset, unsigned int energy, bool should_update_offset)
{
	determine_direction_based_on_offset(offset);
	m_animated_sprite_p->play_animation(m_current_action + m_last_direction);
	if(should_update_offset){ m_animated_sprite_p->update_offset(offset.x_position, offset.y_position); }
}

void GraphicRepresentation::determine_direction_based_on_offset(const Location& offset)
{
	if(!offset.is_zero())
	{
		std::string horizontal_direction = "";
		std::string vertical_direction = "";

		if(offset.y_position < 0)
		{
			vertical_direction = "Up";
		}
		else if(offset.y_position > 0)
		{
			vertical_direction = "Down";
		}

		/*REMOVE THE ELSE IN ORDER TO ALLOW ANIMATION FOR DIAGONAL DIRECTIONS*/
		else if(offset.x_position < 0)
		{
			horizontal_direction = "Left";
		}
		else if(offset.x_position > 0)
		{
			horizontal_direction = "Right";
		}

		m_last_direction = vertical_direction + horizontal_direction;
	}
}

void GraphicRepresentation::draw()
{
	m_animated_sprite_p->draw_sprite();
	m_animated_sprite_p->next_frame();
}
