#include "stdafx.h"
#include "Button.h"
#include "GameFont.h"
#include "Location.h"
#include "TextControl.h"
#include "Colour.h"
#include "GameSettings.h"

Button::Button(std::string text, int order)
	: m_is_selected(false), m_is_disabled(false), m_font(NULL), m_selected_button_p(NULL), m_unselected_button_p(NULL), m_text_control_p(NULL), m_button_order(order)
{
	create_font();
	create_images();
	set_up_text_control(text);
}

Button::~Button()
{
	if(m_font){ m_font; }
	if(m_text_control_p){ m_text_control_p; }
}

void Button::create_font()
{
	m_font = new GameFont();
	m_font->create_font("Verdana", 30, FW_NORMAL);
}

void Button::create_images()
{
	m_unselected_button_p = Image::create_image("images/MenuButtons.png", 512, 128, Rectangle_int(0, 57, 0, 382));
	m_selected_button_p = Image::create_image("images/MenuButtons.png", 512, 128, Rectangle_int(58, 114, 0, 382));
}

void Button::set_up_text_control(std::string text)
{
	int top = get_y_position(DISTANCE_BETWEEN_BUTTONS);
	int bottom = top + 57; //TODO: 57 is the image height
	int left = get_x_position();
	int right = left + 382; //TODO: 382 is the image width

	m_text_control_p = new TextControl(m_font, Rectangle_int(top, bottom, left, right)); //(150+(100*m_button_order), 207+(100*m_button_order), 209, 591));
	m_text_control_p->set_alignement(TextControl::Center);
	m_text_control_p->set_text(text);
	m_text_control_p->set_text_colour(new Colour(185, 0, 0));
}	

bool Button::is_selected()
{
	return m_is_selected;
}

bool Button::is_disabled()
{
	return m_is_disabled;
}

void Button::disable(bool is_disabled)
{
	m_is_disabled = is_disabled;
}

void Button::set_selected(bool is_selected)
{
	m_is_selected = is_selected;
}

void Button::draw()
{
	int x_position = get_x_position();
	int y_position = get_y_position(DISTANCE_BETWEEN_BUTTONS);

	if(m_is_selected)
	{
		m_selected_button_p->draw_image(Location(x_position, y_position));
	}
	else
	{
		m_unselected_button_p->draw_image(Location(x_position, y_position));
	}

	if(m_is_disabled)
	{
		m_text_control_p->set_text_colour(new Colour(108, 108, 108));
	}
	else
	{
		m_text_control_p->set_text_colour(new Colour(237, 28, 36));
	}

	m_text_control_p->set_position(Rectangle_int(y_position, y_position+57, x_position, x_position+382));
	m_text_control_p->draw();
}

int Button::get_x_position()
{
	//TODO: remove padding of image in order to make this work: (m_selected_button_p->get_texture()->get_width() / 2);
	int half_of_image_width = 192;
	int x_position = (GameSettings::get_window_width() / 2) - half_of_image_width;
	return x_position;
}

int Button::get_y_position(int distance_offset)
{
	int y_position = (GameSettings::get_window_height() / 2) + (m_button_order * distance_offset);
	return y_position;
}
