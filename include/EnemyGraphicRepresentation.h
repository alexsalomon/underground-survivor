#ifndef ENEMY_GRAPHIC_REPRESENTATION_H
#define ENEMY_GRAPHIC_REPRESENTATION_H

#include "GraphicRepresentation.h"

class EnergyBar;

class EnemyGraphicRepresentation : public GraphicRepresentation
{
	public:
		EnemyGraphicRepresentation(int enemys_energy, int animation_width, int animation_height);
		virtual ~EnemyGraphicRepresentation();

		virtual void update(const Location& offset, unsigned int damage, bool should_update_offset = true);
		virtual void draw();
		virtual void set_animation_position(Location* location_p);

	protected:
		void draw_energy_bar();

		EnergyBar* m_energy_bar_p;
};

#endif
