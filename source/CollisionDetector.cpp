#include "stdafx.h"
#include "Collisiable.h"
#include "CollisionDetector.h"
#include "Boundary.h"

bool CollisionDetector::collide(Collisiable* object_one, Collisiable* object_two)
{
	Boundary* boundary_1 = object_one->get_boundary();
	Boundary* boundary_2 = object_two->get_boundary();

	Rectangle_int* rect_1 = boundary_1->get_rectangle();
	Rectangle_int* rect_2 = boundary_2->get_rectangle();

	assert(rect_1->is_valid());
	assert(rect_2->is_valid());

	return boundary_1->is_there_collision_with(boundary_2);
}

bool CollisionDetector::collide(Collisiable* object_one, List collisiable_list)
{
	/*Collisiable* collided_object;

	for(ListIterator iter = collisiable_list.begin(); iter != collisiable_list.end(); iter++)
	{
		if(collide(object_one, *iter))
		{
			return *iter;
		}
	}*/

	return true;
}
