#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

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

    uint32_t dedicatedGPUidx = 0;

    for (uint32_t i = 0; i < count; i++)
    {
        VkPhysicalDeviceProperties devicesProperties;
        vkGetPhysicalDeviceProperties(devices[i], &devicesProperties);
        VkPhysicalDeviceFeatures devicesFeatures;
        vkGetPhysicalDeviceFeatures(devices[i], &devicesFeatures);

        printf("Found device: %s\n", devicesProperties.deviceName);

        if (devicesProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            dedicatedGPUidx = i;
    }

    PhysicalDevice = devices[dedicatedGPUidx];

    PhysicalDevice = devices[0];
}

void CreateInstance()
{
    const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .enabledLayerCount = 1,
        .ppEnabledLayerNames = layers,
    };

   if (vkCreateInstance(&instanceCreateInfo, NULL, &Instance) != VK_SUCCESS)
   {
       printf("Intance creation faied\n");
   } 
}