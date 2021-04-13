#include <vulkan/vulkan.h>
#include "instance.h"

VkInstance Instance = VK_NULL_HANDLE;

void GetPhysicalDevice(){

    uint32_t count = 0;
    if (VkEnumeratePhysicalDevices(Instance, &count, NULL) != VK_SUCCESS)
    {
        printf("Enumerating physical devices failed\n");
        return;
    }
    VkPhysicalDevice devices[count];
    VkEnumeratePhysicalDevices(Instance, &count, devices);

    VkPhysicalDeviceProperties devicesProperties[count];

    for (uint32_t i = 0; i < count; i++)
    {
        VKGetPhysicalDeviceProperties(devices[i], devicesProperties[i]);
    }
    
    uint32_t dedicatedGPU = 0;

    for (uint32_t i = 0; i < count; i++)
    {
        if (devicesProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            dedicatedGPU = i;
    }

    PhysicalDevice = devices[dedicatedGPU];
    
}

void CreateInstance()
{
    VkInstanceCreateInfo createInfo;
    memset(&createInfo, 0, sizof(createInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

   if (vkCreateInstance(Instance, &createInfo, NULL) != VK_SUCCESS)
   {
       printf("Intance creation faied\n");
   } 
}