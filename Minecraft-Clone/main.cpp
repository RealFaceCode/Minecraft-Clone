#include <iostream>

#include "src/util/Window.h"
#include "src/file/DataPackager.h"
#include "src/util/Input.h"

int main() {

	//auto n = Node::loadNode("data/test.node");
	//n.printNodes();

	Window::INIT();

	Window::Window window("data/settings/window.node");
	window.loadSettings();

	window.create("Clone");

	while (!glfwWindowShouldClose(window.window))
	{
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.window, true);
		}

		if(Input::isKeyPressed(GLFW_KEY_1)) 
		{
			window.setMonVidMode(-1, 1);
		}
		if (Input::isKeyPressed(GLFW_KEY_2))
		{
			window.setMonVidMode(-1, 2);
		}
		if (Input::isKeyPressed(GLFW_KEY_3))
		{
			window.setMonVidMode(-1, 3);
		}
		if (Input::isKeyPressed(GLFW_KEY_4))
		{
			window.setMonVidMode(-1, 4);
		}
		if (Input::isKeyPressed(GLFW_KEY_5))
		{
			window.setMonVidMode(-1, 5);
		}

		Input::reset();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}