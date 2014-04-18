#ifndef FOURTH_WAVE_SETTINGS_H
#define FOURTH_WAVE_SETTINGS_H

#include "Wave.h"

class FourthWaveSettings : public Wave
{
	static const int FIRST_WAVE_IN_RANGE = 16;
	static const int LAST_WAVE_IN_RANGE = 30;
	static const int NUM_OF_SPAWNIG_LOCATIONS = 10;
	static const int WAVE_DURATION_TIME = 70;

	public:
		FourthWaveSettings(){  }
		~FourthWaveSettings(){  }

	private:
		WaveRange get_wave_range(){ return FOURTH_WAVE_SETTINGS; }
		unsigned int get_last_wave_in_the_range(){ return LAST_WAVE_IN_RANGE; }	
		int get_wave_duration_time(){ return WAVE_DURATION_TIME; }
		int get_num_of_enemy_spawning_locations(){ return NUM_OF_SPAWNIG_LOCATIONS; }
};

#endif