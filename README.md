# VulkanCompute fractal example

Vulkan Compute example based on Udemy course [GPU computing in Vulkan](https://www.udemy.com/course/vulkan-gpu-computing/) by Miloslav Stofa

![Vulkan GPU fractal](http://mzajac.webd.pl/data/fractactal_gpu.png)

Linux  
meson build
cd ./build
ninja

Winows  
* install [clang](https://releases.llvm.org/download.html)
* install [meson](https://github.com/mesonbuild/meson/releases)

meson build --cross-file=cross_file.txt
