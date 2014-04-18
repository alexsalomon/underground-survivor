#include "stdafx.h"
#include "Weapon.h"
#include "Bullet.h"
#include "BulletFactory.h"

BulletFactory::BulletFactory()
{
}

BulletFactory::~BulletFactory()
{
}

Bullet* BulletFactory::create_piece(BulletType bullet_type, Location* initial_position_p, Location* destination_p)
{
	Bullet* bullet_p;

	switch(bullet_type)
	{
		case PISTOL_BULLET:
			bullet_p = new Bullet(initial_position_p, destination_p);
			break;
		default:
			bullet_p = NULL;
	}

	return bullet_p;
}
