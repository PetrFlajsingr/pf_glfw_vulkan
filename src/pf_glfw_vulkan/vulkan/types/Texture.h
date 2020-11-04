//
// Created by petr on 11/1/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURE_H

#include "VulkanObject.h"
#include "fwd.h"
#include <filesystem>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
enum class TextureChannels { grey = 1,
                             grey_alpha = 2,
                             rgb = 3,
                             rgb_alpha = 4 };

PF_GLFW_VULKAN_EXPORT vk::Format TextureChannelsToVkFormat(TextureChannels channels);

struct PF_GLFW_VULKAN_EXPORT FileTextureConfig {
  std::filesystem::path path;
  TextureChannels channels;
  uint32_t mipLevels;
  vk::ImageUsageFlags usage;
};

class PF_GLFW_VULKAN_EXPORT Texture : public VulkanObject {
 public:
  Texture(std::shared_ptr<LogicalDevice> device, CommandPool &pool, FileTextureConfig &&config);

  [[nodiscard]] std::string info() const override;

  [[nodiscard]] LogicalDevice &getLogicalDevice() const;
  [[nodiscard]] Image &getImage() const;

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  std::shared_ptr<Image> image;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURE_H
