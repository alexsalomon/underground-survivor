#ifndef TIMER_H
#define TIMER_H

class Timer
{
	public:
		Timer();
		~Timer();

		void start(unsigned long seconds);
		void stop();
		void pause();
		void resume();
		bool is_running();
		bool is_timeout();

	private:
		unsigned long m_time_left_after_pausing;
		unsigned long m_current_time;
		unsigned long m_begin;
		unsigned long m_end;
		bool m_is_running;
		bool m_is_timeout;
};

#endif