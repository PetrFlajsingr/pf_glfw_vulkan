//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_LOGICALDEVICECONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_LOGICALDEVICECONFIG_H

#include "../fwd.h"
#include <pf_glfw_vulkan/_export.h>
#include <string>
#include <unordered_set>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
struct PF_GLFW_VULKAN_EXPORT LogicalDeviceConfig {
  std::string id;
  vk::PhysicalDeviceFeatures deviceFeatures;
  std::unordered_set<vk::QueueFlagBits> queueTypes;
  bool presentQueueEnabled{};
  std::unordered_set<std::string> requiredDeviceExtensions;
  std::unordered_set<std::string> validationLayers;
  Surface &surface;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_LOGICALDEVICECONFIG_H
