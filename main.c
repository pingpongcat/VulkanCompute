#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"

 #define COLOR_CHANNELS 4

uint32_t InputData[2][10000];
uint32_t OutputData[1];

void generate(void)
{
    uint32_t maxValue = 0;
    for (uint32_t i = 0; i < 10000; i++)
    {
       for (uint32_t j = 0; j < 10000; j++)
       {
           uint32_t value = InputData[0][i] * InputData[1][j];
           
           if (value > maxValue) maxValue = value;
       }

    }
    OutputData[0] = maxValue;
}

int main(int argc, char const *argv[])
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndComuteQueue();
    CreatePipeline();
    CreateDescriptorSet();
    CreateBuffers(sizeof(InputData), sizeof(OutputData));
    CreateCommandPool();    
    PrepareCommandBuffer();

    for (uint32_t i = 0; i < 10000; i++)
    {
        InputData[0][i] = rand() % 1000;
        InputData[1][i] = rand() % 1000;
    }

    CopyToInputBuffer(InputData, sizeof(InputData));

    double time_spent = 0.0;
    clock_t begin = clock();

    generate();

    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Vectors calulation max result: %d CPU time : %f s.\n", OutputData[0], time_spent);

    OutputData[0] = 0;
    CopyFromOutputBuffer(OutputData, sizeof(OutputData));

    begin = clock();

    Compute();
    CopyFromOutputBuffer(OutputData, sizeof(OutputData));

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Vectors calulation max result: %d GPU time : %f s.\n", OutputData[0], time_spent);



    DestroyPipeline();
    DestroyShaderModule();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
