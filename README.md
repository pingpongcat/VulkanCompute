# VulkanCompute fractal example

Vulkan Compute example based on Udemy course [GPU computing in Vulkan](https://www.udemy.com/course/vulkan-gpu-computing/) by Miloslav Stofa

![Vulkan GPU fractal](http://mzajac.webd.pl/data/fractactal_gpu.png)

Linux 
meson build --reconfigure
cd ./build
ninja

Winows
* install [clang](https://releases.llvm.org/download.html)
* install [meson] (https://github.com/mesonbuild/meson/releases)

meson build --reconfigure --cross-file=cross_file.txt
