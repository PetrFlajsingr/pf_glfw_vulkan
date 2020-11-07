//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_INSTANCECONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_INSTANCECONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <unordered_set>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT InstanceConfig {
  std::string appName;
  Version appVersion;
  Version vkVersion;
  EngineInfo engineInfo;
  std::unordered_set<std::string> requiredWindowExtensions;
  std::unordered_set<std::string> validationLayers;

  std::optional<VulkanDebugCallback> callback;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_INSTANCECONFIG_H
