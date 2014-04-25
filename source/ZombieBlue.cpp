#include "stdafx.h"
#include "ZombieBlue.h"
#include "ZombieBlueGraphicRepresentation.h"
#include "Attributes.h"
#include "GameSettings.h"

ZombieBlue::ZombieBlue()
	: Enemy()
{
	m_graphic_representation_p = new ZombieBlueGraphicRepresentation(INITIAL_ENERGY);	
	m_attributes_p = new Attributes(INITIAL_ENERGY, INITIAL_RESISTENCY, INITIAL_ATTACK_POWER, INITIAL_MOVING_SPEED, INITIAL_ATTACK_SPEED);
}

ZombieBlue::~ZombieBlue()
{
}
