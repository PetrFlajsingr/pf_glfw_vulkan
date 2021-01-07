//
// Created by petr on 12/5/20.
//

#include "ComputePipeline.h"

namespace pf::vulkan {
ComputePipeline::ComputePipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&pipelineLayout)
    : Pipeline(std::move(pipeline), std::move(pipelineLayout)) {}

std::string ComputePipeline::info() const { return "Compute pipeline"; }
}// namespace pf::vulkan