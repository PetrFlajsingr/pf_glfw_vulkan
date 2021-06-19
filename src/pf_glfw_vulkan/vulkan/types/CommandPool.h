//
// Created by petr on 9/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_COMMANDPOOL_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_COMMANDPOOL_H

#include "VulkanObject.h"
#include "configs/CommandBufferConfig.h"
#include "configs/CommandPoolConfig.h"
#include "fwd.h"
#include <optional>
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

// TODO: join flags with semaphores to array of pairs or smt
struct PF_GLFW_VULKAN_EXPORT MultiCommandSubmitConfig {
  std::vector<std::reference_wrapper<CommandBuffer>> commandBuffers;
  std::vector<std::reference_wrapper<Semaphore>> waitSemaphores;
  std::vector<std::reference_wrapper<Semaphore>> signalSemaphores;
  std::vector<vk::PipelineStageFlags> flags;
  std::optional<std::reference_wrapper<Fence>> fence;
  bool wait;
};

class PF_GLFW_VULKAN_EXPORT CommandPool : public VulkanObject,
                                          public PtrConstructible<CommandPool>,
                                          public std::enable_shared_from_this<CommandPool> {
 public:
  explicit CommandPool(std::shared_ptr<LogicalDevice> device, CommandPoolConfig &&config);

  CommandPool(const CommandPool &other) = delete;
  CommandPool &operator=(const CommandPool &other) = delete;

  [[nodiscard]] std::vector<std::shared_ptr<CommandBuffer>> createCommandBuffers(const CommandBufferConfig &config);

  void submitCommandBuffers(const MultiCommandSubmitConfig &config);

  [[nodiscard]] const vk::CommandPool &getCommandPool() const;

  const vk::CommandPool &operator*() const;
  vk::CommandPool const *operator->() const;

  [[nodiscard]] LogicalDevice &getDevice() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::UniqueCommandPool vkCommandPool;
  vk::Queue queue;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_COMMANDPOOL_H
