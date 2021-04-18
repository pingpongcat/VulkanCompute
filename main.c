#include <stdio.h>
#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"

 #define STB_IMAGE_WRITE_IMPLEMENTATION
 #include "stb_image_write.h"

uint32_t InputData[1000];
float OutputData[1000][1000];

void generate(void)
{
    for (uint32_t row = 0; row < 1000; row++)
    {
        for (uint32_t column = 0; column < 1000; column++)
        {
            float r = (float)row / 500.0 - 1.0;
            float i = (float)column / 500.0 - 1.0;

            uint32_t cnt = 0;
            while ((r * r + i * i < 4.0) && (cnt < 63))
            {
                float temp = r*r - i * i + 0.17;
                i = 2 * r * i + 0.57;
                r = temp;
                cnt++;
            }
            OutputData[row][column] = (cnt << 10) | 0xff000000;
            
        }
        
    }
    
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

    CoppyToInputBuffer(InputData, sizeof(InputData));

    generate();
    stbi_write_bmp("fractactal_cpu.bmp", 1000, 1000, 4, OutputData);    

    Compute();
    CoppyFromOutputBuffer(OutputData, sizeof(OutputData));
    stbi_write_bmp("fractactal_gpu.bmp", 1000, 1000, 4, OutputData);    

    DestroyPipeline();
    DestroyShaderModule();
    DestroyCommandPoolAndLogicalDevice();
    
    return 0;
}
