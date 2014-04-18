#ifndef GRAPHIC_REPRESENTATION_H
#define GRAPHIC_REPRESENTATION_H

#include "Renderable.h"
#include "AnimatedSprite.h"
#include "AnimationLoader.h"
#include "TextureManager.h"
#include "Location.h"
#include "Colour.h"

class Location;
class Colour;

class GraphicRepresentation : public Renderable
{
	public:
		GraphicRepresentation();
		virtual ~GraphicRepresentation();

		virtual void update(const Location& offset, unsigned int energy = 0, bool should_update_offset = true);
		virtual void draw();
		virtual void set_animation_position(Location* location_p);
		void set_current_action(std::string current_action);

	protected:
		virtual void initialize(int animation_width, int animation_height);
		virtual void load_animations() = 0;
		virtual void initialize_animation_defaults() = 0;
		virtual std::string get_texture_name() = 0;
		virtual Colour get_color_key() = 0;
		virtual void set_image_color_key();	
		virtual void determine_direction_based_on_offset(const Location& offset);

		AnimatedSprite* m_animated_sprite_p;
		std::string m_last_direction;
		std::string m_current_action;
		int m_animation_width;
		int m_animation_height;
};

#endif
