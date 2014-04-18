#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"
#include "Image.h"

class PlayState;
class Button;
class GameFont;
class TextControl;

class MenuState : public GameState
{
	#define NUMBER_OF_MENU_BUTTONS 3

	typedef std::vector<Button*>::iterator ButtonsIterator;
	typedef enum MenuButtons
	{
		NEW_GAME = 0,
		RESUME,
		QUIT
	};

	public:
		static MenuState* get_instance(StateManager* state_manager_p);
		virtual ~MenuState();

		virtual void enter_state();
		virtual void leave_state();

		virtual void on_keyup(WPARAM key);
		virtual void on_keydown(WPARAM key);
		virtual void on_mouse_left_button_click(WPARAM x_coordinate, WPARAM y_coordinate){  }
		virtual void on_mouse_left_button_release(WPARAM x_coordinate, WPARAM y_coordinate){  }
		virtual void on_mouse_move(WPARAM x_coordinate, WPARAM y_coordinate){  }
		virtual void update(DWORD current_time);
		virtual void draw();

	private:
		MenuState(StateManager* state_manager_p);
		void set_up_text_control();
		void selection_up();
		void selection_down();
		void selection_chosen();
		void previous_current_selection();
		void next_current_selection();
		void start_new_game();
		void resume_game();
		void display_highscores();
		void quit_application();

		static MenuState* m_menu_state_p;
		PlayState* m_current_game_p;
		int m_current_selection;
		Image_ptr m_background_image_p;
		GameFont* m_font_p;
		TextControl* m_text_control_p;
		std::vector<Button*> m_buttons;
};

#endif