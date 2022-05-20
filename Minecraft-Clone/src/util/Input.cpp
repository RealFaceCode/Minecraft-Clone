#include "Input.h"

namespace Input
{
	bool keysPressed[GLFW_KEY_LAST]						= {};
	bool keysReleased[GLFW_KEY_LAST]					= {};
	bool mouseButtonsPressed[GLFW_MOUSE_BUTTON_LAST]	= {};
	bool mouseButtonsReleased[GLFW_MOUSE_BUTTON_LAST]	= {};
	bool joystick[GLFW_JOYSTICK_LAST]					= {};

	int mouseX		= 0;
	int mouseY		= 0;
	int scrollDir = 0;

	bool isKeyPressed(int key)
	{
		if (key > GLFW_KEY_LAST)
		{
			return false;
		}

		return keysPressed[key];
	}

	bool isKeyReleased(int key)
	{
		if (key > GLFW_KEY_LAST)
		{
			return false;
		}

		return keysReleased[key];
	}

	bool isButtonPressed(int button)
	{
		if (button > GLFW_MOUSE_BUTTON_LAST)
		{
			return false;
		}

		return mouseButtonsPressed[button];
	}

	bool isButtonReleased(int button)
	{
		if (button > GLFW_MOUSE_BUTTON_LAST)
		{
			return false;
		}

		return mouseButtonsReleased[button];
	}

	bool isScrollUp()
	{
		return scrollDir == 1;
	}

	bool isScrollDown()
	{
		return scrollDir == -1;
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keysPressed[key] = true;
		}
		
		if (action == GLFW_RELEASE)
		{
			keysPressed[key]	= false;
			keysReleased[key]	= true;
		}
	}

	void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseX = xpos;
		mouseY = ypos;
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			mouseButtonsPressed[button] = true;
		}

		if (action == GLFW_RELEASE)
		{
			mouseButtonsPressed[button] = false;
			mouseButtonsReleased[button] = true;
		}
	}

	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		scrollDir = yoffset;
	}

	void reset()
	{
		scrollDir = 0;
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			keysReleased[i] = false;
		}

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
			mouseButtonsReleased[i] = false;
		}
	}
}

