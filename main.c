#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"

int main(int argc, char const *argv[])
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndComuteQueue();
    CreatePipeline();
    CreateDescriptorPool();
    CreateDescriptorSet();
    CreateCommandPool();    
    PrepareCommandBuffer();
    Compute();
    DestroyPipeline();
    DestroyShaderModule();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
