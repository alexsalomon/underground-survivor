#ifndef GAME_STATE_H
#define GAME_STATE_H

class StateManager;
class GameState
{
	public:
		GameState(StateManager* state_manager_p);
		virtual ~GameState();

		virtual void enter_state() = 0;
		virtual void leave_state() = 0;

		virtual void on_keyup(WPARAM w_param) = 0;
		virtual void on_keydown(WPARAM w_param) = 0;
		virtual void on_mouse_left_button_click(WPARAM x_coordinate, WPARAM y_coordinate) = 0;
		virtual void on_mouse_left_button_release(WPARAM x_coordinate, WPARAM y_coordinate) = 0;
		virtual void on_mouse_move(WPARAM x_coordinate, WPARAM y_coordinate) = 0;
		virtual void update(DWORD current_time) = 0;
		virtual void draw() = 0;

	protected:
		void change_state(GameState* new_game_state_p);
		StateManager* m_state_manager_p;
};

#endif