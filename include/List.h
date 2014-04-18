#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
	public:
		List();
		~List();

		void insert(T data);
		void remove(T data);
		T search(T data);

	private:
		std::list<T> m_list;
};

#endif