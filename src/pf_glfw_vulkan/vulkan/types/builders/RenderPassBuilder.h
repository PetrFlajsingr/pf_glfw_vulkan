//
// Created by petr on 9/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_BUILDERS_RENDERPASSBUILDER_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_BUILDERS_RENDERPASSBUILDER_H

#include "../fwd.h"
#include <map>
#include <optional>
#include <pf_glfw_vulkan/_export.h>
#include <utility>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class RenderPassBuilder;

namespace details {

class AttachmentDescriptionBuilder {
 public:
  explicit AttachmentDescriptionBuilder(std::string name, RenderPassBuilder &parent);

  AttachmentDescriptionBuilder &format(vk::Format format);
  AttachmentDescriptionBuilder &initialLayout(vk::ImageLayout layout);
  AttachmentDescriptionBuilder &finalLayout(vk::ImageLayout layout);
  AttachmentDescriptionBuilder &samples(vk::SampleCountFlagBits sampleCount);
  AttachmentDescriptionBuilder &loadOp(vk::AttachmentLoadOp attLoadOp);
  AttachmentDescriptionBuilder &storeOp(vk::AttachmentStoreOp attStoreOp);
  AttachmentDescriptionBuilder &stencilLoadOp(vk::AttachmentLoadOp stLoadOp);
  AttachmentDescriptionBuilder &stencilStoreOp(vk::AttachmentStoreOp stStoreOp);
  AttachmentDescriptionBuilder &flags(vk::AttachmentDescriptionFlagBits descFlags);
  RenderPassBuilder &attachmentDone();

 private:
  RenderPassBuilder &parent;
  vk::AttachmentDescription description;
  std::string name;
};

struct SubPassDependencyData {
  vk::SubpassDependency dependency;
  std::string srcSubpassName;
  std::string dstSubpassName;
};
struct SubPassData {
  vk::SubpassDescription description;
  std::vector<std::string> colorAttachmentNames;
  std::vector<std::string> inputAttachmentNames;
  std::vector<std::string> resolveAttachmentNames;
  std::vector<std::string> preserveAttachmentNames;
  std::vector<SubPassDependencyData> dependencies;
  std::optional<std::string> depthStencilAttachmentName;
};

class SubPassBuilder;
class SubPassDependencyBuilder {
 public:
  explicit SubPassDependencyBuilder(SubPassBuilder &parent);

  SubPassDependencyBuilder &srcSubpass(std::string name = "");
  SubPassDependencyBuilder &dstSubpass(std::string name);
  SubPassDependencyBuilder &srcStageMask(const vk::PipelineStageFlags &stageFlags);
  SubPassDependencyBuilder &dstStageMask(const vk::PipelineStageFlags &stageFlags);
  SubPassDependencyBuilder &srcAccessFlags(const vk::AccessFlags &accessFlags);
  SubPassDependencyBuilder &dstAccessFlags(const vk::AccessFlags &accessFlags);

  SubPassBuilder &dependencyDone();

 private:
  SubPassDependencyData data;
  SubPassBuilder &parent;
};

class SubPassBuilder {
  friend class SubPassDependencyBuilder;

 public:
  explicit SubPassBuilder(std::string name, RenderPassBuilder &parent);

  SubPassBuilder &flags(const vk::SubpassDescriptionFlags &flags_);
  SubPassBuilder &colorAttachment(std::string attachmentName);
  SubPassBuilder &inputAttachment(std::string attachmentName);
  SubPassBuilder &depthStencilAttachment(std::string attachmentName);
  SubPassBuilder &resolveAttachment(std::string attachmentName);
  SubPassBuilder &preserveAttachment(std::string attachmentName);
  SubPassBuilder &pipelineBindPoint(vk::PipelineBindPoint bindPoint);
  SubPassDependencyBuilder dependency();
  RenderPassBuilder &subpassDone();

 private:
  SubPassData data;
  std::string name;
  RenderPassBuilder &parent;
};

}// namespace details

class PF_GLFW_VULKAN_EXPORT RenderPassBuilder {
  friend class details::AttachmentDescriptionBuilder;
  friend class details::SubPassBuilder;
  friend class RenderPass;

 public:
  explicit RenderPassBuilder(std::shared_ptr<LogicalDevice> device);
  details::AttachmentDescriptionBuilder attachment(std::string name);
  details::SubPassBuilder subpass(std::string name);

  [[nodiscard]] std::shared_ptr<RenderPass> build();

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  std::pair<std::vector<std::string>, vk::UniqueRenderPass> build(pf::vulkan::LogicalDevice &device);

  std::map<std::string, vk::AttachmentDescription> attachDescriptions;
  std::map<std::string, details::SubPassData> subpasses;

  std::optional<uint32_t> getSubpassIdx(const std::string &name);
};

}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_BUILDERS_RENDERPASSBUILDER_H
