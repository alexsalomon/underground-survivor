#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
	: m_is_running(false), m_begin(0), m_end(0), m_remaining_time(0)
{
}

Timer::~Timer()
{
}

void Timer::start(unsigned long seconds)
{
	m_begin = (unsigned long)clock() / CLOCKS_PER_SEC; //makes it be seconds instead of miliseconds
	m_end = m_begin + seconds; 
	m_is_running = true;
}

void Timer::pause()
{
	if(m_is_running)
	{
		long remaining_time = m_end - ((unsigned long)clock() / CLOCKS_PER_SEC);

		if(remaining_time > 0)
		{
			m_remaining_time = remaining_time;
		}
		else //timeout
		{
			m_remaining_time = 0;
		}

		m_is_running = false;
	}
}

void Timer::resume()
{
	if(!m_is_running)
	{
		start(m_remaining_time);
	}
}

bool Timer::is_running()
{
	return m_is_running;
}

bool Timer::is_timeout()
{
	bool is_timeout = false;

	if(m_is_running)
	{
		is_timeout = ((unsigned long)clock() / CLOCKS_PER_SEC) >= m_end;

		if(is_timeout)
		{
			m_is_running = false;
		}
	}

	return is_timeout;
}
