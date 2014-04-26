#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

class Timer;
class GameFont;
class TextControl;

class WaveManager
{
	#define WAITING_TIME_BETWEEN_WAVES 5
	#define BLUE_ZOMBIES_BASE_SPAWN_RATE 20
	#define GRUNT_PURPLE_ZOMBIES_BASE_SPAWN_RATE 8

	public:
		WaveManager();
		~WaveManager();

		void next_wave();
		unsigned int get_current_wave_number();
		unsigned int get_waiting_time_between_waves();
		unsigned int get_num_of_enemy_spawning_locations();
		unsigned int get_num_of_enemies_to_spawn();
		unsigned int get_blue_zombies_spawn_rate();
		unsigned int get_grunt_purple_zombies_spawn_rate();

	private:
		unsigned int m_current_wave_number;
		unsigned int m_num_of_enemy_spawning_locations;
		unsigned int m_num_of_enemies_to_spawn;
};

#endif