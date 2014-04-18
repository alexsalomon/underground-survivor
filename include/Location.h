#ifndef LOCATION_H
#define LOCATION_H

class Location
{
	public:
		Location() : x_position(0), y_position(0){  }
		Location(int x, int y) : x_position(x), y_position(y){  }
		virtual ~Location(){  }

		bool is_zero() const
		{
			return (x_position == 0 && y_position == 0);
		}

		int x_position;
		int y_position;
};

#endif