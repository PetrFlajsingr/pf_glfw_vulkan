//
// Created by petr on 12/5/20.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_COMPUTEPIPELINE_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_COMPUTEPIPELINE_H

#include "Pipeline.h"
#include <pf_common/concepts/PtrConstructible.h>

namespace pf::vulkan {
// TODO: fully implement
class PF_GLFW_VULKAN_EXPORT ComputePipeline : public Pipeline, public PtrConstructible<ComputePipeline> {
 public:
  ComputePipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&pipelineLayout);

  [[nodiscard]] std::string info() const override;
};
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_COMPUTEPIPELINE_H
