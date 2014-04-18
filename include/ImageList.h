#ifndef IMAGE_LIST_H
#define IMAGE_LIST_H

class Image;
class ImageList
{
	public:
		ImageList();
		ImageList(const ImageList& other);
		~ImageList();

		ImageList& operator= (const ImageList& other);

		void clear_list();
		void append_image(Image_ptr image_p);
		unsigned get_images_count() const;
		void go_to_first_image();
		bool go_to_next_image();
		Image_ptr get_current_image() const;

	private:
		void copy_list(const ImageList& other_image);

		typedef std::list<Image_ptr> ImageList_type;
		ImageList_type m_image_list;
		ImageList_type::iterator m_current_image_iter;
};

#endif