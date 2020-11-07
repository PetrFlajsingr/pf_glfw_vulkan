//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_FENCECONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_FENCECONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT FenceConfig {
  vk::FenceCreateFlags flags;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_FENCECONFIG_H
