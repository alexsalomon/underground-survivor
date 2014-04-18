#include "stdafx.h"
#include "WaveManager.h"
#include "Wave1to5.h"
#include "Wave6to10.h"
#include "ThirdWaveSettings.h"
#include "FourthWaveSettings.h"
#include "Timer.h"
#include "GameFont.h"
#include "Location.h"
#include "Colour.h"
#include "TextControl.h"
#include"GameSettings.h"

WaveManager::WaveManager()
	: m_current_wave_p(NULL), m_current_wave_number(0), m_wave_duration_timer_p(NULL)
{
	m_wave_duration_timer_p = new Timer();
	change_waves_if_applicable(true, true);
}

WaveManager::~WaveManager()
{
	clean_wave_pointer();
	if(m_wave_duration_timer_p){ delete m_wave_duration_timer_p; }
}

void WaveManager::pause()
{
	m_wave_duration_timer_p->pause();
}

void WaveManager::resume()
{
	m_wave_duration_timer_p->resume();
}

void WaveManager::clean_wave_pointer()
{
	if(m_current_wave_p){ delete m_current_wave_p; }
}

int WaveManager::get_current_wave_number()
{
	return m_current_wave_number;
}

int WaveManager::get_waiting_time_between_waves()
{
	return WAITING_TIME_BETWEEN_WAVES;
}

bool WaveManager::change_waves_if_applicable(bool are_enemies_dead, bool force_new_wave)
{
	bool changed_waves = false;

	if((m_wave_duration_timer_p->is_timeout() && are_enemies_dead) || force_new_wave)
	{
		next_wave();
		m_wave_duration_timer_p->start((WAITING_TIME_BETWEEN_WAVES + m_current_wave_p->get_wave_duration_time()));
		changed_waves = true;
	}
	
	return changed_waves;
}

void WaveManager::next_wave()
{
	WaveRange wave_range = DEFAULT_WAVE_SETTINGS;
	m_current_wave_number = m_current_wave_number+1;

	if(m_current_wave_p && m_current_wave_number > m_current_wave_p->get_last_wave_in_the_range())
	{
		wave_range = (WaveRange)(m_current_wave_p->get_wave_range() + 1);
		update_wave_range(wave_range);
	}
	else if(m_current_wave_p == NULL)
	{
		update_wave_range(wave_range);
	}
}

void WaveManager::update_wave_range(WaveRange range)
{
	clean_wave_pointer();

	switch(range)
	{
		case FIRST_WAVE_SETTINGS:
			m_current_wave_p = new Wave1to5();
			break;
		case SECOND_WAVE_SETTINGS:
			m_current_wave_p = new Wave6to10();
			break;
		case THIRD_WAVE_SETTINGS:
			m_current_wave_p = new ThirdWaveSettings();
			break;
		case FOURTH_WAVE_SETTINGS:
			m_current_wave_p = new FourthWaveSettings();
			break;
		default:
			m_current_wave_p = new Wave1to5();
			break;
	}
}

int WaveManager::get_num_of_enemy_spawning_locations()
{
	if(m_current_wave_p)
		return m_current_wave_p->get_num_of_enemy_spawning_locations();
	else
	{
		throw Exception("WaveManager::get_enemy_spawning_location() - m_current_state_p is NULL");
		return 0;
	}
}

bool WaveManager::is_ready_to_change_waves()
{
	return m_wave_duration_timer_p->is_timeout();
}
