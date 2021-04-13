#include "compute.h"
#include "instance.h"
#include "device.h"

int main(int argc, char const *argv[])
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndComuteQueue();
    CreateCommandPool();    
    PrepareCommandBuffer();
    Compute();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
