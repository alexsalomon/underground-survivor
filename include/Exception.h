#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class Exception : public std::exception
{
	public:
		Exception(const std::string& message = "") : m_message(message){ }
		virtual ~Exception(){ }
		const char* what() const{ return m_message.c_str(); }

		std::string m_message;
};

#endif