#include "stdafx.h"
#include "StateManager.h"
#include "GameFont.h"
#include "MainWindow.h"
#include "GameSettings.h"

MainWindow::MainWindow(int width, int height)
  :  m_window_handler(NULL), m_device_context_handler(NULL), m_gl_context_handler(NULL), m_state_manager_p(NULL)
{
	register_window_class();
	switch_to_fullscreen_mode_if_necessary(width, height);
	select_window_style();
	create_window(width, height);
	create_context();
	GameFont::set_device_context(m_device_context_handler);
	initialize_openGL();
	ShowWindow(m_window_handler, /*SW_SHOW*/ SW_MAXIMIZE);
	on_size(width, height);
	m_state_manager_p = new StateManager();
}

MainWindow::~MainWindow()
{
	remove_fullscreen_setting();
	delete_current_openGL_context();
	release_device_context();
    DestroyWindow(m_window_handler);
    UnregisterClass(GAME_NAME, GetModuleHandle(NULL));
	delete(m_state_manager_p);
}

void MainWindow::register_window_class()
{
	WNDCLASS WindowClass;
	WindowClass.style         = 0;
	WindowClass.lpfnWndProc   = &MainWindow::on_event_message_received;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = GetModuleHandle(NULL);
	WindowClass.hIcon         = NULL;
	WindowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = 0;
	WindowClass.lpszMenuName  = NULL;
	WindowClass.lpszClassName = GAME_NAME;

	RegisterClass(&WindowClass);
}

void MainWindow::switch_to_fullscreen_mode_if_necessary(int width, int height)
{
	if(GameSettings::get_settings(GameSettings::SystemOptions::IS_FULL_SCREEN))
	{
		DEVMODE ScreenSettings;
		memset(&ScreenSettings, 0, sizeof(ScreenSettings));
		ScreenSettings.dmSize = sizeof(ScreenSettings);
		ScreenSettings.dmPelsWidth  = width;
		ScreenSettings.dmPelsHeight = height;
		ScreenSettings.dmBitsPerPel = 32;
		ScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if (ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
		  throw Exception("MainWindow::switch_to_fullscreen_mode - Unable to switch to fullscreen mode");
		}

		ShowCursor(FALSE);
	}
}

void MainWindow::select_window_style()
{
	if(GameSettings::get_settings(GameSettings::SystemOptions::IS_FULL_SCREEN))
	{
		m_ex_style = WS_EX_APPWINDOW;
		m_style = WS_POPUP;
	}
	else
	{
		m_ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		m_style = WS_OVERLAPPEDWINDOW;
	}
}

void MainWindow::create_window(int width, int height)
{
	RECT WindowRect;
	WindowRect.top = 0;
	WindowRect.left = 0;
	WindowRect.right = width;
	WindowRect.bottom = height;

	AdjustWindowRectEx(&WindowRect, m_style, FALSE, m_ex_style);
	m_window_handler = CreateWindowEx(m_ex_style, GAME_NAME, GAME_NAME, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | m_style,
													0, 0, (WindowRect.right - WindowRect.left), (WindowRect.bottom - WindowRect.top), NULL, NULL,
													GetModuleHandle(NULL), this);

	if (m_window_handler == NULL)
	{
		throw Exception("MainWindow::create_window - Cannot create the main window");
	}
}

LRESULT MainWindow::on_event_message_received(HWND handle, UINT message, WPARAM w_param, LPARAM l_param)
{
  if (message == WM_NCCREATE)
  {
    CREATESTRUCT* create_struct_p = reinterpret_cast<CREATESTRUCT*>(l_param);
    SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<long>(create_struct_p->lpCreateParams));
  }

  MainWindow* window_p = reinterpret_cast<MainWindow*>(GetWindowLongPtr(handle, GWLP_USERDATA));

  if (window_p)
  {
    window_p->process_event(message, w_param, l_param);
  }

  return DefWindowProc(handle, message, w_param, l_param);
}

void MainWindow::process_event(UINT message, WPARAM w_param, LPARAM l_param)
{
    switch (message)
    {
		case WM_CLOSE :
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			on_size(LOWORD(l_param), HIWORD(l_param));
			break;
		case WM_KEYDOWN :
			m_state_manager_p->on_keydown(w_param);
			break;
		case WM_KEYUP :
			m_state_manager_p->on_keyup(w_param);
			break;
		case WM_LBUTTONDOWN :
			m_state_manager_p->on_mouse_left_button_click(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
			break;
		case WM_LBUTTONUP :
			m_state_manager_p->on_mouse_left_button_release(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
			break;
		case WM_MOUSEMOVE :
			m_state_manager_p->on_mouse_move(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
    }
}

void MainWindow::create_context()
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |	PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;	
	pfd.cColorBits = 32;

	m_device_context_handler = GetDC(m_window_handler);
	if (!m_device_context_handler)	
		throw Exception("Unable to create rendering context - Device Context Handler not found");

	int PixelFormat = ChoosePixelFormat(m_device_context_handler, &pfd);
	if (!PixelFormat)				
		throw Exception("Unable to create rendering context");

	if(!SetPixelFormat(m_device_context_handler, PixelFormat, &pfd))			
		throw Exception("Unable to create rendering context");

	m_gl_context_handler = wglCreateContext(m_device_context_handler);
	if (!m_gl_context_handler)	
		throw Exception("Unable to create rendering context");

	if(!wglMakeCurrent(m_device_context_handler, m_gl_context_handler))
		throw Exception("Unable to create rendering context");						
}

void MainWindow::initialize_openGL()
{
	glEnable(GL_TEXTURE_2D);			// Enable 2D texturing
    glShadeModel(GL_FLAT);				// Choose a smooth shading model
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Set the clear color to black
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);					// Enable blending
}

void MainWindow::on_size(GLsizei width, GLsizei height)
{
    glViewport(0,0, width, height);		// Sets the size of the OpenGL viewport
	glMatrixMode(GL_PROJECTION);		// Select the projection stack and apply an orthographic projection
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void MainWindow::remove_fullscreen_setting()
{
	if(GameSettings::get_settings(GameSettings::SystemOptions::IS_FULL_SCREEN))
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);	
	}
}

void MainWindow::delete_current_openGL_context()
{
	if (m_gl_context_handler)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(m_gl_context_handler);
		m_gl_context_handler = NULL;
	}
}

void MainWindow::release_device_context()
{
	if (m_device_context_handler)
	{
		ReleaseDC(m_window_handler,m_device_context_handler);
		m_device_context_handler = NULL;
	}
}

void MainWindow::update(DWORD current_time)
{
	m_state_manager_p->update(current_time);
}

void MainWindow::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_state_manager_p->draw();
	SwapBuffers(m_device_context_handler);
}
