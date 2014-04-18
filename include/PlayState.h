#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "Image.h"

class GameWorld;
class Panel;
class GameFont;
class TextControl;

class PlayState : public GameState
{
	static const int VK_P = 80;

	public:
		static PlayState* get_instance(StateManager* state_manager_p);
		virtual ~PlayState();

		virtual void enter_state();
		virtual void leave_state();

		virtual void reset();
		virtual bool is_game_over();
		virtual void set_game_over(bool is_game_over);
		virtual void on_keyup(WPARAM w_param);
		virtual void on_keydown(WPARAM w_param);
		virtual void on_mouse_left_button_click(WPARAM x_coordinate, WPARAM y_coordinate);
		virtual void on_mouse_left_button_release(WPARAM x_coordinate, WPARAM y_coordinate);
		virtual void on_mouse_move(WPARAM x_coordinate, WPARAM y_coordinate);
		virtual void update(DWORD current_time);
		virtual void draw();

	private:
		PlayState(StateManager* state_manager_p);
		void initialize_game();
		void set_up_text_control();	
		void pause_game();
		void draw_game_over_screen_if_applicable();
		void draw_paused_game_screen_if_applicable();
		void draw_black_transparent_screen();

		static PlayState* m_play_state_p;
		GameWorld* m_game_world_p;
		Panel* m_main_panel_p;
		GameFont* m_font;
		TextControl* m_text_control_p;
		bool m_is_game_over;
		bool m_is_paused;
};

#endif