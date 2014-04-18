#include "stdafx.h"
#include "TextControl.h"
#include "GameFont.h"
#include "Colour.h"
#include "Location.h"

TextControl::TextControl(GameFont* font, const Rectangle_int& rectangle_position)
  : m_font(font), m_rect_position(rectangle_position), m_text(""), m_text_colour(new Colour(0, 0, 0))
{
}

TextControl::~TextControl()
{
}

void TextControl::set_text(const std::string& text)
{
	m_text = text; 
}

void TextControl::set_position(Rectangle_int& rectangle_position)
{
	m_rect_position = rectangle_position; 
}

void TextControl::set_alignement(TextAlignement alignement)
{
	m_alignement = alignement; 
}

void TextControl::set_text_colour(Colour* colour)
{
	if(m_text_colour){ delete m_text_colour; }
	m_text_colour = colour;
}

void TextControl::draw()
{
	Rectangle_int text_size = m_font->get_text_size(m_text);
	int x_offset = 0;
	int y_offset = (m_rect_position.get_height() / 2) + (text_size.get_height() / 2);

	switch (m_alignement)
	{
		case Left:
			break;
		case Center:
			x_offset = (m_rect_position.get_width() - text_size.get_width()) / 2;
			break;
		case Right:
			x_offset = m_rect_position.get_width() - text_size.get_width();
			break;
	}

	int x_pos = m_rect_position.left + x_offset;
	int y_pos = m_rect_position.top + y_offset - 5;
	m_font->draw_text(m_text, new Location(x_pos, y_pos), m_text_colour);
}
