//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_SWAPCHAINCONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_SWAPCHAINCONFIG_H

#include "../../../concepts/Window.h"
#include <pf_glfw_vulkan/_export.h>
#include <set>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT SwapChainConfig {
  std::set<vk::SurfaceFormatKHR> formats;
  std::set<vk::PresentModeKHR> presentModes;
  ui::Resolution resolution;
  vk::ImageUsageFlags imageUsage;
  std::unordered_set<uint32_t> sharingQueues;
  uint32_t imageArrayLayers;
  bool clipped;
  std::optional<vk::SwapchainKHR> oldSwapChain;
  vk::CompositeAlphaFlagBitsKHR compositeAlpha;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_SWAPCHAINCONFIG_H
