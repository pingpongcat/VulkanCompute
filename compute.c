#include <string.h>
#include <stdio.h>
#include <vulkan/vulkan.h>
#include "compute.h"
#include "device.h"
#include "instance.h"
#include "pipeline.h"

VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;

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
    vkCmdDispatch(CommandBuffer, 1, 1, 1);
    if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS)
    {
        printf("Failed to end buffer\n");
        return;
    }
}

int Compute(void){

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &CommandBuffer,
    };
    
    if (vkQueueSubmit(ComputingQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
    {

        printf("Sumbiting the command bufer failed\n");
        return -1;
    }
    return 0;
}