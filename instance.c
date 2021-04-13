#include <vulkan/vulkan.h>
#include <stdio.h>
#include <string.h>
#include "instance.h"

VkInstance Instance = VK_NULL_HANDLE;
VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

void GetPhysicalDevice(){

    uint32_t count = 0;
    if (vkEnumeratePhysicalDevices(Instance, &count, NULL) != VK_SUCCESS)
    {
        printf("Enumerating physical devies failes");
        return;
    }

    VkPhysicalDevice devices[count];
    vkEnumeratePhysicalDevices(Instance, &count, devices);

    VkPhysicalDeviceProperties devicesProperties[count];

    for (uint32_t i = 0; i < count; i++)
    {
        vkGetPhysicalDeviceProperties(devices[i], devicesProperties);
    }
    
    uint32_t dedicatedGPUidx = 0;

    for (uint32_t i = 0; i < count; i++)
    {
        if (devicesProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            dedicatedGPUidx = i;
    }

    PhysicalDevice = devices[dedicatedGPUidx];
    
}

void CreateInstance()
{
    const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
    VkInstanceCreateInfo instanceCreateInfo;
    memset(&instanceCreateInfo, 0, sizeof(instanceCreateInfo));
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.enabledLayerCount = 1;
    instanceCreateInfo.ppEnabledLayerNames = layers;

   if (vkCreateInstance(&instanceCreateInfo, NULL, &Instance) != VK_SUCCESS)
   {
       printf("Intance creation faied\n");
   } 
}