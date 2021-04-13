cmake_minimum_required(VERSION 3.11.4)

project(VulkanCompute)
add_executable(${PROJECT_NAME} main.c compute.c device.c instance.c)

find_package(Vulkan)
#link_libraries(${Vulkan_LIBRARY})
target_link_libraries(${PROJECT_NAME} vulkan)
#include_directories(${Vulkan_INCLUDE_DIRS})
#target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})



#set(DEPENDENCY_DIR ${CMAKE_SOURCE_DIR}/external)
#set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glfw/include/")
#set(GLFW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/external/glfw/lib/")

set(CMAKE_C_STANDARD 99)