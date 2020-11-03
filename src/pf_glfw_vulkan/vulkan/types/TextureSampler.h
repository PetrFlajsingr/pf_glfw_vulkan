//
// Created by petr on 11/1/20.
//

#ifndef REALISTIC_VOXEL_RENDERING_VULKAN_TYPES_TEXTURESAMPLER_H
#define REALISTIC_VOXEL_RENDERING_VULKAN_TYPES_TEXTURESAMPLER_H

#include "VulkanObject.h"
#include "fwd.h"
#include <vulkan/vulkan.hpp>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT TextureSamplerConfig {
  vk::Filter magFilter;
  vk::Filter minFilter;
  struct {
    vk::SamplerAddressMode u;
    vk::SamplerAddressMode v;
    vk::SamplerAddressMode w;
  }addresssMode;
  std::optional<float> maxAnisotropy;
  vk::BorderColor borderColor;
  bool unnormalizedCoordinates;
  std::optional<vk::CompareOp> compareOp;
  struct {
    vk::SamplerMipmapMode mode;
    float lodBias;
    float minLod;
    float maxLod;
  }mip;
};

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
#endif//REALISTIC_VOXEL_RENDERING_VULKAN_TYPES_TEXTURESAMPLER_H
