//
// Created by petr on 9/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_GRAPHICSPIPELINE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_GRAPHICSPIPELINE_H

#include "Pipeline.h"
#include <pf_common/concepts/PtrConstructible.h>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT GraphicsPipeline : public Pipeline,
                                               public PtrConstructible<GraphicsPipeline> {
 public:
  // TODO: builder only
  explicit GraphicsPipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&layout,
                            std::shared_ptr<RenderPass> pass);

  GraphicsPipeline(const GraphicsPipeline &other) = delete;
  GraphicsPipeline &operator=(const GraphicsPipeline &other) = delete;
  [[nodiscard]] RenderPass &getRenderPass() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<RenderPass> renderPass;
};

}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_GRAPHICSPIPELINE_H
