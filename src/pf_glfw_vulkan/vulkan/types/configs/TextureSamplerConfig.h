//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_TEXTURESAMPLERCONFIG_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_TEXTURESAMPLERCONFIG_H

#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT TextureSamplerConfig {
    vk::Filter magFilter;
    vk::Filter minFilter;
    struct {
      vk::SamplerAddressMode u;
      vk::SamplerAddressMode v;
      vk::SamplerAddressMode w;
    } addresssMode;
    std::optional<float> maxAnisotropy;
    vk::BorderColor borderColor;
    bool unnormalizedCoordinates;
    std::optional<vk::CompareOp> compareOp;
    struct {
      vk::SamplerMipmapMode mode;
      float lodBias;
      float minLod;
      float maxLod;
    } mip;
};

}

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_TEXTURESAMPLERCONFIG_H
