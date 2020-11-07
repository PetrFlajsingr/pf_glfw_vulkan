//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_DESCRIPTORSETLAYOUTCONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_DESCRIPTORSETLAYOUTCONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT DescriptorSetLayoutBindingConfig {
  uint32_t binding;
  vk::DescriptorType type;
  uint32_t count;
  vk::ShaderStageFlags stageFlags;
};

struct PF_GLFW_VULKAN_EXPORT DescriptorSetLayoutConfig {
  std::vector<DescriptorSetLayoutBindingConfig> bindings;
};
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_DESCRIPTORSETLAYOUTCONFIG_H
