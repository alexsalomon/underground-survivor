#include "stdafx.h"
#include "GameSettings.h"
#include "Location.h"
#include "Image.h"
#include "BoundaryManager.h"
#include "Background.h"

Background::Background()
{
	m_background_image_p = Image::create_image("images/3d_backround_1.jpg", GameSettings::get_window_width(), GameSettings::get_window_height());

	BoundaryManager* boundary_manager_p = BoundaryManager::get_instance();
	m_boundary_p = boundary_manager_p->choose_strategy(INVERTED_BOUNDING_BOX);

	int top = (int)(GameSettings::get_window_height()*0.213);
	int bottom = (int)(GameSettings::get_window_height()*0.879);
	int left = (int)(GameSettings::get_window_width()*0.104);
	int right = (int)(GameSettings::get_window_width()*0.876);

	m_boundary_p->create_boundary(Rectangle_int(top, bottom, left, right));
	initialize_enemy_spawning_locations();
}

Background::~Background()
{
	if(m_background_image_p){ delete m_background_image_p; }
	if(m_boundary_p){ delete m_boundary_p; }
	m_enemy_spawning_locations.clear();

}

Boundary* Background::get_boundary()
{
	return m_boundary_p;
}

void Background::initialize_enemy_spawning_locations()
{
	//Upper tunnels:
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.242), (int)(GameSettings::get_window_height()*0.136)));
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.48), (int)(GameSettings::get_window_height()*0.136)));
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.714), (int)(GameSettings::get_window_height()*0.136)));

	//Lower tunnels:
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.242), (int)(GameSettings::get_window_height()*0.889)));
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.48), (int)(GameSettings::get_window_height()*0.889)));
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.714), (int)(GameSettings::get_window_height()*0.889)));

	//left tunnels:
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.066), (int)(GameSettings::get_window_height()*0.325)));
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.066), (int)(GameSettings::get_window_height()*0.725)));

	//left tunnels:
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.895), (int)(GameSettings::get_window_height()*0.325)));
	m_enemy_spawning_locations.push_back(new Location((int)(GameSettings::get_window_width()*0.895), (int)(GameSettings::get_window_height()*0.725)));
}

Location* Background::get_enemy_spawning_location(int index)
{
	Location* spawning_location_p = NULL;

	if(m_enemy_spawning_locations.size() > (unsigned int)index)
	{
		Location* enemy_location_p = m_enemy_spawning_locations[index];
		spawning_location_p = new Location(enemy_location_p->x_position, enemy_location_p->y_position);
	}

	return spawning_location_p;
}

void Background::update()
{
}

void Background::draw()
{
	m_background_image_p->draw_image(Location(0, 0));
	draw_boundary_if_applicable(GameSettings::get_settings(GameSettings::Debug::DRAW_BOUNDARIES));
}

void Background::draw_boundary_if_applicable(bool is_draw_boundary_enabled)
{
	if(is_draw_boundary_enabled)
	{
		m_boundary_p->draw_boundary();
	}
}