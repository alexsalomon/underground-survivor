#ifndef BUTTON_H
#define BUTTON_H

#include "Image.h"

class GameFont;
class Location;
class TextControl;

class Button
{
	#define DISTANCE_BETWEEN_BUTTONS 100

	public:
		Button(std::string text, int order);
		~Button();

		void disable(bool is_disabled);
		void set_selected(bool is_selected);
		bool is_selected();
		bool is_disabled();
		void draw();

	private:
		void create_font();
		void create_images();
		void set_up_text_control(std::string text);
		int get_x_position();
		int get_y_position(int distance_offset);

		int m_button_order;
		bool m_is_selected;
		bool m_is_disabled;
		GameFont* m_font;
		TextControl* m_text_control_p;
		Image_ptr m_selected_button_p;
		Image_ptr m_unselected_button_p;
};

#endif