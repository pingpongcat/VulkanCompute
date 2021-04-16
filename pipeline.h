#pragma once

#include <vulkan/vulkan.h>

extern VkPipeline Pipeline;
extern VkPipelineLayout PipelineLayout;
extern VkDescriptorSetLayout DescriptorSetLayeout;

void CreatePipeline(void);
void DestroyPipeline(void);
void DestroyShaderModule(void);


