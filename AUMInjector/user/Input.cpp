#include "Input.h"

Input inputSingleton;

// Expects input of 'A' to 'Z'
void Input::SetKey(char key, bool value)
{
	keyboardKeys[key - 'A'] = value;
}

// Expects input of 'A' to 'Z'
bool Input::GetKey(char key)
{
	return keyboardKeys[key - 'A'];
}
