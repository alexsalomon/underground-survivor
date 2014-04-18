#ifndef PLAYER_GRAPHIC_REPRESENTATION_H
#define PLAYER_GRAPHIC_REPRESENTATION_H

#include "GraphicRepresentation.h"

class PlayerGraphicRepresentation : public GraphicRepresentation
{
	#define TEXTURE_PATH "images/little_girl_with_gun.bmp"
	#define NUMBER_OF_IMAGES_PER_ROW 4	
	#define NUMBER_OF_ROWS_IN_THE_TEXTURE 4	

	public:
		PlayerGraphicRepresentation();
		virtual ~PlayerGraphicRepresentation();

		std::string get_texture_name(){ return TEXTURE_PATH; }
		Colour get_color_key(){ return Colour(255, 255, 255); }

	private:
		void load_animations();	
		void load_standing_animations(AnimationLoader& animation_loader);
		void load_walking_animations(AnimationLoader& animation_loader);
		void load_attacking_animations(AnimationLoader& animation_loader);
		void load_receiving_damage_animations(AnimationLoader& animation_loader);
		void load_dying_animations(AnimationLoader& animation_loader);
		void initialize_animation_defaults();
};

#endif
