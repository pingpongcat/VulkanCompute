#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <string.h>

extern VkPipeline Pipeline;
extern VkPipelineLayout PipelineLayout;

void CreatePipeline(void);
void DestroyPipeline(void);