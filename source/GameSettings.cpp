#include "stdafx.h"
#include "GameSettings.h"

const std::string GameSettings::Debug::DRAW_BOUNDARIES = "draw_boundaries";
const std::string GameSettings::Debug::DRAW_PANELS = "draw_panels";
const std::string GameSettings::Debug::DRAW_ENERGY_BARS = "draw_energy_bars";
const std::string GameSettings::SystemOptions::IS_FULL_SCREEN = "is_full_screen";

GameSettings::SettingsMap GameSettings::m_settings;
int GameSettings::m_window_width;
int GameSettings::m_window_height;

void GameSettings::set_settings(std::string key, bool value)
{
	MapIterator iter = m_settings.find(key);
	if(iter != m_settings.end())
	{		
		iter->second = value;
	}
	else
	{
		m_settings.insert(std::make_pair(key, value));
	}
}

bool GameSettings::get_settings(std::string key)
{
	MapIterator iter = m_settings.find(key);
	if(iter != m_settings.end())
	{	
		return iter->second;
	}
	else
	{
		throw "Undefined setting";
		return false;
	}
}

void GameSettings::toggle_settings(std::string key, bool default_value)
{
	MapIterator iter = m_settings.find(key);
	if(iter != m_settings.end())
	{	
		bool current_settings = get_settings(key);
		set_settings(key, !current_settings);
	}
	else
	{
		set_settings(key, default_value);
	}
}

int GameSettings::get_window_width()
{
	return m_window_width;
}

void GameSettings::set_window_width(int window_width)
{
	m_window_width = window_width;
}

int GameSettings::get_window_height()
{
	return m_window_height;
}

void GameSettings::set_window_height(int window_height)
{
	m_window_height = window_height;
}
