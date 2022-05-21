#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace Window 
{
	void INIT();

	struct Settings
	{
		int width;
		int height;
		bool resizable;
		bool fullscreen;
		int monitor;
		int vMode;
	};

	struct Monitor
	{
		GLFWmonitor* monitor;
		int vModeCount;
		const GLFWvidmode* vModes;
		const char* name;
	};

	struct Window
	{
	public:
		std::vector<Monitor> monitors;
		GLFWwindow* window;
		Settings settings;
		const char* settingsPath;

	public:
		Window() = default;
		Window(const char* settingsPath);
		~Window();
		bool create(const char* title);

		void setDefaultSettings();
		bool setMonVidMode(int mon, int videoMode);
		
		void saveSettings();
		bool loadSettings();
	};
}
