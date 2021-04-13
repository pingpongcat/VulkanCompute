#pragma once

extern VkDevice LogicalDevice;
extern VkQueue ComputingQueue;
extern VkCommandPool ComputeCmdPool;

void CreateDeviceAndComuteQueue(void);
void CreateCommandPool(void);
void DestroyCommandPoolAndLogicalDevice(void);
