#ifndef ZOMBIE_GRAPHIC_REPRESENTATION_H
#define ZOMBIE_GRAPHIC_REPRESENTATION_H

#include "EnemyGraphicRepresentation.h"

class ZombieGraphicRepresentation : public EnemyGraphicRepresentation
{
	#define TEXTURE_PATH "images/zombies_correct.bmp"
	#define NUMBER_OF_IMAGES_PER_ROW 12
	#define NUMBER_OF_ROWS_IN_THE_TEXTURE 8	

	public:
		ZombieGraphicRepresentation(int energy);
		virtual ~ZombieGraphicRepresentation();

		std::string get_texture_name(){ return TEXTURE_PATH; }
		Colour get_color_key(){ return Colour(51, 128, 0); }

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
