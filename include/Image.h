#ifndef IMAGE_H
#define IMAGE_H

#include "Rectangle.h"
#include "Texture.h"

class Image;
typedef Image* Image_ptr;

class Rectangle;
class Texture;
class Location;

class Image
{
	public:
		static Image_ptr create_image(const std::string& filename, int desired_width, int desired_height);
		static Image_ptr create_image(const std::string& filename, int desired_width, int desired_height, const Rectangle_int& texture_coordinates);
		~Image();

		Texture* get_texture() const;
		void draw_image(const Location& location);
		void draw_image(const Location& location, const Rectangle_int& part);

	protected:
		Image(const std::string& filename, int desired_width, int desired_height);
		Image(const std::string& filename, int desired_width, int desired_height, const Rectangle_int& texture_coordinates);

	private:
		void reload_texture_if_actual_size_doesnt_match_desired_size(int desired_width, int desired_height);
		float* calculate_coordinates_of_image(const Rectangle_int& rect) const;
		void draw_textured_rectangle(float coordinates[], int x_offset, int y_offset, const Rectangle_int& rect) const;
		void validate_rectangle_argument(const Rectangle_int& rect) const;

		Texture* m_texture_p;
		Rectangle_int m_rect_texture_coordinates;
};

#endif