//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_COMMANDBUFFERCONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_COMMANDBUFFERCONFIG_H

#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT CommandBufferConfig {
  vk::CommandBufferLevel level;
  uint32_t count;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_COMMANDBUFFERCONFIG_H
