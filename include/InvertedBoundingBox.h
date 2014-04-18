#ifndef INVERTED_BOUNDING_BOX_H
#define INVERTED_BOUNDING_BOX_H

#include "Boundary.h"
#include "Rectangle.h"

class InvertedBoundingBox : public Boundary
{
	friend class BoundaryManager;

	public:
		virtual ~InvertedBoundingBox();

		Rectangle_int* get_rectangle();

		void create_boundary(Rectangle_int& rect_position);
		void update_boundary(int x_offset, int y_offset);
		void draw_boundary();
		bool is_there_collision_with(Boundary* boundary);
			
	private:
		InvertedBoundingBox();

		Rectangle_int* m_rectangle;
};

#endif
