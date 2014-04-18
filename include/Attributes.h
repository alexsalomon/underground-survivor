    #ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

class Attributes
{
	public:
		Attributes(int energy, int resistency, int attack_power, int moving_speed, int attack_speed);
		Attributes();
		~Attributes();

		bool inflict_damage(int damage);
		bool is_dead();

		int energy;
		int resistency;
		int attack_power;
		int moving_speed;
		int attack_speed;
};

#endif 