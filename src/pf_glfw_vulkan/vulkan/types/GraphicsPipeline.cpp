//
// Created by petr on 9/28/20.
//

#include "GraphicsPipeline.h"

namespace pf::vulkan {
GraphicsPipeline::GraphicsPipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&layout,
                                   std::shared_ptr<RenderPass> pass)
    : Pipeline(std::move(pipeline), std::move(layout)), renderPass(std::move(pass)) {}

std::string GraphicsPipeline::info() const { return "Vulkan graphics pipeline unique"; }

RenderPass &GraphicsPipeline::getRenderPass() const { return *renderPass; }

}// namespace pf::vulkan