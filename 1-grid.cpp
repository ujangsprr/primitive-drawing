#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE); // close program on ESC key
}

void setup_viewport(GLFWwindow* window)
{
	// setting viewports size, projection etc
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-17, 17, -17, 17, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void grid(int row, int col)
{
	int i;

	int left = -col / 2;
	int right = col / 2;
	int bottom = -row / 2;
	int top = row / 2;

	glBegin(GL_LINES);
	glLineWidth(1);

	for (i = 0; i < row + 1; i++)
	{
		glVertex2f(left, row / 2 - i);
		glVertex2f(right, row / 2 - i);
	}

	for (i = 0; i < col + 1; i++)
	{
		glVertex2f(col / 2 - i, bottom);
		glVertex2f(col / 2 - i, top);
	}

	glLineWidth(3);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(left, 0);
	glVertex2f(right, 0);
	glVertex2f(0, bottom);
	glVertex2f(0, top);

	glEnd();
}

void display()
{
	glColor3ub(255, 255, 255);
	grid(20, 20);
}

int main(void) {
	GLFWwindow* window;
	if (!glfwInit()) exit(EXIT_FAILURE);

	window = glfwCreateWindow(720, 720, "Graphic Grid (x,y)", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POINT_SMOOTH);

	while (!glfwWindowShouldClose(window))
	{
		setup_viewport(window);

		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
