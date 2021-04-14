#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <string.h>

extern VkPipeline Pipeline;
extern VkPipelineLayout PipelineLayout;

void DestroyPipeline(void);
void CreatePipeline(void);