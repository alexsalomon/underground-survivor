#include "stdafx.h"
#include "WaveManager.h"
#include "Timer.h"
#include "GameFont.h"
#include "Location.h"
#include "Colour.h"
#include "TextControl.h"
#include"GameSettings.h"

WaveManager::WaveManager()
	: m_current_wave_number(0), m_num_of_enemy_spawning_locations(3), m_num_of_enemies_to_spawn(4)
{
	next_wave();
}

WaveManager::~WaveManager()
{
}

unsigned int WaveManager::get_current_wave_number()
{
	return m_current_wave_number;
}

unsigned int WaveManager::get_waiting_time_between_waves()
{
	return WAITING_TIME_BETWEEN_WAVES;
}

void WaveManager::next_wave()
{
	m_current_wave_number = m_current_wave_number+1;
	m_num_of_enemies_to_spawn += m_current_wave_number;
}

unsigned int WaveManager::get_num_of_enemy_spawning_locations()
{
	if(m_current_wave_number <= 2)
	{
		m_num_of_enemy_spawning_locations = 3;
	}
	else if(m_current_wave_number <= 5)
	{
		m_num_of_enemy_spawning_locations = 6;
	}
	else
	{
		m_num_of_enemy_spawning_locations = 10;
	}

	return m_num_of_enemy_spawning_locations;
}

unsigned int WaveManager::get_num_of_enemies_to_spawn()
{
	return m_num_of_enemies_to_spawn;
}

unsigned int WaveManager::get_blue_zombies_spawn_rate()
{
	unsigned int rate = BLUE_ZOMBIES_BASE_SPAWN_RATE;

	if(m_current_wave_number <= 2)
	{
		rate = 0;
	}

	return rate;
}
