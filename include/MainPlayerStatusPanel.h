#ifndef MAIN_PLAYER_STATUS_PANEL_H
#define MAIN_PLAYER_STATUS_PANEL_H

#include "Panel.h"

class EnergyBar;
class Colour;
class GameFont;
class TextControl;

class MainPlayerStatusPanel : public Panel
{
	public:
		MainPlayerStatusPanel(Rectangle_int* panel_coordinates, unsigned int energy);
		~MainPlayerStatusPanel();

		void update(int damage);
		void draw();
		Colour* get_panel_drawing_colour(){ return new Colour(181, 230, 29); }

	private:
		void set_up_text_control();

		EnergyBar* m_energy_bar_p;
		unsigned int m_energy;
		GameFont* m_font_p;
		TextControl* m_text_control_p;
};

#endif
