// window.cpp

#include <GLFW/glfw3.h>

#include "window.h"
#include "console.h"
#include "init.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Console *console = static_cast<Console *>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
	{
		console->open = !console->open;
	}
}

int openWindow()
{
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "t7gtools", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Set the key callback function */
	Console console{false};
	glfwSetWindowUserPointer(window, &console);
	glfwSetKeyCallback(window, key_callback);

	/* Initialize Game State */
	//init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		if (console.open)
		{
			/* Render the console area */
			glColor3f(0.0f, 0.0f, 0.0f); // Set the color to black
			glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);		 // Bottom-left corner
			glVertex2f(1280.0f, 0.0f);	 // Bottom-right corner
			glVertex2f(1280.0f, 200.0f); // Top-right corner
			glVertex2f(0.0f, 200.0f);	 // Top-left corner
			glEnd();
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}