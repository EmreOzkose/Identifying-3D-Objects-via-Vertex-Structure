
#include<stdio.h>
#include <iostream>


int main()
{
	std::cout << "dasasd";
}
/*int main(void)
{
	glewInit();
	glfwSetErrorCallback(error_callback); //Error callback
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);

	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);



		int width, height;
		double startTime = glfwGetTime();
		double lastTime = 0;

		//Set cursor position to middle
		glfwGetWindowSize(window, &width, &height);

		glfwMakeContextCurrent(window);

		glfwPollEvents();
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow *window)
{
		float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
}*/