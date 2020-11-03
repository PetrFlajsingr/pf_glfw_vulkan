//
// Created by petr on 9/28/20.
//

#ifndef VOXEL_RENDER_GRAPHICSPIPELINE_H
#define VOXEL_RENDER_GRAPHICSPIPELINE_H

#include <pf_common/concepts/PtrConstructible.h>
#include "VulkanObject.h"
#include "fwd.h"
#include <vulkan/vulkan.hpp>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT GraphicsPipeline : public VulkanObject, public PtrConstructible<GraphicsPipeline> {
 public:
  // TODO: builder only
  explicit GraphicsPipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&layout,
                            std::shared_ptr<RenderPass> pass);

  GraphicsPipeline(const GraphicsPipeline &other) = delete;
  GraphicsPipeline &operator=(const GraphicsPipeline &other) = delete;

  [[nodiscard]] const vk::Pipeline &getVkPipeline() const;
  [[nodiscard]] const vk::PipelineLayout &getVkPipelineLayout() const;
  [[nodiscard]] RenderPass &getRenderPass() const;

  const vk::Pipeline &operator*() const;
  vk::Pipeline const *operator->() const;

  [[nodiscard]] std::string info() const override;

 private:
  vk::UniquePipeline vkPipeline;
  vk::UniquePipelineLayout vkLayout;
  std::shared_ptr<RenderPass> renderPass;
};

}// namespace pf::vulkan
#endif//VOXEL_RENDER_GRAPHICSPIPELINE_H
