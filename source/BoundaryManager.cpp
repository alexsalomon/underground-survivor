#include "stdafx.h"
#include "Collisiable.h"
#include "BoundaryManager.h"
#include "BoundingBox.h" 
#include "InvertedBoundingBox.h" 

BoundaryManager* BoundaryManager::m_boundary_manager = NULL;

BoundaryManager* BoundaryManager::get_instance()
{
	if(m_boundary_manager == NULL)
		m_boundary_manager = new BoundaryManager();

	return m_boundary_manager;
}

BoundaryManager::BoundaryManager()
{
}

BoundaryManager::~BoundaryManager()
{
}

Boundary* BoundaryManager::choose_strategy(BoundaryStrategy strategy)
{
	Boundary* boundary = NULL;

	switch(strategy)
	{
		case(BOUNDING_BOX):
			boundary = new BoundingBox();
			break;
		case(INVERTED_BOUNDING_BOX):
			boundary = new InvertedBoundingBox();
			break;
		default:
			throw("Collision detection strategy unknown: " + strategy);
	}

	return boundary;
}
