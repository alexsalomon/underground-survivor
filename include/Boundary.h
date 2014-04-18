#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Rectangle.h"

typedef enum
{
	BOUNDING_BOX = 0,
	INVERTED_BOUNDING_BOX
} BoundaryStrategy;

class Location;
class Collisiable;
class Boundary
{
	public:
		virtual ~Boundary(){ }

		virtual Rectangle_int* get_rectangle() = 0;

		virtual void create_boundary(Rectangle_int& rect_position) = 0;
		virtual void update_boundary(int x_offset, int y_offset) = 0;
		virtual void draw_boundary() = 0;
		virtual bool is_there_collision_with(Boundary* boundary) = 0;	
};

#endif
