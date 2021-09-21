#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "VulkanRenderer.h"

GLFWwindow* window;
VulkanRenderer vulkanRenderer;

void initWindow(std::string wName = "Janel de teste", const int width = 800, const int height = 600)
{
	// Inicializa GLFW
	glfwInit();

	// Set GLFW to NOT work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main()
{
	// Cria janela
	initWindow("Janela de Teste", 800, 600);

	// Cria instância de Vulkan Renderer
	if (vulkanRenderer.init(window) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	// Cria loop até input para fechar janela
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}