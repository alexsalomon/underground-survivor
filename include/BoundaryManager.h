#ifndef BOUNDARY_MANAGER_H
#define BOUNDARY_MANAGER_H

#include "Boundary.h"

class Collisiable;
class BoundaryManager
{
	public:	
		static BoundaryManager* get_instance();
		virtual ~BoundaryManager();
		Boundary* choose_strategy(BoundaryStrategy strategy);

	private:
		BoundaryManager();

		static BoundaryManager* m_boundary_manager;
		//list of all boundaries created so far - type collisiable
};

#endif