#ifndef CRECTANGLE_H
#define CRECTANGLE_H

template <class T>
class CRectangle
{
	public:
		CRectangle() : top(0), bottom(0), left(0), right(0){ }
		CRectangle (T top, T bottom, T left, T right) : top(top), bottom(bottom), left(left), right(right){ }
		~CRectangle(){ }

		T get_width()  const { return right - left;  }
		T get_height() const  { return bottom - top;  }

		bool does_rectangle_intersect(const CRectangle& rect) const
		{
			return ((left < rect.right) && (right > rect.left ) && (bottom > rect.top) && (top < rect.bottom));
		}

		bool is_valid() const
		{
			bool is_valid = true;

			if ( (top > bottom) || (left > right) )
			{
				is_valid = false;
			}

			return is_valid;
		}

		void offset_rectangle(int x_offset, int y_offset)
		{
			top += y_offset;
			bottom += y_offset;
			left += x_offset;
			right += x_offset;
		}

		T  top;
		T  bottom;
		T  left;
		T  right;	
};

typedef CRectangle<int>    Rectangle_int;
typedef CRectangle<float>  Rectangle_float;
typedef CRectangle<double> Rectangle_double;

#endif