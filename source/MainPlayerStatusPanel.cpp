#include "stdafx.h"
#include "MainPlayerStatusPanel.h"
#include "EnergyBar.h"
#include "Location.h"
#include "GameFont.h"
#include "TextControl.h"

MainPlayerStatusPanel::MainPlayerStatusPanel(Rectangle_int* panel_coordinates_p, unsigned int energy)
	: Panel(panel_coordinates_p), m_energy(energy)
{
																						//m_panel_height*0.20 when panel was in the bottom
	m_energy_bar_p = new EnergyBar(translate_position((int)(m_panel_width*0.33), (int)(m_panel_height*0.50)), 100);
	set_up_text_control();
}

MainPlayerStatusPanel::~MainPlayerStatusPanel()
{
	RemoveFontResource("Ghastly Panic.ttf");
}

void MainPlayerStatusPanel::set_up_text_control()
{
	AddFontResource("fonts/Ghastly Panic.ttf");
	m_font_p = new GameFont();
	m_font_p->create_font("Ghastly Panic", 57, FW_NORMAL);

	Rectangle_int* energy_bar_rect = m_energy_bar_p->get_rectangle();
	m_text_control_p = new TextControl(m_font_p, Rectangle_int(energy_bar_rect->top - 37, energy_bar_rect->bottom, (energy_bar_rect->left - 100), energy_bar_rect->left));
	m_text_control_p->set_alignement(TextControl::Center);
	m_text_control_p->set_text_colour(&Colour(237, 28, 36));
	m_text_control_p->set_text("Energy");
}

void MainPlayerStatusPanel::update(int damage)
{
	m_energy_bar_p->update(damage);
}

void MainPlayerStatusPanel::draw()
{
	Panel::draw();
	m_text_control_p->draw();
	m_energy_bar_p->draw();
	m_text_control_p->draw();
}


