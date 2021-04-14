#include <vulkan/vulkan.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device.h"
#include "compute.h"
#include "instance.h"
#include "pipeline.h"

uint32_t ComputeQueueFamilyIndex;

VkDevice LogicalDevice = VK_NULL_HANDLE;
VkQueue ComputingQueue = VK_NULL_HANDLE;
VkCommandPool ComputeCmdPool = VK_NULL_HANDLE;

void CreateDeviceAndComuteQueue(void)
{
    uint32_t count = 1;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &count, NULL);
    VkQueueFamilyProperties families[count];
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &count, families);

    printf("Found queue families count: %d\n", count);

    ComputeQueueFamilyIndex = 0;
    while ((ComputeQueueFamilyIndex < count) && ((families[ComputeQueueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
    {
        ComputeQueueFamilyIndex++;
    }
    
    if(ComputeQueueFamilyIndex == count)
    {
        printf("Compute family not found\n");
        free(families);
        return;
    }

    float prio = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo;
    memset(&queueCreateInfo, 0, sizeof(queueCreateInfo));
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = ComputeQueueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &prio; 

    VkDeviceCreateInfo deviceCreateInfo;
    memset(&deviceCreateInfo, 0, sizeof(deviceCreateInfo));
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;

    if (vkCreateDevice(PhysicalDevice, &deviceCreateInfo, NULL, &LogicalDevice) != VK_SUCCESS)
    {
        printf("Could not create logical device\n");
        return;
    }

    vkGetDeviceQueue(LogicalDevice, ComputeQueueFamilyIndex, 0, &ComputingQueue);
}

void CreateCommandPool(void)
{
    VkCommandPoolCreateInfo poolCreateInfo;
    memset(&poolCreateInfo, 0, sizeof(poolCreateInfo));
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.queueFamilyIndex = ComputeQueueFamilyIndex;

    if (vkCreateCommandPool(LogicalDevice, &poolCreateInfo, NULL, &ComputeCmdPool) != VK_SUCCESS)
    {
        printf("Failed to create command pool\n");
    }
}

void DestroyCommandPoolAndLogicalDevice(void)
{
    if (ComputeCmdPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(LogicalDevice, ComputeCmdPool, NULL);
    }
    if(LogicalDevice != VK_NULL_HANDLE)
    {
        vkDestroyDevice(LogicalDevice,NULL);
    }
}