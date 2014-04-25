#include "stdafx.h"
#include "ZombiePurple.h"
#include "ZombiePurpleGraphicRepresentation.h"
#include "Attributes.h"
#include "GameSettings.h"

ZombiePurple::ZombiePurple()
	: Enemy()
{
	m_graphic_representation_p = new ZombiePurpleGraphicRepresentation(INITIAL_ENERGY);	
	m_attributes_p = new Attributes(INITIAL_ENERGY, INITIAL_RESISTENCY, INITIAL_ATTACK_POWER, INITIAL_MOVING_SPEED, INITIAL_ATTACK_SPEED);
}

ZombiePurple::~ZombiePurple()
{
}
