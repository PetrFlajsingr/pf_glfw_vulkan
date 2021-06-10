//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_BUFFERCONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_BUFFERCONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT BufferConfig {
  vk::DeviceSize size;
  vk::BufferUsageFlags usageFlags;
  vk::SharingMode sharingMode;
  std::vector<uint32_t> queueFamilyIndices;
};

struct PF_GLFW_VULKAN_EXPORT BufferMemoryPoolConfig {
  vk::DeviceSize alignment;
  vk::DeviceSize offset = 0;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_BUFFERCONFIG_H
