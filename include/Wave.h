#ifndef WAVE_H
#define WAVE_H

class Location;
class Timer;

typedef enum WaveRange
{
	DEFAULT_WAVE_SETTINGS = -1,
	FIRST_WAVE_SETTINGS = 0,
	SECOND_WAVE_SETTINGS = 1,
	THIRD_WAVE_SETTINGS = 2,
	FOURTH_WAVE_SETTINGS = 3
};

class Wave
{
	friend class WaveManager;

	public:
		virtual ~Wave(){  };

	protected:
		virtual WaveRange get_wave_range() = 0;
		virtual unsigned int get_last_wave_in_the_range() = 0;
		virtual int get_num_of_enemy_spawning_locations() = 0;	
		virtual int get_wave_duration_time() = 0;

	private:
			
};

#endif