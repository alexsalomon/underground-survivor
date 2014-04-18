#ifndef APPLICATION_H
#define APPLICATION_H

class MainWindow;
class Application
{
	static const int FRAME_TIME = 50;

	public:
		Application();
		~Application();
		void initialize_game_settings();
		void run();

	private:
		void create_window();
		void set_up_next_deadline();
		void send_message_to_be_processed_by_the_appropriate_window(MSG* Message) const;
		bool should_application_be_updated() const;
		void update_application_if_necessary(bool update);	
		void recalculate_sleeping_time_and_next_deadline();

		MainWindow* m_mainWindow;
		DWORD m_next_deadline;
		DWORD m_sleeping_time;
};

#endif
