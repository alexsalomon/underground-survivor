#ifndef ANIMATION_LOADER_H
#define ANIMATION_LOADER_H

class ImageList;
class AnimationLoader
{
	public:
		AnimationLoader(const std::string& filename, unsigned images_per_row, unsigned number_of_rows, unsigned image_width, unsigned image_height);
		~AnimationLoader();

		ImageList get_animation(unsigned start_index, unsigned stop_index);

	private:
		std::string m_filename;
		unsigned m_image_width;
		unsigned m_image_height;
		unsigned m_images_per_row;
		unsigned m_number_of_rows;
};

#endif
