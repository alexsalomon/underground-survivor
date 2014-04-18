#include "stdafx.h"
#include "ZombieGraphicRepresentation.h"
#include "GameSettings.h"

ZombieGraphicRepresentation::ZombieGraphicRepresentation(int energy)
	: EnemyGraphicRepresentation(energy, (int)(GameSettings::get_window_width()*0.05), (int)(GameSettings::get_window_height()*0.083))
{
	int animation_width = (int)(GameSettings::get_window_width()*0.0375);		//skeleton = 0.05
	int animation_height = (int)(GameSettings::get_window_height()*0.083);
	initialize(animation_width, animation_height);
}

ZombieGraphicRepresentation::~ZombieGraphicRepresentation()
{
}

void ZombieGraphicRepresentation::load_animations()
{
	AnimationLoader animation_loader(TEXTURE_PATH, NUMBER_OF_IMAGES_PER_ROW, NUMBER_OF_ROWS_IN_THE_TEXTURE, m_animation_width, m_animation_height);
	load_standing_animations(animation_loader);
	load_walking_animations(animation_loader);
	load_attacking_animations(animation_loader);
	load_receiving_damage_animations(animation_loader);
	load_dying_animations(animation_loader);
}

void ZombieGraphicRepresentation::load_standing_animations(AnimationLoader& animation_loader)
{
	m_animated_sprite_p->add_animation("StandDown", animation_loader.get_animation(25, 25));			//(0, 0));
	m_animated_sprite_p->add_animation("StandLeft", animation_loader.get_animation(37, 37));			//(18, 18));
	m_animated_sprite_p->add_animation("StandUp", animation_loader.get_animation(1, 1));				//(36, 36));
	m_animated_sprite_p->add_animation("StandRight", animation_loader.get_animation(13, 13));			//(54, 54));
}

void ZombieGraphicRepresentation::load_walking_animations(AnimationLoader& animation_loader)
{
	m_animated_sprite_p->add_animation("WalkDown", animation_loader.get_animation(24, 26));				//(0, 6));	= Skeleton
	m_animated_sprite_p->add_animation("WalkLeft", animation_loader.get_animation(36, 38));				//(18, 24));
	m_animated_sprite_p->add_animation("WalkUp", animation_loader.get_animation(0, 2));					//(36, 42));
	m_animated_sprite_p->add_animation("WalkRight", animation_loader.get_animation(12, 14));			//(54, 60));
}

void ZombieGraphicRepresentation::load_attacking_animations(AnimationLoader& animation_loader)
{
	m_animated_sprite_p->add_animation("AttackDown", animation_loader.get_animation(25, 25));			//(0, 0));
	m_animated_sprite_p->add_animation("AttackLeft", animation_loader.get_animation(37, 37));			//(18, 18));
	m_animated_sprite_p->add_animation("AttackUp", animation_loader.get_animation(1, 1));				//(36, 36));
	m_animated_sprite_p->add_animation("AttackRight", animation_loader.get_animation(13, 13));

	//m_animated_sprite_p->add_animation("AttackDown", animation_loader.get_animation(9, 15));
	//m_animated_sprite_p->add_animation("AttackLeft", animation_loader.get_animation(27, 33));
	//m_animated_sprite_p->add_animation("AttackUp", animation_loader.get_animation(45, 51));
	//m_animated_sprite_p->add_animation("AttackRight", animation_loader.get_animation(63, 69));
}

void ZombieGraphicRepresentation::load_receiving_damage_animations(AnimationLoader& animation_loader)
{
	//m_animated_sprite_p->add_animation("DamagedDown", animation_loader.get_animation(0, 0));
	//m_animated_sprite_p->add_animation("DamagedLeft", animation_loader.get_animation(18, 18));
	//m_animated_sprite_p->add_animation("DamagedUp", animation_loader.get_animation(36, 36));
	//m_animated_sprite_p->add_animation("DamagedRight", animation_loader.get_animation(54, 54));
}

void ZombieGraphicRepresentation::load_dying_animations(AnimationLoader& animation_loader)
{
	//m_animated_sprite_p->add_animation("DeadDown", animation_loader.get_animation(8, 8));
	//m_animated_sprite_p->add_animation("DeadLeft", animation_loader.get_animation(8, 8));
	//m_animated_sprite_p->add_animation("DeadUp", animation_loader.get_animation(8, 8));
	//m_animated_sprite_p->add_animation("DeadRight", animation_loader.get_animation(8, 8));
}

void ZombieGraphicRepresentation::initialize_animation_defaults()
{	
	m_current_action = "Walk";
	m_last_direction = "Down";
	m_animated_sprite_p->play_animation(m_current_action + m_last_direction);
}
