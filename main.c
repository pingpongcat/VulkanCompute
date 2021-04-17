#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"

uint32_t InputData[1000];
float OutputData[1000];

int main(int argc, char const *argv[])
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndComuteQueue();
    CreatePipeline();
    CreateDescriptorPool();
    CreateBuffers(sizeof(InputData), sizeof(OutputData));
    CreateDescriptorSet();
    CreateCommandPool();    
    PrepareCommandBuffer();
    Compute();
    DestroyPipeline();
    DestroyShaderModule();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
