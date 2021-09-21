#include "VulkanRenderer.h"


VulkanRenderer::VulkanRenderer()
{
}

int VulkanRenderer::init(GLFWwindow* newWindow)
{
	window = newWindow;
	try{
		createInstance();
	}
	catch (const std::runtime_error& e) {
		printf("Erro: %s\n", e.what());
		return EXIT_FAILURE;
	}

	return 0;
}

VulkanRenderer::~VulkanRenderer()
{
}

void VulkanRenderer::createInstance()
{
	// Cria informação sobre a aplicação
	// Dados não afetam o programa, servem para conveniencia do dev
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "App Vulkan";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_2;

	// Cria informação para VkInstance
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// Cria lista de Extensões da instância
	std::vector<const char*> instanceExtensions = std::vector<const char*>();

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	// Requesita extensões GLFW
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// Adiciona extensões GLFW à lista de extensões
	for (size_t i = 0; i < glfwExtensionCount; i++) {
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	// Checa extensões da instância são suportadas
	if (!checkInstanceExtensionSupport(&instanceExtensions))
	{
		throw std::runtime_error("VkInstance não suporta extensões requisitadas");
	}

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	// TODO - Validation Layers
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;

	// Cria instância Vulkan
	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Falha ao criar instância Vulkan");
	}
}

bool VulkanRenderer::checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions)
{
	// Busca número de extensões para depois criar array para guardar extensões
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	// Cria lista para extensões
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	for (const auto &checkExtension : *checkExtensions)
	{
		bool hasExtension = false;
		for (const auto &extension : extensions)
		{
			if (strcmp(checkExtension, extension.extensionName))
			{
				hasExtension = true;
				break;
			}
		}
		if (!hasExtension)
		{
			return false;
		}
	}
	return true;
}
