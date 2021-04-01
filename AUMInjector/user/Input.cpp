#include "Input.h"

ModInput inputSingleton;

// Expects input of 'A' to 'Z'
void ModInput::SetKey(char key, bool value)
{
	keyboardKeys[key - 'A'] = value;
}

// Expects input of 'A' to 'Z'
bool ModInput::GetKey(char key)
{
	return keyboardKeys[key - 'A'];
}
