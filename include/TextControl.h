#ifndef TEXTCONTROL_H
#define TEXTCONTROL_H

#include "Rectangle.h"

class GameFont;
class Colour;

class TextControl
{
	public:
		enum TextAlignement
		{
			Left,
			Center,
			Right
		};

		TextControl(GameFont* font, const Rectangle_int& rectangle_position);
		~TextControl();
		
		void set_text(const std::string& text);
		void set_position(Rectangle_int& rectangle_position);
		void set_alignement(TextAlignement alignement);
		void set_text_colour(Colour* colour);
		void draw();

	private:
		GameFont* m_font;
		Rectangle_int m_rect_position;
		std::string m_text;
		TextAlignement m_alignement;
		Colour* m_text_colour;
};

#endif  _TEXTCONTROL_H_