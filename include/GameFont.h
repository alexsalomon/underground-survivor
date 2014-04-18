#ifndef GAMEFONT_H_
#define GAMEFONT_H_

#include "Rectangle.h"
class Location;
class Colour;

class GameFont
{
	public:
		GameFont();
		~GameFont();

		void create_font(const std::string& font_name, int height, int weight);
		void draw_text(const std::string& font_name, Location* location_p, Colour* font_colour);
		Rectangle_int get_text_size(const std::string& font_name);

		static void set_device_context(HDC device_context);  

	private:
		static HDC m_device_context;
		GLuint m_list_base_index;
		HFONT m_font;
};

#endif 
