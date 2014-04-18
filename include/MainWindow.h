#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Image.h"

class StateManager;

class MainWindow
{
	public:
		MainWindow(int width, int height);
		~MainWindow();
		void update(DWORD time);
		void draw();

	private:
		void register_window_class();
		RECT* set_up_rectangle_dimensions(int width, int height);
		void switch_to_fullscreen_mode_if_necessary(int width, int height);
		void select_window_style();
		void create_window(int width, int height);
		void create_context();
		void initialize_openGL();
		void remove_fullscreen_setting();
		void delete_current_openGL_context();
		void release_device_context();

		void on_size(GLsizei width, GLsizei height); //better name
		static LRESULT CALLBACK on_event_message_received(HWND handle, UINT message, WPARAM w_param, LPARAM l_param);
		void process_event(UINT message, WPARAM w_param, LPARAM l_param);

		HWND m_window_handler;
		DWORD m_ex_style;
		DWORD m_style;
		HDC m_device_context_handler;
		HGLRC m_gl_context_handler; 
		StateManager* m_state_manager_p;
};

#endif