#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

class Timer;
class GameFont;
class TextControl;

class WaveManager
{
	#define WAITING_TIME_BETWEEN_WAVES 5

	public:
		WaveManager();
		~WaveManager();

		void next_wave();
		int get_current_wave_number();
		int get_waiting_time_between_waves();
		int get_num_of_enemy_spawning_locations();
		int get_num_of_enemies_to_spawn();

	private:
		unsigned int m_current_wave_number;
		unsigned int m_num_of_enemy_spawning_locations;
		unsigned int m_num_of_enemies_to_spawn;
};

#endif