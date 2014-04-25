#include "stdafx.h"
#include "PlayState.h"
#include "MenuState.h"
#include "GameWorld.h"
#include "GameSettings.h"
#include "MainPlayerStatusPanel.h"
#include "TextControl.h"
#include "GameFont.h"
#include "Colour.h"
#include "Location.h"

PlayState* PlayState::m_play_state_p = NULL;

PlayState* PlayState::get_instance(StateManager* state_manager_p)
{
	if(m_play_state_p == NULL)
		m_play_state_p = new PlayState(state_manager_p);

	return m_play_state_p;
}

PlayState::PlayState(StateManager* state_manager_p)
	: GameState(state_manager_p), m_main_panel_p(NULL), m_game_world_p(NULL), m_is_game_over(false), m_is_paused(false)
{
	set_up_text_control();
	initialize_game();																	
}

void PlayState::set_up_text_control()
{
	AddFontResource("fonts/Ghastly Panic.ttf");
	m_font = new GameFont();
	m_font->create_font("Ghastly Panic", 150, FW_NORMAL);
	m_text_control_p = new TextControl(m_font, Rectangle_int(0, GameSettings::get_window_height(), 0, GameSettings::get_window_width()));
	m_text_control_p->set_alignement(TextControl::Center);
	m_text_control_p->set_text_colour(&Colour(187, 187, 187));
}

void PlayState::initialize_game()
{
	m_main_panel_p = new MainPlayerStatusPanel(new Rectangle_int(0, (int)(GameSettings::get_window_height()*0.12), 0, GameSettings::get_window_width()), 100);
	m_game_world_p = new GameWorld(this, m_main_panel_p);
}

PlayState::~PlayState()
{
	RemoveFontResource("Ghastly Panic.ttf");
}

void PlayState::reset()
{
	if(m_game_world_p){ delete m_game_world_p; }
	if(m_main_panel_p){ delete m_main_panel_p; }
	initialize_game();
	set_game_over(false);
}

bool PlayState::is_game_over()
{
	return m_is_game_over;
}

void PlayState::set_game_over(bool is_game_over)
{
	m_is_game_over = is_game_over;
}

void PlayState::enter_state()
{
}

void PlayState::leave_state()
{
}

void PlayState::on_keyup(WPARAM w_param)
{
	m_game_world_p->on_keyup(w_param);
}

void PlayState::on_keydown(WPARAM w_param)
{
	switch (w_param)
	{
		case VK_UP:
			m_game_world_p->on_keydown(w_param);
			break;
		case VK_DOWN:
			m_game_world_p->on_keydown(w_param);
			break;
		case VK_LEFT:
			m_game_world_p->on_keydown(w_param);
			break;
		case VK_RIGHT:
			m_game_world_p->on_keydown(w_param);
			break;
		case VK_PAUSE:
		case VK_P:
			pause_game();
			break;
		case VK_ESCAPE:
			pause_game();
			change_state(MenuState::get_instance(m_state_manager_p));
			break;
		case VK_F12:
			GameSettings::toggle_settings(GameSettings::Debug::DRAW_BOUNDARIES);
			GameSettings::toggle_settings(GameSettings::Debug::DRAW_PANELS);
			break;
	}
}

void PlayState::on_mouse_left_button_click(WPARAM x_coordinate, WPARAM y_coordinate)
{
	m_game_world_p->set_should_bullet_be_fired(true);
}

void PlayState::on_mouse_left_button_release(WPARAM x_coordinate, WPARAM y_coordinate)
{
	m_game_world_p->set_should_bullet_be_fired(false);
}

void PlayState::on_mouse_move(WPARAM x_coordinate, WPARAM y_coordinate)
{
	Location bullet_destination(x_coordinate, y_coordinate);
	m_game_world_p->set_bullet_destination(bullet_destination);
}

void PlayState::pause_game()
{
	m_is_paused = !m_is_paused;

	if(m_is_paused)
	{
		m_game_world_p->pause();
	}
	else
	{
		m_game_world_p->resume();
	}
}

void PlayState::update(DWORD current_time)
{
	if(!m_is_game_over && !m_is_paused)
	{
		m_game_world_p->update();
	}
}

void PlayState::draw()
{
	m_game_world_p->draw();
	m_main_panel_p->draw();
	draw_game_over_screen_if_applicable();
	draw_paused_game_screen_if_applicable();
}

void PlayState::draw_game_over_screen_if_applicable()
{
	if(m_is_game_over)
	{
		draw_black_transparent_screen();
		m_text_control_p->set_text("Game Over");
		m_text_control_p->draw();
	}
}

void PlayState::draw_paused_game_screen_if_applicable()
{
	if(m_is_paused)
	{
		draw_black_transparent_screen();
		m_text_control_p->set_text("Paused");
		m_text_control_p->draw();
	}
}

void PlayState::draw_black_transparent_screen()
{
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
	glBegin(GL_QUADS);
		glVertex3i(0, 0, 0);
		glVertex3i(0, GameSettings::get_window_height(), 0);
		glVertex3i(GameSettings::get_window_width(), GameSettings::get_window_height(), 0);
		glVertex3i(GameSettings::get_window_width(), 0, 0);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}

