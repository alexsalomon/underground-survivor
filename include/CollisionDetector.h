#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

class Collisiable;
class CollisionDetector
{
	typedef std::list<Collisiable*> List;
	typedef std::list<Collisiable*>::iterator ListIterator;

	public:
		static bool collide(Collisiable* object_one, Collisiable* object_two);	
		static bool collide(Collisiable* object_one, List collisiable_list);
};

#endif
