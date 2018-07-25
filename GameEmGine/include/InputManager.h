#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "StructInfo.h"

/***Enums***/

enum  KeyState
{
	KEY_RELEASED,
	KEY_PRESSED,
	KEY_HELD
};

enum ModKey
{
	MOD_SHIFT = 1,
	MOD_CONTROL = 2,
	MOD_ALT = 4,
	MOD_SUPER = 8
};

enum MouseState
{
	MOUSE_RELEASED,
	MOUSE_PRESSED
};

enum MouseButton
{
	MOUSE_BUTTON_1,
	MOUSE_BUTTON_2,
	MOUSE_BUTTON_3,
	MOUSE_BUTTON_4,
	MOUSE_BUTTON_5,
	MOUSE_BUTTON_6,
	MOUSE_BUTTON_7,
	MOUSE_BUTTON_8,

	LEFT_BUTTON = 1,
	RIGHT_BUTTON = 2,
	MIDDLE_BUTTON = 3,
	LAST_BUTTON = 7
};

/***Structs***/

struct XboxController
{
	union Sticks
	{
		float LSx, LSy, RSx, RSy;
		const float* sticks;
	}sticks;
	union Buttons
	{
		char A, B, X, Y, LB, RB, LSB, RSB;
		const unsigned char* buttons;
	}buttons;

	int numSticks, numButtons;
};

/***Class***/

class InputManager
{
public:

	InputManager();
	~InputManager();

	void mouseButtonPressCallback(void mouseButton(int button, int mods));
	void mouseButtonReleaseCallback(void mouseButton(int button, int mods));
	void mouseButtonAllCallback(void mouseButton(int state, int button, int mods));

	Coord2D getMouseCursorPosition();
	/*
	Callback for whenever any key is pressed or held
	*/
	void keyPressedCallback(void key(int key, int mod));
	/*
	Callback for whenever any key is released
	*/
	void keyReleasedCallback(void key(int key, int mod));
	 /*
	 Callback for any key pressed or released
	 */
	void keyAllCallback(void key(int state, int key, int mod));

	void getControllers();

private:
	static void mouseButtonUpdate(GLFWwindow *, int button, int action, int mods);
	static void keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods);
	static void(*_keyUp)(int, int), (*_keyDown)(int, int), (*_keyAll)(int, int, int),
		(*_mouseButtonPress)(int, int), (*_mouseButtonRelease)(int, int), (*_mouseButtonAll)(int, int, int);
};

