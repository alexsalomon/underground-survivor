#ifndef GAME_WORLD_H
#define GAME_WORLD_H

class PlayState;
class Panel;
class GameFont;
class TextControl;
class Background;
class Player;
class Enemy;
class Bullet;
class WaveManager;
class Timer;
class Location;
class Colour;

class GameWorld
{
	#define WAITING_TIME_BETWEEN_ENEMY_SPAWN 1

	typedef std::list<Location*>::iterator LocationList;
	typedef std::list<Enemy*>::iterator EnemyListIterator;
	typedef std::list<Bullet*>::iterator BulletListIterator;

	typedef enum State
	{
		INVALID_STATE = -1,
		START_WAVE,
		DISPLAY_WAVE_NUMBER_TO_SCREEN,
		SPAWN_ENEMY,
		WAIT_TO_SPAWN_NEXT_ENEMY
	}State;

	public:
		GameWorld(PlayState* play_state_p, Panel* main_panel_p);
		~GameWorld();

		void pause();
		void resume();
		void on_keyup(WPARAM w_param);
		void on_keydown(WPARAM w_param);
		void set_should_bullet_be_fired(bool fire_bullet);
		void set_bullet_destination(const Location& bullet_destination);
		void update();
		void draw();

	private:
		void initialize_world();
		void set_up_wave_text_control();
		void create_bullets_if_applicable();
		void update_bullets();
		void clean_up_bullet_if_applicable();
		void update_flying_bullets();
		void deal_with_hit_enemies_if_applicable();
		void update_enemies();
		void spawn_enemy();
		Location* get_random_enemy_spawning_location();
		int get_random_index_inside_range(int range);
		void draw_bullets();
		void draw_enemies();
		void draw_new_wave_text_if_applicable();
		void destroy_bullets();
		void destroy_enemies();

		PlayState* m_play_state_p;
		Panel* m_main_panel_p;
		std::list<Enemy*> m_enemy_list;
		std::list<Bullet*> m_bullet_list;
		Background* m_background_p;
		Player* m_player_1_p;
		WaveManager* m_wave_settings_manager_p;
		Timer* m_spawn_enemy_timer_p;
		Timer* m_between_waves_timer_p;
		GameFont* m_font;
		TextControl* m_text_control_p;
		
		Location* m_bullet_destination_p;
		State m_current_state;
		bool m_should_bullet_be_fired;
		bool m_draw_new_wave_text;
		int m_current_num_of_enemies_to_spawn;
};

#endif