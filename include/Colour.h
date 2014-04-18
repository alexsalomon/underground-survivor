#ifndef COLOUR_H
#define COLOUR_H

class Colour
{
	public:
		Colour() : red(0), green(0), blue(0){  }
		Colour(unsigned char l_red, unsigned char l_green, unsigned char l_blue) : red(l_red), green(l_green), blue(l_blue){  }
		virtual ~Colour(){ }

		void set_colour(unsigned char l_red, unsigned char l_green, unsigned char l_blue)
		{
			red = l_red;
			green = l_green;
			blue = l_blue;
		}
		
		unsigned char red;
		unsigned char green;
		unsigned char blue;
};

#endif
