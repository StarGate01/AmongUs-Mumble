#include <Windows.h>
#include <comdef.h>
#include <iostream>
#include "settings.h"

Settings::Settings():
	mumble_exe("C:\\Program Files\\Mumble\\mumble.exe"),
	app("AmongUs-Mumble", "Among Us.exe")
{ }

void Settings::parse()
{
	// Setup argument parser
	app.allow_extras(true);
	app.allow_config_extras(true);
	app.set_config("-c,--config", "config.ini", "Read an INI configuration file", false);
	app.add_option("-m,--mumble", mumble_exe, "Mumble executable path", true);
	// Get arguments from OS
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	// Convert arguments from unicode to narrow
	_bstr_t** argv_bstr = (_bstr_t**)malloc(argc * sizeof(_bstr_t*));
	char** argv_narrow = (char**)malloc(argc * sizeof(char*));
	for (int i = 0; i < argc; i++)
	{
		argv_bstr[i] = new _bstr_t(argv[i]);
		argv_narrow[i] = *argv_bstr[i];
	}
	// Parse arguments
	app.parse(argc, argv_narrow);
	// Free temp buffers
	LocalFree(argv);
	for (int i = 0; i < argc; i++)
	{
		argv_bstr[i]->~_bstr_t();
		free(argv_bstr[i]);
	}
	free(argv_bstr);
	free(argv_narrow);
}

void Settings::print_usage()
{
	std::cout << app.help();
}

void Settings::print_config()
{
	std::cout << app.config_to_str(true, true);
}

Settings app_settings;