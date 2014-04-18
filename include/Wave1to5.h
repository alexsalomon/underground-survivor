#ifndef WAVE_ONE_TO_FIVE_H
#define WAVE_ONE_TO_FIVE_H

#include "Wave.h"

class Wave1to5 : public Wave
{
	static const int FIRST_WAVE_IN_RANGE = 1;
	static const int LAST_WAVE_IN_RANGE = 2;
	static const int NUM_OF_SPAWNIG_LOCATIONS = 3;
	static const int WAVE_DURATION_TIME = 10;

	public:
		Wave1to5(){  }
		~Wave1to5(){  }

	private:
		WaveRange get_wave_range(){ return FIRST_WAVE_SETTINGS; }
		unsigned int get_last_wave_in_the_range(){ return LAST_WAVE_IN_RANGE; }	
		int get_wave_duration_time(){ return WAVE_DURATION_TIME; }
		int get_num_of_enemy_spawning_locations(){ return NUM_OF_SPAWNIG_LOCATIONS; }
};

#endif