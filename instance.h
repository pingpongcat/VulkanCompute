#pragma once
#include <vulkan/vulkan.h>

extern VkInstance Instance;
extern VkPhysicalDevice PhysicalDevice;

void GetPhysicalDevice();
void CreateInstance();