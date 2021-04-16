#pragma once

#include <vulkan/vulkan.h>

extern VkDevice LogicalDevice;
extern VkQueue ComputingQueue;
extern VkCommandPool ComputeCmdPool;
extern VkDescriptorPool DescriptorPool;

void CreateDeviceAndComuteQueue(void);
void CreateDescriptorPool(void);
void CreateCommandPool(void);
void DestroyCommandPoolAndLogicalDevice(void);

