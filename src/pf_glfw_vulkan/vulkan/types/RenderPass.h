//
// Created by petr on 9/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_RENDERPASS_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_RENDERPASS_H

#include "VulkanObject.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
class RenderPassBuilder;
class PF_GLFW_VULKAN_EXPORT RenderPass : public VulkanObject, public PtrConstructible<RenderPass> {
 public:
  friend class RenderPassBuilder;
  RenderPass(RenderPassBuilder &builder, std::shared_ptr<LogicalDevice> device);

  RenderPass(const RenderPass &other) = delete;
  RenderPass &operator=(const RenderPass &other) = delete;

  [[nodiscard]] const vk::RenderPass &getRenderPass() const;
  [[nodiscard]] LogicalDevice &getLogicalDevice() const;

  const vk::RenderPass &operator*() const;
  vk::RenderPass const *operator->() const;

  [[nodiscard]] std::string info() const override;

 private:
  vk::UniqueRenderPass vkRenderPass;
  std::vector<std::string> subPassNames;
  std::shared_ptr<LogicalDevice> logicalDevice;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_RENDERPASS_H
