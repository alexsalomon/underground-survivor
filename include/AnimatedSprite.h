#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "Image.h"
#include "ImageList.h"

class AnimatedSprite
{
	public:
		AnimatedSprite();
		~AnimatedSprite();

		void add_animation(const std::string& animation_name, const ImageList& animation);
		void play_animation(const std::string& animation_name);

		void draw_sprite();
		void next_frame();

		void set_position(int x_pos, int y_pos);
		void update_offset(int x_offset, int y_offset);

	private:
		typedef std::map<std::string, ImageList> AnimationMap;
		typedef AnimationMap::iterator AnimationMapIterator;

		AnimationMap m_animation_map;
		AnimationMapIterator m_animation_map_iter;

		int m_x_pos;
		int m_y_pos;
};

#endif