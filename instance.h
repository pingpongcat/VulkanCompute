#if !defined(INSTANCE_H)
#define INSTANCE_H

#include <vulkan/vulkan.h>

extern VkInstance Instance;
extern VkPhysicalDevice PhysicalDevice;

void GetPhysicalDevice(void);
void CreateInstance(void);

#endif // INSTANCE_H
