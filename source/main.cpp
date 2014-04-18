/*
*	main.cpp
*/

#include "stdafx.h"
#include "Application.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT)
{
	try
	{
		Application application;
		application.initialize_game_settings();
		application.run();
	}
	catch(Exception& e)
	{
		MessageBox(NULL, e.what(), "Error", MB_OK|MB_ICONEXCLAMATION);
	}

	return 0;
}
