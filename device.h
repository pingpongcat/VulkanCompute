#pragma once

extern VkDevice LogicalDevice = VK_NULL_HANDLE;
extern VkQueue ComputingQueue = VK_NULL_HANDLE;
extern VkCommandPool ComputeCmdPool = VK_NULL_HANDLE;

void CreateDeviceAndComuteQueue(void);
void CreateCommandPool(void);
void DestroyCommandPoolAndLogicalDevice(void);
