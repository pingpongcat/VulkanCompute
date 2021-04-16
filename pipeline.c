#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pipeline.h"
#include "device.h"

VkPipeline Pipeline = VK_NULL_HANDLE;
VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
VkShaderModule ShaderModule = VK_NULL_HANDLE;

static size_t fileGetLenght(FILE *file)
{
	size_t lenght;
	size_t currPos = ftell(file);
	fseek(file, 0 , SEEK_END);
	lenght = ftell(file);
	fseek(file, currPos, SEEK_SET);
	return lenght;
}

static void CreateComputeShader(void)
{
    FILE *file = fopen("shader.spv", "rb");

    if (file == NULL)
    {
        printf("Failed to open shader file\n");
        return;
    }

    size_t lenght = fileGetLenght(file);
	const uint32_t *shaderData = (const uint32_t *)calloc(lenght + 1, 1);

	if (!shaderData) {
		printf("Out of memory when reading shader.spv\n");
		fclose(file);
		file = NULL;
		return;
	}

	fread((void *)shaderData,1,lenght,file);
    fclose(file);

    file = NULL;

    VkShaderModuleCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = lenght,
        .pCode = (uint32_t *)shaderData,
    };

    if (vkCreateShaderModule(LogicalDevice, &createInfo, NULL, &ShaderModule))
    {
        printf("Failed to create shader module\n");
        return;
    }

}

static void CratePipelineLayout(void)
{
    VkPipelineLayoutCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    };

    if (vkCreatePipelineLayout(LogicalDevice, &createInfo, NULL, &PipelineLayout) != VK_SUCCESS)
    {
        printf("Failed to create pipeline layout\n");
        return;
    }
}

void CreatePipeline(void)
{
    CratePipelineLayout();
    CreateComputeShader();

    VkComputePipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .layout = PipelineLayout,
        .basePipelineIndex = -1,
        .stage = (VkPipelineShaderStageCreateInfo){
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_COMPUTE_BIT,
            .pName = "main",
            .module = ShaderModule,
        }};

    if (vkCreateComputePipelines(LogicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &Pipeline) != VK_SUCCESS)
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

void DestroyShaderModule()
{
    if (ShaderModule != VK_NULL_HANDLE)
    {
        vkDestroyShaderModule(LogicalDevice, ShaderModule, NULL);
    }
}