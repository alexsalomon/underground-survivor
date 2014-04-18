#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

class GameState;
class StateManager
{
	public:
		StateManager();
		~StateManager();

		void change_state(GameState* new_game_state_p);
		GameState* get_current_state();

		void on_keyup(WPARAM w_param);
		void on_keydown(WPARAM w_param);
		void on_mouse_left_button_click(WPARAM x_coordinate, WPARAM y_coordinate);
		void on_mouse_left_button_release(WPARAM x_coordinate, WPARAM y_coordinate);
		void on_mouse_move(WPARAM x_coordinate, WPARAM y_coordinate);
		void update(DWORD current_time);
		void draw();

	private:
		GameState* m_current_state_p;
};

#endif