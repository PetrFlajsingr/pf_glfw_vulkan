//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_TEXTURECONFIGS_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_TEXTURECONFIGS_H

#include <filesystem>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
enum class TextureChannels { grey = 1, grey_alpha = 2, rgb = 3, rgb_alpha = 4 };

PF_GLFW_VULKAN_EXPORT vk::Format TextureChannelsToVkFormat(TextureChannels channels);

struct PF_GLFW_VULKAN_EXPORT FileTextureConfig {
  std::filesystem::path path;
  TextureChannels channels;
  uint32_t mipLevels;
  vk::ImageUsageFlags usage;
};
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_TEXTURECONFIGS_H
