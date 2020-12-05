//
// Created by petr on 12/5/20.
//

#include "Pipeline.h"

namespace pf::vulkan {
Pipeline::Pipeline(vk::UniquePipeline &&pipeline, vk::UniquePipelineLayout &&pipelineLayout)
    : vkPipeline(std::move(pipeline)), vkLayout(std::move(pipelineLayout)) {}

const vk::Pipeline &Pipeline::getVkPipeline() const { return *vkPipeline; }

const vk::Pipeline &Pipeline::operator*() const { return *vkPipeline; }

vk::Pipeline const *Pipeline::operator->() const { return &*vkPipeline; }

const vk::PipelineLayout &Pipeline::getVkPipelineLayout() const { return *vkLayout; }
}// namespace pf::vulkan