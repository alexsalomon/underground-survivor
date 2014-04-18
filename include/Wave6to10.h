#ifndef WAVE_SIX_TO_TEN_H
#define WAVE_SIX_TO_TEN_H

#include "Wave.h"

class Wave6to10 : public Wave
{
	static const int FIRST_WAVE_IN_RANGE = 3;
	static const int LAST_WAVE_IN_RANGE = 7;
	static const int NUM_OF_SPAWNIG_LOCATIONS = 6;
	static const int WAVE_DURATION_TIME = 25;

	public:
		Wave6to10(){  }
		~Wave6to10(){  }

	private:
		WaveRange get_wave_range(){ return SECOND_WAVE_SETTINGS; }
		unsigned int get_last_wave_in_the_range(){ return LAST_WAVE_IN_RANGE; }
		int get_wave_duration_time(){ return WAVE_DURATION_TIME; }
		int get_num_of_enemy_spawning_locations(){ return NUM_OF_SPAWNIG_LOCATIONS; }		
};

#endif