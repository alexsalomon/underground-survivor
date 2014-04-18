#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

class GameSettings
{
	#define GAME_NAME "Underground Survivor"

	public:
		virtual ~GameSettings(){  }

		static void set_settings(std::string key, bool value);
		static bool get_settings(std::string key);
		static void toggle_settings(std::string key, bool default_value = false);

		static int get_window_width();
		static void set_window_width(int window_width);
		static int get_window_height();
		static void set_window_height(int window_height);

	private:
		typedef std::map<std::string, bool> SettingsMap;
		typedef std::map<std::string, bool>::iterator MapIterator;
		static SettingsMap m_settings;

		static int m_window_width;
		static int m_window_height;

	public:
		class Debug
		{
			public:
				static const std::string DRAW_BOUNDARIES;
				static const std::string DRAW_PANELS;
				static const std::string DRAW_ENERGY_BARS;
		};

		class SystemOptions
		{
			public:
				static const std::string IS_FULL_SCREEN;
		};
};

#endif