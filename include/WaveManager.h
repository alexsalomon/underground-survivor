#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "Wave.h"

class Timer;
class GameFont;
class TextControl;

class WaveManager
{
	#define WAITING_TIME_BETWEEN_WAVES 5

	public:
		WaveManager();
		~WaveManager();

		void pause();
		void resume();
		bool change_waves_if_applicable(bool are_enemies_dead, bool force_new_wave = false);
		int get_current_wave_number();
		int get_num_of_enemy_spawning_locations();
		bool is_ready_to_change_waves();
		int get_waiting_time_between_waves();

	private:
		void next_wave();
		void update_wave_range(WaveRange range);
		void clean_wave_pointer();
		Location* get_screen_parameters();

		unsigned int m_current_wave_number;
		Wave* m_current_wave_p; 		
		Timer* m_wave_duration_timer_p;
};

#endif