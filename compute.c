#include <vulkan/vulkan.h>

#include <string.h>
#include <stdio.h>

#include "compute.h"
#include "device.h"
#include "instance.h"
#include "pipeline.h"

VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;

void PrepareCommandBuffer(void)
{
    VkCommandBufferAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = ComputeCmdPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };

    if (vkAllocateCommandBuffers(LogicalDevice, &allocInfo, &CommandBuffer) != VK_SUCCESS)
    {
        printf("Failed to allocate the buffer");
        return;
    }

    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };

    if(vkBeginCommandBuffer(CommandBuffer, &beginInfo) != VK_SUCCESS)
    {
        printf("Failed to begin the buffer\n");
        return;
    }


    vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, Pipeline);
    vkCmdBindDescriptorSets(CommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, PipelineLayout, 0, 1, &DescriptorSet, 0, NULL);
    vkCmdDispatch(CommandBuffer, 5, 1, 1);
    if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS)
    {
        printf("Failed to end buffer\n");
        return;
    }
}

int Compute(void){

    VkFence fence;
    VkFenceCreateInfo fenceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
    };

    if (vkCreateFence(LogicalDevice, &fenceCreateInfo, NULL, &fence) != VK_SUCCESS)
    {
        printf("Failed to freate a fence\n");
    }

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &CommandBuffer,
    };
    
    if (vkQueueSubmit(ComputingQueue, 1, &submitInfo, fence) != VK_SUCCESS)
    {
        printf("Sumbiting the command bufer failed\n");
        return -1;
    }

    if (vkWaitForFences(LogicalDevice, 1, &fence, VK_TRUE, 1000000000) != VK_SUCCESS)
    {
        printf("Failed to wait for a fence\n");
    }

    vkDestroyFence(LogicalDevice, fence, NULL);

    return 0;
}

void CreateDescriptorSet(void)
{
    CreateDescriptorPool();

    VkDescriptorSetAllocateInfo descriptorSetAllocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorSetCount = 1,
        .pSetLayouts = &DescriptorSetLayeout,
        .descriptorPool = DescriptorPool,
    };

    if (vkAllocateDescriptorSets(LogicalDevice, &descriptorSetAllocInfo, &DescriptorSet) != VK_SUCCESS)
    {
        printf("Failed to allocate the descriptor set\n");
    }

}