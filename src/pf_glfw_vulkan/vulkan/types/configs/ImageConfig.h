//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_IMAGECONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_IMAGECONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <unordered_set>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
struct PF_GLFW_VULKAN_EXPORT ImageConfig {
  vk::ImageType imageType;
  vk::Format format;
  vk::Extent3D extent;
  uint32_t mipLevels;
  uint32_t arrayLayers;
  vk::SampleCountFlagBits sampleCount;
  vk::ImageTiling tiling;
  vk::ImageUsageFlags usage;
  std::unordered_set<uint32_t> sharingQueues;
  vk::ImageLayout layout;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_IMAGECONFIG_H
