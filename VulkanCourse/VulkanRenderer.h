#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

class VulkanRenderer
{
public:
	VulkanRenderer();

	int init(GLFWwindow* newWindow);

	~VulkanRenderer();

private:
	GLFWwindow* window;

	// Componentes Vulkan
	VkInstance instance;


	// Funções Vulkan
	// Create Functions
	void createInstance();

	// Support Functions
	bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
};