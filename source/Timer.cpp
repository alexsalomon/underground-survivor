#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
	: m_is_running(false), m_begin(-2), m_end(-1), m_current_time(-2)
{
}

Timer::~Timer()
{
}

void Timer::start(unsigned long seconds)
{
	m_begin = (unsigned long)clock() / CLOCKS_PER_SEC; //makes it be seconds instead of miliseconds
	m_end = m_begin + seconds; 
	m_current_time = m_begin;
	m_is_running = true;
	m_is_timeout = false;
}

void Timer::stop()
{
}

void Timer::pause()
{
	if(m_is_running)
	{
		m_time_left_after_pausing = (m_end - m_current_time);
		m_is_running = false;
	}
	else
	{
		m_time_left_after_pausing = 0;
	}
}

void Timer::resume()
{
	start(m_time_left_after_pausing);
}

bool Timer::is_running()
{
	return m_is_running;
}

bool Timer::is_timeout()
{
	if(m_is_running)
	{
		m_current_time = (unsigned long)clock() / CLOCKS_PER_SEC;
		m_is_timeout = (m_current_time >= m_end);

		if(m_is_timeout)
		{
			m_is_running = false;
		}
	}

	return m_is_timeout;
}
