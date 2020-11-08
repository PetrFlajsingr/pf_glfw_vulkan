//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_DESCRIPTORPOOLCONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_DESCRIPTORPOOLCONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
struct PF_GLFW_VULKAN_EXPORT DescriptorPoolConfig {
  vk::DescriptorPoolCreateFlags flags;
  uint32_t maxSets;
  std::vector<vk::DescriptorPoolSize> poolSizes;
};
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_DESCRIPTORPOOLCONFIG_H
