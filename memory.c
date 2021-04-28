#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "compute.h"
#include "device.h"
#include "instance.h"
#include "memory.h"

VkBuffer InputBuffer = VK_NULL_HANDLE;
VkBuffer OutputBuffer = VK_NULL_HANDLE;
VkDeviceMemory InputBufferMemory = VK_NULL_HANDLE;
VkDeviceMemory OutputBufferMemory = VK_NULL_HANDLE;

VkBuffer InputBufferUint1 = VK_NULL_HANDLE;
VkBuffer InputBufferUint2 = VK_NULL_HANDLE;
VkDeviceMemory InputBufferMemory1 = VK_NULL_HANDLE;
VkDeviceMemory InputBufferMemory2 = VK_NULL_HANDLE;

static uint32_t FindMemoryIndexByType(uint32_t allowedTypeMask,
                                      VkMemoryPropertyFlags flags) {
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &memProperties);

  uint32_t typeMask = 1;

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++, typeMask <<= 1) {
    if ((allowedTypeMask & typeMask) != 0) {
      if ((memProperties.memoryTypes[i].propertyFlags & flags) == flags) {
        return i;
      }
    }
  }

  printf("Failed to find memory type index\n");
  return 0;
}

VkBuffer CreateBufferAndMemory(size_t size, VkDeviceMemory *defviceMemory,
                               VkBufferUsageFlagBits usage,
                               VkMemoryPropertyFlagBits memProperties) {
  VkBuffer buffer;
  VkDeviceMemory memory;

  VkBufferCreateInfo bufferInfo = {
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = size,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
      .usage = usage,
  };

  if (vkCreateBuffer(LogicalDevice, &bufferInfo, NULL, &buffer) != VK_SUCCESS) {
    printf("Failed to create buffer\n");
    return VK_NULL_HANDLE;
  }

  VkMemoryRequirements memoryRequirements;
  vkGetBufferMemoryRequirements(LogicalDevice, buffer, &memoryRequirements);

  VkMemoryAllocateInfo memoryAllocInfo = {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .allocationSize = memoryRequirements.size,
      .memoryTypeIndex = FindMemoryIndexByType(
          memoryRequirements.memoryTypeBits, memProperties),
  };

  if (vkAllocateMemory(LogicalDevice, &memoryAllocInfo, NULL, &memory) !=
      VK_SUCCESS) {
    printf("Failed to allocate mamory for the buffer\n");
    vkDestroyBuffer(LogicalDevice, buffer, NULL);
    return VK_NULL_HANDLE;
  }

  if (vkBindBufferMemory(LogicalDevice, buffer, memory, 0) != VK_SUCCESS) {
    printf("Failed to bind buffer and memmory\n");

    vkDestroyBuffer(LogicalDevice, buffer, NULL);
    return VK_NULL_HANDLE;
  }

  *defviceMemory = memory;
  return buffer;
}

