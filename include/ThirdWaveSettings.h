#ifndef THIRD_WAVE_SETTINGS_H
#define THIRD_WAVE_SETTINGS_H

#include "Wave.h"

class ThirdWaveSettings : public Wave
{
	static const int FIRST_WAVE_IN_RANGE = 8;
	static const int LAST_WAVE_IN_RANGE = 15;
	static const int NUM_OF_SPAWNIG_LOCATIONS = 10;
	static const int WAVE_DURATION_TIME = 50;

	public:
		ThirdWaveSettings(){  }
		~ThirdWaveSettings(){  }

	private:
		WaveRange get_wave_range(){ return THIRD_WAVE_SETTINGS; }
		unsigned int get_last_wave_in_the_range(){ return LAST_WAVE_IN_RANGE; }	
		int get_wave_duration_time(){ return WAVE_DURATION_TIME; }
		int get_num_of_enemy_spawning_locations(){ return NUM_OF_SPAWNIG_LOCATIONS; }
};

#endif