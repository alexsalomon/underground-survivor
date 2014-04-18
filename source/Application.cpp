#include "stdafx.h"
#include "GameSettings.h"
#include "MainWindow.h"
#include "Application.h"

Application::Application()
	: m_mainWindow(NULL)
{
	GameSettings::set_settings(GameSettings::SystemOptions::IS_FULL_SCREEN, false);
}

Application::~Application()
{
}

void Application::initialize_game_settings()
{
	GameSettings::set_settings(GameSettings::Debug::DRAW_BOUNDARIES, false);
	GameSettings::set_settings(GameSettings::Debug::DRAW_PANELS, false);
	GameSettings::set_settings(GameSettings::Debug::DRAW_ENERGY_BARS, false);
}

void Application::run()
{
	create_window();
	set_up_next_deadline();
	bool update = false;

	MSG Message;
	Message.message = ~WM_QUIT;

	while(Message.message != WM_QUIT)		
	{
		DWORD received_message = MsgWaitForMultipleObjectsEx(0, NULL, m_sleeping_time, QS_ALLEVENTS, 0);
		if(received_message != WAIT_TIMEOUT)
		{
			send_message_to_be_processed_by_the_appropriate_window(&Message);

			if (GetTickCount() >= m_next_deadline)
			{
				update = true;
			}
			else
			{
				update = false;
			}
		}
		else
		{
			update = true;
		}

		update_application_if_necessary(update);
		recalculate_sleeping_time_and_next_deadline();
	}

	delete(m_mainWindow);
}

void Application::create_window()
{						
	RECT desktop_area;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop_area, 0);
	int screen_width = desktop_area.right;
	int screen_height = desktop_area.bottom;

	GameSettings::set_window_width(screen_width);
	GameSettings::set_window_height(screen_height);

	m_mainWindow = new MainWindow(screen_width, screen_height);
	//1280, 768
}

void Application::set_up_next_deadline()
{		
	m_next_deadline = GetTickCount() + FRAME_TIME;	
	m_sleeping_time = FRAME_TIME;
}

void Application::send_message_to_be_processed_by_the_appropriate_window(MSG* Message) const
{
	if(PeekMessage(&(*Message), NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&(*Message));
		DispatchMessage(&(*Message));
	}
}

void Application::update_application_if_necessary(bool update)
{
	if(update)
	{
		DWORD current_time = GetTickCount();
		m_mainWindow->update(current_time);
		m_mainWindow->draw();
		m_next_deadline = m_next_deadline + FRAME_TIME;
	}
}

void Application::recalculate_sleeping_time_and_next_deadline()
{
	m_sleeping_time = m_next_deadline - GetCurrentTime();			

	if(m_sleeping_time > FRAME_TIME)								
	{
		m_sleeping_time = FRAME_TIME;
		m_next_deadline = GetCurrentTime() + FRAME_TIME;
	}
}
