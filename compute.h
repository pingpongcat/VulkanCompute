#pragma once

#include <vulkan/vulkan.h>

extern VkDescriptorSet DescriptorSet;

void PrepareCommandBuffer(void);
void CreateDescriptorSet(void);
int Compute(void);
