#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

class Bullet;
class BulletFactory
{
	public:
		BulletFactory();
		virtual ~BulletFactory();
		static Bullet* create_piece(BulletType bullet_type, Location* initial_position_p, Location* destination_p);
};

#endif