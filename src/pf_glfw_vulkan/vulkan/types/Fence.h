//
// Created by petr on 10/18/20.
//

#ifndef VOXEL_RENDER_FENCE_H
#define VOXEL_RENDER_FENCE_H

#include <pf_common/concepts/PtrConstructible.h>
#include "VulkanObject.h"
#include "fwd.h"
#include <vulkan/vulkan.hpp>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT FenceConfig {
  vk::FenceCreateFlags flags;
};

class PF_GLFW_VULKAN_EXPORT Fence : public VulkanObject, public PtrConstructible<Fence> {
 public:
  Fence(std::shared_ptr<LogicalDevice> device, FenceConfig &&config);

  void wait() const;
  void reset();

  const vk::Fence &operator*() const;
  vk::Fence const *operator->() const;

  [[nodiscard]] const vk::Fence &getVkFence() const;

  [[nodiscard]] LogicalDevice &getLogicalDevice() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::UniqueFence vkFence;
};

}// namespace pf::vulkan

#endif//VOXEL_RENDER_FENCE_H
