//
// Created by petr on 11/1/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURESAMPLER_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURESAMPLER_H

#include "VulkanObject.h"
#include "configs/TextureSamplerConfig.h"
#include "fwd.h"
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT TextureSampler : public VulkanObject {
 public:
  TextureSampler(std::shared_ptr<LogicalDevice> device, TextureSamplerConfig &&config);

  [[nodiscard]] std::string info() const override;
  [[nodiscard]] LogicalDevice &getLogicalDevice() const;
  [[nodiscard]] const vk::Sampler &getVkSampler() const;

  const vk::Sampler &operator*();
  vk::Sampler const *operator->();

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::UniqueSampler vkSampler;
};
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_TEXTURESAMPLER_H
