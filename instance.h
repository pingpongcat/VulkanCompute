#pragma once
#include <vulkan/vulkan.h>

extern VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

void GetPhysicalDevice();
void CreateInstance();