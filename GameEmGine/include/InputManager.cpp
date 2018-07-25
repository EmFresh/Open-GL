#include "InputManager.h"

void(*InputManager::_keyUp)(int, int), (*InputManager::_keyDown)(int, int), (*InputManager::_keyAll)(int, int, int),
(*InputManager::_mouseButtonPress)(int, int), (*InputManager::_mouseButtonRelease)(int, int),(*InputManager::_mouseButtonAll)(int, int, int);

InputManager::InputManager()
{
	glfwInit();
	glfwSetKeyCallback(glfwGetCurrentContext(), keyUpdate);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouseButtonUpdate);

}

InputManager::~InputManager()
{}

void InputManager::mouseButtonPressCallback(void mouseButton(int button, int mods))
{
	_mouseButtonPress = mouseButton;
}

void InputManager::mouseButtonReleaseCallback(void mouseButton(int button, int mods))
{
	_mouseButtonRelease = mouseButton;
}

void InputManager::mouseButtonUpdate(GLFWwindow *, int button, int state, int mods)
{
	if(state == MOUSE_PRESSED)
		if(_mouseButtonPress != nullptr)
			_mouseButtonPress(button, mods);
	if(state == MOUSE_RELEASED)
		if(_mouseButtonRelease != nullptr)
			_mouseButtonRelease(button, mods);

	if(_mouseButtonAll != nullptr)
		_mouseButtonAll(state, button, mods);
}

void InputManager::keyUpdate(GLFWwindow *, int key, int scancode, int state, int mods)
{
	if(state == KEY_RELEASED) //more of a stroke since release is only called if a key is pressed then released
		if(_keyUp != nullptr)
			_keyUp(key, mods);
	if(state == KEY_PRESSED)  //Key is being Pressed or Heald
		if(_keyUp != nullptr)
			_keyDown(key, mods);
	
	if(_keyAll != nullptr)
		_keyAll(state, key, mods);
}

void InputManager::mouseButtonAllCallback(void mouseButton(int state, int button, int mods))
{
	_mouseButtonAll = mouseButton;
}

Coord2D InputManager::getMouseCursorPosition()
{
	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	return {(float)x,(float)y};
}

void InputManager::keyPressedCallback(void key(int key, int mod))
{
	_keyDown = key;
}

void InputManager::keyReleasedCallback(void key(int key, int mod))
{
	_keyUp = key;
}

void InputManager::keyAllCallback(void key(int state, int key, int mod))
{
	_keyAll = key;
}

