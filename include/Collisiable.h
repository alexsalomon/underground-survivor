#ifndef COLLISIABLE_H
#define COLLISIABLE_H

class Boundary;
class Collisiable
{
	public:
		virtual ~Collisiable(){ }

		virtual Boundary* get_boundary() = 0;
};

#endif
