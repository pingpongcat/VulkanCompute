#include "pipeline.h"
#include "device.h"

VkPipeline Pipeline = VK_NULL_HANDLE;
VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;

VkShaderModule CreateComputeShader(void)
{
    uint8_t shaderData[20000];

    FILE *f = fopen("comp.spv", "rb");

    if (f == NULL)
    {
        printf("Failed to open shader file\n");
        return VK_NULL_HANDLE;
    }

    size_t size = fread(shaderData, 1, sizeof(shaderData), f);
    fclose(f);

    VkShaderModuleCreateInfo createInfo;
    memset(&createInfo, 0, sizeof(createInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = size;
    createInfo.pCode = (uint32_t *)shaderData;

    VkShaderModule handle;
    if (vkCreateShaderModule(LogicalDevice, &createInfo, NULL, &handle))
    {
        printf("Failed to create shader module\n");
        return VK_NULL_HANDLE;
    }

    return handle;
}

void CratePipelineLayout(void)
{
    VkPipelineLayoutCreateInfo createInfo;
    memset(&createInfo, 0, sizeof(createInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;

    if (vkCreatePipelineLayout(LogicalDevice, &createInfo, NULL, &PipelineLayout) != VK_SUCCESS)
    {
        printf("Failed to create pipeline layout\n");
        return;
    }
}

void CreatePipeline(void)
{
    CratePipelineLayout();

    VkComputePipelineCreateInfo pipelineInfo;
    memset(&pipelineInfo, 0, sizeof(pipelineInfo));
    pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    pipelineInfo.layout = PipelineLayout;
    pipelineInfo.basePipelineIndex = -1;
    pipelineInfo.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    pipelineInfo.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    pipelineInfo.stage.pNext = "main";
    pipelineInfo.stage.module = CreateComputeShader();

    if (vkCreateComputePipelines(LogicalDevice, NULL, 1, &pipelineInfo, NULL, &Pipeline) != VK_SUCCESS)
    {
        printf("Failed to create pipeline\n");
        return;
    }
}

void DestroyPipeline()
{
    if (PipelineLayout != VK_NULL_HANDLE)
    {
        vkDestroyPipelineLayout(LogicalDevice, PipelineLayout, NULL);
    }
    if (Pipeline != VK_NULL_HANDLE)
    {
        vkDestroyPipeline(LogicalDevice, Pipeline, NULL);
    }
}