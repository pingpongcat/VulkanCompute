#include <stdio.h>
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
    //CreateDescriptorPool();
    CreateDescriptorSet();
    CreateBuffers(sizeof(InputData), sizeof(OutputData));
    CreateCommandPool();    
    PrepareCommandBuffer();

    for (size_t i = 0; i < 1000; i++)
    {
        InputData[i] = i;
        OutputData[i] = 0;
    }
    
    CoppyToInputBuffer(InputData, sizeof(InputData));

    Compute();

    CoppyFromOutputBuffer(OutputData, sizeof(OutputData));

    for (size_t i = 0; i < 1000; i += 50)
    {
        printf("%u -> %f\n", InputData[i], OutputData[i]);
    }

    DestroyPipeline();
    DestroyShaderModule();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