void CreateBuffers(size_t inputSize, size_t outputSize, uint32_t inputSizeUin1, uint32_t inputSizeUin2)
{
  InputBuffer = CreateBufferAndMemory(inputSize, &InputBufferMemory,
                                      VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                      VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  OutputBuffer = CreateBufferAndMemory(outputSize, &OutputBufferMemory,
                                       VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

  InputBufferUint1 = CreateBufferAndMemory(inputSizeUin1, &InputBufferMemory1,
                                      VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                                      VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  InputBufferUint2 = CreateBufferAndMemory(inputSizeUin2, &InputBufferMemory2,
                                      VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                                      VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  VkWriteDescriptorSet writeDescriptorSet[2] = {
    {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = DescriptorSet,
      .dstBinding = 0,
      .descriptorCount = 2,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .pBufferInfo = (VkDescriptorBufferInfo[2]){
        {
          .buffer = InputBuffer,
          .offset = 0,
          .range = inputSize
        },
        {
          .buffer = OutputBuffer,
          .offset = 0,
          .range = outputSize
        }
      }
    },
    {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = DescriptorSet,
      .dstBinding = 2,
      .descriptorCount = 2,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .pBufferInfo = (VkDescriptorBufferInfo[2]){
        {
          .buffer = InputBufferUint1,
          .offset = 0,
          .range = inputSizeUin1
        },
        {
          .buffer = InputBufferUint2,
          .offset = 0,
          .range = inputSizeUin2
        }
      }
    },
    };

  vkUpdateDescriptorSets(LogicalDevice, 2, writeDescriptorSet, 0, NULL);
}

static void CopyData(void *data, size_t size, bool isWrite,
                      VkDeviceMemory memory) {
  void *adress;
  if (vkMapMemory(LogicalDevice, memory, 0, size, 0, &adress) != VK_SUCCESS) {
    printf("Failed to map buffer memory\n");
    return;
  }

  isWrite ? memcpy(adress, data, size) : memcpy(data, adress, size);

  vkUnmapMemory(LogicalDevice, memory);
}

void CopyBufferToBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, size_t size)
{
  VkCommandBuffer cmdBuffer;

  VkCommandBufferAllocateInfo cmdBuffAllocInfo = {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    .commandPool = ComputeCmdPool,
    .commandBufferCount = 1
  };

  vkAllocateCommandBuffers(LogicalDevice, &cmdBuffAllocInfo, &cmdBuffer);

  VkCommandBufferBeginInfo cmdBufferBegin = {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
  };

  vkBeginCommandBuffer(cmdBuffer, &cmdBufferBegin);

  VkBufferCopy buffCopy = {
    .srcOffset = 0,
    .dstOffset = 0,
    .size = size
  };

  vkCmdCopyBuffer(cmdBuffer, srcBuffer, dstBuffer, 1, &buffCopy);
  vkEndCommandBuffer(cmdBuffer);

  VkSubmitInfo submitInfo = {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .commandBufferCount = 1,
    .pCommandBuffers = &cmdBuffer,
  };

  vkQueueSubmit(ComputingQueue, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(ComputingQueue);
  vkFreeCommandBuffers(LogicalDevice, ComputeCmdPool, 1, &cmdBuffer);
}

void CopyToLocalBuffer(void *data, size_t size, VkBuffer buffer)
{
    VkDeviceMemory tempMemory;
    VkBuffer tempBuffer = CreateBufferAndMemory(size, &tempMemory,
    VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    CopyData(data, size, 1, tempMemory);

    CopyBufferToBuffer(tempBuffer, buffer, size);

    vkDestroyBuffer(LogicalDevice, tempBuffer, NULL);
    vkFreeMemory(LogicalDevice, tempMemory, NULL);
}

void DestroyBuffers(void) {
  vkDestroyBuffer(LogicalDevice, InputBuffer, NULL);
  vkFreeMemory(LogicalDevice, InputBufferMemory, NULL);
  vkDestroyBuffer(LogicalDevice, OutputBuffer, NULL);
  vkFreeMemory(LogicalDevice, OutputBufferMemory, NULL);

  vkDestroyBuffer(LogicalDevice, InputBufferUint1, NULL);
  vkFreeMemory(LogicalDevice, InputBufferMemory1, NULL);
  vkDestroyBuffer(LogicalDevice, InputBufferUint2, NULL);
  vkFreeMemory(LogicalDevice, InputBufferMemory2, NULL);
}

void CopyToInputBuffer(void *data, size_t size) {
  CopyToLocalBuffer(data, size, InputBuffer);
}

void CopyFromOutputBuffer(void *data, size_t size) {
  CopyData(data, size, false, OutputBufferMemory);
}
//Uniform
void CopyToInputBufferUni1(void *data, size_t size) {
  CopyToLocalBuffer(data, size, InputBufferUint1);
}
void CopyToInputBufferUni2(void *data, size_t size) {
  CopyToLocalBuffer(data, size, InputBufferUint2);
}