//
// Created by petr on 11/1/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURE_H

#include "VulkanObject.h"
#include "configs/TextureConfigs.h"
#include "configs/TextureSamplerConfig.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT Texture : public VulkanObject, public PtrConstructible<Texture> {
 public:
  Texture(std::shared_ptr<LogicalDevice> device, CommandPool &pool, FileTextureConfig &&config);

  [[nodiscard]] std::string info() const override;

  [[nodiscard]] LogicalDevice &getLogicalDevice() const;
  [[nodiscard]] Image &getImage() const;
  [[nodiscard]] std::shared_ptr<TextureSampler> createSampler(TextureSamplerConfig &&config);

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  std::shared_ptr<Image> image;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURE_H
