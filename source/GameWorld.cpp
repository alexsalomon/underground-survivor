#include "stdafx.h"
#include "GameWorld.h"
#include "PlayState.h"
#include "MainPlayerStatusPanel.h"
#include "GameSettings.h"
#include "CollisionDetector.h"
#include "WaveManager.h"
#include "TextControl.h"
#include "GameFont.h"
#include "Background.h"
#include "Player.h"
#include "ZombiePurple.h"
#include "ZombieBlue.h"
#include "Bullet.h"
#include "Timer.h"
#include "Location.h"
#include "Colour.h"

GameWorld::GameWorld(PlayState* play_state_p, Panel* main_panel_p)
	: m_play_state_p(play_state_p), m_main_panel_p(main_panel_p), m_enemy_list(), m_bullet_list(), m_font(NULL), m_text_control_p(NULL), m_bullet_destination_p(NULL), m_should_bullet_be_fired(false), m_draw_new_wave_text(false), m_current_num_of_enemies_to_spawn(1)
{
	m_background_p = new Background();
	m_player_1_p = new Player();
	m_bullet_destination_p = new Location();

	m_spawn_enemy_timer_p = new Timer();
	m_between_waves_timer_p = new Timer();
	m_wave_settings_manager_p = new WaveManager();

	initialize_world();
}

GameWorld::~GameWorld()
{
	destroy_bullets();
	destroy_enemies();
	if(m_wave_settings_manager_p){ delete m_wave_settings_manager_p; }
	if(m_between_waves_timer_p){ delete m_between_waves_timer_p; }
	if(m_spawn_enemy_timer_p){ delete m_spawn_enemy_timer_p; }
	if(m_bullet_destination_p){ delete m_bullet_destination_p; }
	if(m_player_1_p){ delete m_player_1_p; }
	if(m_background_p){ delete m_background_p; }

	RemoveFontResource("fonts/zombified.ttf");
}

void GameWorld::destroy_bullets()
{
	for(BulletListIterator iter = m_bullet_list.begin(); iter != m_bullet_list.end(); iter++)
	{
		delete *iter;
	}
}

void GameWorld::destroy_enemies()
{
	for(EnemyListIterator iter = m_enemy_list.begin(); iter != m_enemy_list.end(); iter++)
	{
		delete *iter;
	}
}

void GameWorld::initialize_world()
{
	m_current_state = START_WAVE;
	set_up_wave_text_control();
}

void GameWorld::set_up_wave_text_control()
{
	m_font = new GameFont();
	AddFontResource("fonts/zombified.ttf");
	m_font->create_font("zombified", 170, FW_NORMAL);
	m_text_control_p = new TextControl(m_font, Rectangle_int(0, (int)(GameSettings::get_window_height()*0.60), 0, GameSettings::get_window_width()));
	m_text_control_p->set_alignement(TextControl::Center);
	m_text_control_p->set_text_colour(new Colour(0, 0, 0));
}

void GameWorld::pause()
{
	m_spawn_enemy_timer_p->pause();
	m_between_waves_timer_p->pause();
}

void GameWorld::resume()
{
	m_spawn_enemy_timer_p->resume();
	m_between_waves_timer_p->resume();
}

void GameWorld::on_keyup(WPARAM w_param)
{
	switch (w_param)
	{
		case VK_UP:
			m_player_1_p->on_keyup(KEY_UP);
			break;
		case VK_DOWN:
			m_player_1_p->on_keyup(KEY_DOWN);
			break;
		case VK_LEFT:
			m_player_1_p->on_keyup(KEY_LEFT);
			break;
		case VK_RIGHT:
			m_player_1_p->on_keyup(KEY_RIGHT);
			break;
	}
}

void GameWorld::on_keydown(WPARAM w_param)
{
	switch (w_param)
	{
		case VK_UP:
			m_player_1_p->on_keydown(KEY_UP);
			break;
		case VK_DOWN:
			m_player_1_p->on_keydown(KEY_DOWN);
			break;
		case VK_LEFT:
			m_player_1_p->on_keydown(KEY_LEFT);
			break;
		case VK_RIGHT:
			m_player_1_p->on_keydown(KEY_RIGHT);
			break;
	}
}

void GameWorld::set_should_bullet_be_fired(bool fire_bullet)
{
	m_should_bullet_be_fired = fire_bullet;
}

void GameWorld::set_bullet_destination(const Location& bullet_destination)
{
	m_bullet_destination_p->x_position = bullet_destination.x_position;
	m_bullet_destination_p->y_position = bullet_destination.y_position;
}

void GameWorld::update()
{
	m_player_1_p->update(m_background_p);
	update_bullets();
	update_enemies();
	create_bullets_if_applicable();

	switch(m_current_state)
	{
		case START_WAVE:
			m_between_waves_timer_p->start(m_wave_settings_manager_p->get_waiting_time_between_waves());
			m_current_num_of_enemies_to_spawn = m_wave_settings_manager_p->get_num_of_enemies_to_spawn();
			m_current_state = DISPLAY_WAVE_NUMBER_TO_SCREEN;
			break;

		case DISPLAY_WAVE_NUMBER_TO_SCREEN:
			m_draw_new_wave_text = true;
			if(m_between_waves_timer_p->is_timeout())
			{
				m_draw_new_wave_text = false;
				m_current_state = SPAWN_ENEMY; 
			}
			break;

		case SPAWN_ENEMY:
			spawn_enemy();
			m_spawn_enemy_timer_p->start(WAITING_TIME_BETWEEN_ENEMY_SPAWN);
			m_current_state = WAIT_TO_SPAWN_NEXT_ENEMY;
			break;

		case WAIT_TO_SPAWN_NEXT_ENEMY:
			if(m_spawn_enemy_timer_p->is_timeout() && m_current_num_of_enemies_to_spawn > 0)
			{
				m_current_state = SPAWN_ENEMY;
			}
			else if(m_current_num_of_enemies_to_spawn == 0 && m_enemy_list.empty())
			{
				m_wave_settings_manager_p->next_wave();
				m_current_state = START_WAVE;
			}
			break;

		default:
			throw Exception("GameWorld::update - Invalid state");
	}
}

