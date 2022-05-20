#pragma once
#include <GLFW/glfw3.h>

namespace Input
{
	extern bool keysPressed[GLFW_KEY_LAST];
	extern bool keysReleased[GLFW_KEY_LAST];
	extern bool mouseButtonsPressed[GLFW_MOUSE_BUTTON_LAST];
	extern bool mouseButtonsReleased[GLFW_MOUSE_BUTTON_LAST];
	extern bool joystick[GLFW_JOYSTICK_LAST];

	extern int mouseX;
	extern int mouseY;
	extern int scrollDir;

	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
	bool isButtonPressed(int button);
	bool isButtonReleased(int button);
	bool isScrollUp();
	bool isScrollDown();

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	void reset();
}