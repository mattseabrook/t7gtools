#include <GLFW/glfw3.h>

#include "console.h"

void renderConsole(int windowWidth, int windowHeight, int consoleHeight)
{
    // Set the color to black
    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw a rectangle for the console
    glBegin(GL_QUADS);
    glVertex2f(0.0f, consoleHeight); // Bottom-left corner
    glVertex2f(1280, consoleHeight); // Bottom-right corner
    glVertex2f(1280, 0.0f);          // Top-right corner
    glVertex2f(0.0f, 0.0f);          // Top-left corner
    glEnd();

    // TODO: Render console text
}