void GameWorld::spawn_enemy()
{
	Enemy* enemy_p = get_enemy_type();
	Location* spawning_location = get_random_enemy_spawning_location();
	enemy_p->set_location(spawning_location);
	m_enemy_list.push_back(enemy_p);
	m_current_num_of_enemies_to_spawn--;
}

Enemy* GameWorld::get_enemy_type()
{
	Enemy* enemy_p = NULL;

	if(rand() % 100 < (int)m_wave_settings_manager_p->get_blue_zombies_spawn_rate())
	{
		 enemy_p = new ZombieBlue();
	}
	else
	{
		 enemy_p = new ZombiePurple();
	}

	return enemy_p;
}

Location* GameWorld::get_random_enemy_spawning_location()
{
	try
	{
		Location* random_location = NULL;
		int range = m_wave_settings_manager_p->get_num_of_enemy_spawning_locations();
		int index = get_random_index_inside_range(range);
		random_location = m_background_p->get_enemy_spawning_location(index);

		return random_location;
	}
	catch(...)
	{
		throw "Exception inside function PlayState::get_random_enemy_spawning_location()";
	}
}

int GameWorld::get_random_index_inside_range(int range)
{
	return rand() % range;
}

void GameWorld::create_bullets_if_applicable()
{
	if(m_should_bullet_be_fired)
	{
		Bullet* bullet_p = m_player_1_p->shoot(m_bullet_destination_p->x_position, m_bullet_destination_p->y_position);

		if(bullet_p)
		{
			m_bullet_list.push_back(bullet_p);
		}
	}
}

void GameWorld::update_bullets()
{
	clean_up_bullet_if_applicable();
	deal_with_hit_enemies_if_applicable();
	update_flying_bullets();
}

void GameWorld::clean_up_bullet_if_applicable()
{
	BulletListIterator bullet_iter = m_bullet_list.begin();

	while(bullet_iter != m_bullet_list.end())
	{
		if(CollisionDetector::collide(m_background_p, *bullet_iter))
		{
			bullet_iter = m_bullet_list.erase(bullet_iter);
		}
		else
		{
			++bullet_iter;
		}
	}
}

void GameWorld::deal_with_hit_enemies_if_applicable()
{
	bool was_bullet_delete = false;
	BulletListIterator bullet_iter = m_bullet_list.begin();

	while(bullet_iter != m_bullet_list.end())
	{
		EnemyListIterator enemy_iter = m_enemy_list.begin();
		while(enemy_iter != m_enemy_list.end() && !was_bullet_delete)
		{
			if(CollisionDetector::collide(*bullet_iter, *enemy_iter))
			{
				bullet_iter = m_bullet_list.erase(bullet_iter);
				was_bullet_delete = true;
				unsigned int damage = m_player_1_p->get_total_inflicted_damage();
				bool is_enemy_dead = (*enemy_iter)->take_damage(damage);
				if(is_enemy_dead)
				{
					enemy_iter = m_enemy_list.erase(enemy_iter);
				}
			}
			else
			{
				++enemy_iter;
			}
		}

		if(bullet_iter != m_bullet_list.end())
		{
			++bullet_iter;
		}
	}
}

void GameWorld::update_flying_bullets()
{
	for(BulletListIterator iter = m_bullet_list.begin(); iter != m_bullet_list.end(); iter++)
	{
		(*iter)->update();
	}
}

void GameWorld::update_enemies()
{
	bool should_move = true;

	for(EnemyListIterator iter = m_enemy_list.begin(); iter != m_enemy_list.end(); iter++)
	{
		if(CollisionDetector::collide(m_player_1_p, *iter))
		{
			should_move = false;
			unsigned int damage = (*iter)->attack();
			m_play_state_p->set_game_over(m_player_1_p->take_damage(damage));
			m_main_panel_p->update(damage); // TODO: That is not the actual damage, need to include calculations using the defense
		}
		else
		{
			should_move = true;
			(*iter)->walk();
		}

		(*iter)->update( *(m_player_1_p->get_location()), should_move );
	}
}

void GameWorld::draw()
{
	m_background_p->draw();
	draw_bullets();
	m_player_1_p->draw();
	draw_enemies();
	draw_new_wave_text_if_applicable();
}

void GameWorld::draw_bullets()
{
	for(BulletListIterator iter = m_bullet_list.begin(); iter != m_bullet_list.end(); iter++)
	{
		(*iter)->draw();
	}
}

void GameWorld::draw_enemies()
{
	for(EnemyListIterator iter = m_enemy_list.begin(); iter != m_enemy_list.end(); iter++)
	{
		(*iter)->draw();
	}
}

void GameWorld::draw_new_wave_text_if_applicable()
{
	if(m_draw_new_wave_text)
	{
		std::stringstream wave_text_stream;
		wave_text_stream << "Wave " << m_wave_settings_manager_p->get_current_wave_number();
		m_text_control_p->set_text(wave_text_stream.str());
		m_text_control_p->draw();
	}
}
