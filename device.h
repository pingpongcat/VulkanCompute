#if !defined(DEVICE_H)
#define DEVICE_H

#include <vulkan/vulkan.h>

extern VkDevice LogicalDevice;
extern VkQueue ComputingQueue;
extern VkCommandPool ComputeCmdPool;

void CreateDeviceAndComuteQueue(void);
void CreateCommandPool(void);
void DestroyCommandPoolAndLogicalDevice(void);

#endif // DEVICE_H

