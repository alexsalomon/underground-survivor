#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Boundary.h"
#include "Rectangle.h"

class BoundingBox : public Boundary
{
	friend class BoundaryManager;

	public:
		virtual ~BoundingBox();

		Rectangle_int* get_rectangle();

		void create_boundary(Rectangle_int& rect_position);
		void update_boundary(int x_offset, int y_offset);
		void draw_boundary();
		bool is_there_collision_with(Boundary* boundary);
			
	private:
		BoundingBox();

		Rectangle_int* m_rectangle;
};

#endif
