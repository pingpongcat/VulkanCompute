cmake_minimum_required(VERSION 3.11.4)

project(VulkanCompute)
add_executable(${PROJECT_NAME} main.c compute.c device.c instance.c)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

set(CMAKE_C_STANDARD 99)