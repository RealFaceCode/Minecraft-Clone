#include "Window.h"
#include "../file/DataPackager.h"
#include "../file/BasicFileHandling.h"
#include "Input.h"

namespace Window
{

	Window::Window(const char* settingsPath)
		:settings(Settings{0, 0, false, false, -1, -1}), window(nullptr), settingsPath(settingsPath)
	{
		int count;
		GLFWmonitor** m = glfwGetMonitors(&count);

		for (int i = 0; i < count; i++)
		{
			Monitor monitor;
			monitor.monitor = m[i];
			monitor.vModes	= glfwGetVideoModes(m[i], &monitor.vModeCount);
			monitor.name	= glfwGetMonitorName(m[i]);
			monitors.emplace_back(monitor);
		}
	}

	Window::~Window()
	{
		saveSettings();
	}

	bool Window::create(const char* title)
	{
	Monitor* monPtr = &monitors.at(0);
		GLFWmonitor* mon = nullptr;

		if (settings.monitor != -1) {
			if (settings.monitor >= monitors.size())
			{
				settings.monitor = monitors.size() - 1;
			}
			monPtr = &monitors.at(settings.monitor);
			mon = monPtr->monitor;
		}

		if(settings.vMode != -1)
		{
			if (settings.vMode >= monPtr->vModeCount)
			{
				settings.vMode = monPtr->vModeCount - 1;
			}

			const GLFWvidmode* vMod = &monPtr->vModes[settings.vMode];

			settings.width = vMod->width;
			settings.height = vMod->height;

			glfwWindowHint(GLFW_RED_BITS, vMod->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, vMod->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, vMod->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, vMod->refreshRate);

		}
		
		window = glfwCreateWindow(settings.width, settings.height, title, mon, nullptr);
		if (window == nullptr)
		{
			return false;
		}

		glfwMakeContextCurrent(window);

		glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
		glfwSetCursorPosCallback(window, Input::CursorPositionCallback);
		glfwSetKeyCallback(window, Input::KeyCallback);
		glfwSetScrollCallback(window, Input::ScrollCallback);

		if (glewInit() != GLEW_OK) {
			return false;
		}

		return true;
	}

	void Window::setDefaultSettings()
	{
		settings.width = 720;
		settings.height = 480;
		settings.fullscreen = 0;
		settings.resizable = 0;
		settings.monitor = -1;
		settings.vMode = -1;
	}

	bool Window::setMonVidMode(int mon, int videoMode)
	{
		if (mon == -1)
		{
			if (videoMode >= monitors[0].vModeCount)
			{
				return false;
			}
			glfwSetWindowMonitor(window, nullptr, 100, 100, monitors[0].vModes[videoMode].width, monitors[0].vModes[videoMode].height, monitors[0].vModes[videoMode].refreshRate);
			settings.vMode = videoMode;
			return true;
		}
		
		if (mon >= monitors.size())
		{
			return false;
		}

		if (videoMode >= monitors[mon].vModeCount)
		{
			return false;
		}
		glfwSetWindowMonitor(window, monitors[mon].monitor, 100, 100, monitors[mon].vModes[videoMode].width, monitors[mon].vModes[videoMode].height, monitors[mon].vModes[videoMode].refreshRate);

		settings.vMode		= videoMode;
		settings.monitor	= mon;

		return true;
	}

	void Window::saveSettings()
	{
		Node win;
		win["window"]["settings"]["width"]		= settings.width;
		win["window"]["settings"]["height"]		= settings.height;
		win["window"]["settings"]["fullscreen"] = settings.fullscreen;
		win["window"]["settings"]["resizable"]	= settings.resizable;
		win["window"]["settings"]["monitor"]	= settings.monitor;
		win["window"]["settings"]["vMode"]		= settings.vMode;

		win.write(settingsPath);
	}

	bool Window::loadSettings()
	{
		if (!checkExistFile(settingsPath))
		{
			setDefaultSettings();
			return false;
		}

		Node win = Node::loadNode(settingsPath);

		settings.width		= win["window"]["settings"]["width"].getAsInt(0);
		settings.height		= win["window"]["settings"]["height"].getAsInt(0);
		settings.fullscreen = win["window"]["settings"]["fullscreen"].getAsInt(0);
		settings.resizable	= win["window"]["settings"]["resizable"].getAsInt(0);
		settings.monitor	= win["window"]["settings"]["monitor"].getAsInt(0);
		settings.vMode		= win["window"]["settings"]["vMode"].getAsInt(0);

		return true;
	}

	void INIT()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			return;
		}
	}

}
