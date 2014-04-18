#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Collisiable.h"
#include "Renderable.h"
#include "Image.h"

class Boundary;
class Location;

class Background : public Collisiable, public Renderable
{
	typedef std::vector<Location*> EnemySpawningLocations;

	public:
		Background();
		virtual ~Background();

		void update();
		void draw();
		Boundary* get_boundary();

		Location* get_enemy_spawning_location(int index);

	private:
		void initialize_enemy_spawning_locations();
		void draw_boundary_if_applicable(bool is_draw_boundary_enabled);

		Image_ptr m_background_image_p;
		Boundary* m_boundary_p;
		EnemySpawningLocations m_enemy_spawning_locations;
};

#endif