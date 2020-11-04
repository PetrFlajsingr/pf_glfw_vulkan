//
// Created by petr on 10/18/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_COMMANDBUFFER_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_COMMANDBUFFER_H

#include "VulkanObject.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT CommandBufferConfig {
  vk::CommandBufferLevel level;
  uint32_t count;
};

struct PF_GLFW_VULKAN_EXPORT ClearFrameBuffersCommand {
  RenderPass &renderPass;
  FrameBuffer &frameBuffer;
  std::vector<vk::ClearValue> clearValues;
  vk::Extent2D extent;
};

struct PF_GLFW_VULKAN_EXPORT DrawCommand {
  uint32_t vertexCount;
  uint32_t instanceCount;
  uint32_t vertexOffset;
  uint32_t instanceOffset;
};

class PF_GLFW_VULKAN_EXPORT CommandBufferRecording {
 public:
  explicit CommandBufferRecording(CommandBuffer &buffer);
  CommandBufferRecording(const CommandBufferRecording &) = delete;
  CommandBufferRecording &operator=(const CommandBufferRecording &) = delete;
  CommandBufferRecording(CommandBufferRecording &&other) noexcept;
  CommandBufferRecording &operator=(CommandBufferRecording &&other) noexcept;
  ~CommandBufferRecording();

  CommandBufferRecording &beginRenderPass(ClearFrameBuffersCommand &&cmd);
  CommandBufferRecording &endRenderPass();
  [[nodiscard]] CommandBuffer &getCommandBuffer();

  CommandBufferRecording &bindPipeline(vk::PipelineBindPoint bindPoint, GraphicsPipeline &pipeline);
  CommandBufferRecording &draw(DrawCommand &&cmd);

  CommandBufferRecording &copyBuffer(Buffer &src, Buffer &dst, vk::DeviceSize srcOffset,
                                     vk::DeviceSize dstOffset, vk::DeviceSize range);
  CommandBufferRecording &copyBufferToImage(Buffer &src, Image &dst, vk::DeviceSize srcOffset,
                                            uint32_t srcRowLength, uint32_t srcHeight,
                                            vk::Offset3D dstOffset,
                                            const vk::ImageSubresourceLayers &imageSubresourceLayers);

  CommandBufferRecording &pipelineBarrier(vk::PipelineStageFlagBits srcStage,
                                          vk::PipelineStageFlagBits dstStage,
                                          const std::vector<vk::MemoryBarrier> &memoryBarrier,
                                          const std::vector<vk::BufferMemoryBarrier> &bufferBarrier,
                                          const std::vector<vk::ImageMemoryBarrier> &imageBarrier);

  void end();

 private:
  bool isValid = true;
  std::reference_wrapper<CommandBuffer> owner;
};

struct PF_GLFW_VULKAN_EXPORT CommandSubmitConfig {
  std::vector<std::reference_wrapper<Semaphore>> waitSemaphores;
  std::vector<std::reference_wrapper<Semaphore>> signalSemaphores;
  vk::PipelineStageFlags flags;
  std::optional<std::reference_wrapper<Fence>> fence;
  bool wait;
};

class PF_GLFW_VULKAN_EXPORT CommandBuffer : public VulkanObject, public PtrConstructible<CommandBuffer> {
 public:
  friend class CommandBufferRecording;
  explicit CommandBuffer(std::shared_ptr<CommandPool> pool, vk::UniqueCommandBuffer &&buffer);

  CommandBuffer(const CommandBuffer &other) = delete;
  CommandBuffer &operator=(const CommandBuffer &other) = delete;

  CommandBufferRecording begin(vk::CommandBufferUsageFlagBits flag);
  [[nodiscard]] CommandPool &getCommandPool();

  [[nodiscard]] const vk::CommandBuffer &getVkBuffer() const;

  const vk::CommandBuffer &operator*() const;
  vk::CommandBuffer const *operator->() const;

  [[nodiscard]] std::string info() const override;

  void submit(CommandSubmitConfig &&config);

 private:
  vk::UniqueCommandBuffer vkBuffer;
  std::shared_ptr<CommandPool> commandPool;
  bool isRecording = false;
};
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_COMMANDBUFFER_H
