#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.c"

int main(int argc, char const *argv[])
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndComuteQueue();
    CreatePipeline();
    CreateCommandPool();    
    PrepareCommandBuffer();
    Compute();
    DestroyPipeline();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
