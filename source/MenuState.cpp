#include "stdafx.h"
#include "Button.h"
#include "PlayState.h"
#include "MenuState.h"
#include "GameSettings.h"
#include "Location.h"
#include "TextControl.h"
#include "GameFont.h"
#include "Colour.h"

MenuState* MenuState::m_menu_state_p = NULL;

MenuState* MenuState::get_instance(StateManager* state_manager_p)
{
	if(m_menu_state_p == NULL)
		m_menu_state_p = new MenuState(state_manager_p);

	return m_menu_state_p;
}

MenuState::MenuState(StateManager* state_manager_p)
	: GameState(state_manager_p), m_current_game_p(NULL), m_current_selection(0)
{
	set_up_text_control();
	m_background_image_p = Image::create_image("images/zombie_background_1280.bmp", GameSettings::get_window_width(), GameSettings::get_window_height());

	m_buttons.push_back(new Button("New Game", 0));
	m_buttons.push_back(new Button("Resume Game", 1));
	//m_buttons.push_back(new Button("High scores", 2));
	m_buttons.push_back(new Button("Exit", 2));
}

MenuState::~MenuState()
{
	for(ButtonsIterator iter = m_buttons.begin(); iter != m_buttons.end(); ++iter)
	{
		if(*iter)
		{
			delete (*iter);
		}
	}

	RemoveFontResource("evil_bunny.ttf");
}

void MenuState::set_up_text_control()
{
	m_font_p = new GameFont();
	AddFontResource("fonts/Ghastly Panic.ttf");
	m_font_p->create_font("Ghastly Panic", 300, FW_NORMAL);
	m_text_control_p = new TextControl(m_font_p, Rectangle_int(0, GameSettings::get_window_height()/2, 0, GameSettings::get_window_width()));
	m_text_control_p->set_alignement(TextControl::Center);
	m_text_control_p->set_text_colour(new Colour(237, 28, 36));
}

void MenuState::enter_state()
{
	if(!m_current_game_p || m_current_game_p->is_game_over())
	{
		m_buttons[NEW_GAME]->disable(false);
		m_buttons[NEW_GAME]->set_selected(true);
		m_buttons[RESUME]->disable(true);
		m_buttons[RESUME]->set_selected(false);
		m_current_selection = NEW_GAME;
	}
	else
	{
		m_buttons[NEW_GAME]->disable(true);
		m_buttons[NEW_GAME]->set_selected(false);
		m_buttons[RESUME]->disable(false);
		m_buttons[RESUME]->set_selected(true);
		m_current_selection = RESUME;
	}

	//m_buttons[HIGHSCORES]->disable(true);
}

void MenuState::leave_state()
{
}

void MenuState::on_keyup(WPARAM key)
{
}

void MenuState::on_keydown(WPARAM key)
{
	switch (key)
	{
	case VK_DOWN:
		selection_down();
		break;
	case VK_UP:
		selection_up();
		break;
	case VK_RETURN:
		selection_chosen();
		break;
	}
}

void MenuState::update(DWORD current_time)
{
}

void MenuState::selection_down()
{
	m_buttons[m_current_selection]->set_selected(false);
	next_current_selection();

	while(m_buttons[m_current_selection]->is_disabled())
	{
		next_current_selection();
	}

	m_buttons[m_current_selection]->set_selected(true);
}

void MenuState::next_current_selection()
{
	m_current_selection++;

	if(m_current_selection == NUMBER_OF_MENU_BUTTONS)
	{
		m_current_selection = 0;
	}
}

void MenuState::selection_up()
{
	m_buttons[m_current_selection]->set_selected(false);
	previous_current_selection();

	while(m_buttons[m_current_selection]->is_disabled())
	{
		previous_current_selection();
	}

	m_buttons[m_current_selection]->set_selected(true);

}

void MenuState::previous_current_selection()
{
	m_current_selection--;

	if (m_current_selection == -1)
	{
		m_current_selection = NUMBER_OF_MENU_BUTTONS-1;
	}
}

void MenuState::selection_chosen()
{
	switch (m_current_selection)
	{
		case NEW_GAME:
			start_new_game();
			break;

		case RESUME:
			resume_game();
			break;

		//case HIGHSCORES:
		//	display_highscores();
		//	break;

		case QUIT:
			quit_application();
			break;
	}
}

void MenuState::start_new_game()
{
	if(!m_current_game_p)
	{
		m_current_game_p = PlayState::get_instance(m_state_manager_p);
	}
	else
	{
		m_current_game_p->reset();
	}

	change_state(m_current_game_p);
}

void MenuState::resume_game()
{
	if (m_current_game_p && !m_current_game_p->is_game_over())
	{
		change_state(m_current_game_p);
	}
}

void MenuState::display_highscores()
{
	//change_state(HighScoreState::get_instance(m_state_manager_p));
}

void MenuState::quit_application()
{
	PostQuitMessage(0);
}

void MenuState::draw()
{
	m_background_image_p->draw_image(Location(0, 0));
	m_text_control_p->set_text(GAME_NAME);
	m_text_control_p->draw();

	for(ButtonsIterator iter = m_buttons.begin(); iter != m_buttons.end(); ++iter)
	{
		(*iter)->draw();
	}
}
