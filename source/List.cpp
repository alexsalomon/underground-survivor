#include "stdafx.h"
#include "List.h"

template <class T>
List<T>::List()
	: m_list()
{
}

template <class T>
List<T>::~List()
{
}

template <class T>
void List<T>::insert(T data)
{
	m_list.insert(data);
}

template <class T>
void List<T>::remove(T data)
{
	m_list.remove(data);
}

template <class T>
T List<T>::search(T data)
{
	list<T>::iterator found = find_if( m_list.begin(), m_list.end(), data );
	if(found)
	{
		return found->second;
	}

	return NULL;
}
