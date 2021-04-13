cmake_minimum_required(VERSION 3.11.4)

project(VulkanCompute)
add_executable(${PROJECT_NAME} main.c compute.c device.c instance.c)

find_package(Vulkan)

target_link_libraries(${PROJECT_NAME} vulkan)

#link_libraries(${Vulkan_LIBRARY})
#include_directories(${Vulkan_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 99)