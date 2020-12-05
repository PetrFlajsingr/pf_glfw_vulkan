//
// Created by petr on 12/5/20.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_PIPELINE_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_PIPELINE_H

#include "VulkanObject.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {
class PF_GLFW_VULKAN_EXPORT Pipeline : public VulkanObject {
 public:
  explicit Pipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&pipelineLayout);

  Pipeline(const Pipeline &other) = delete;
  Pipeline &operator=(const Pipeline &other) = delete;

  [[nodiscard]] const vk::Pipeline &getVkPipeline() const;
  [[nodiscard]] const vk::PipelineLayout &getVkPipelineLayout() const;

  const vk::Pipeline &operator*() const;
  vk::Pipeline const *operator->() const;

 private:
  vk::UniquePipeline vkPipeline;
  vk::UniquePipelineLayout vkLayout;
};
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_PIPELINE_H
