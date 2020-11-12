#pragma once

#include <string>
#include "CLI11.hpp"

class Settings
{
	public:
		std::string mumble_exe;
		bool noConsole;

		Settings();
		void parse();
		void print_usage();
		void print_config();

	private:
		CLI::App app;
};

extern Settings app_settings;
