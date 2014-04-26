#include "stdafx.h"
#include "ZombieGruntPurple.h"
#include "ZombieGruntPurpleGraphicRepresentation.h"
#include "Attributes.h"
#include "GameSettings.h"

ZombieGruntPurple::ZombieGruntPurple()
	: Enemy()
{
	m_graphic_representation_p = new ZombieGruntPurpleGraphicRepresentation(INITIAL_ENERGY);	
	m_attributes_p = new Attributes(INITIAL_ENERGY, INITIAL_RESISTENCY, INITIAL_ATTACK_POWER, INITIAL_MOVING_SPEED, INITIAL_ATTACK_SPEED);
}

ZombieGruntPurple::~ZombieGruntPurple()
{
}
