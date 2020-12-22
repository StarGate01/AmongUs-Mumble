// For now this is a thin wrapper around the keyboard keys 'A' to 'Z'
// Note that keys have to be capitalized
class Input
{
public:
	void SetKey(char key, bool value);
	bool GetKey(char key);

private:
	bool keyboardKeys['Z' - 'A'] = { 0 };
};

// One instance of this class exists in the program
extern Input inputSingleton;