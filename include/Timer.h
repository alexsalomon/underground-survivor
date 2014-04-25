#ifndef TIMER_H
#define TIMER_H

class Timer
{
	public:
		Timer();
		~Timer();

		void start(unsigned long seconds);
		void pause();
		void resume();
		bool is_running();
		bool is_timeout();

	private:
		unsigned long m_begin;
		unsigned long m_end;
		unsigned long m_remaining_time;
		bool m_is_running;
};

#endif