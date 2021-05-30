//
// Created by petr on 10/18/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_LOGICALDEVICE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_LOGICALDEVICE_H

#include "VulkanObject.h"
#include "configs/BufferConfig.h"
#include "configs/CommandPoolConfig.h"
#include "configs/DescriptorPoolConfig.h"
#include "configs/DescriptorSetLayoutConfig.h"
#include "configs/FenceConfig.h"
#include "configs/ImageConfig.h"
#include "configs/LogicalDeviceConfig.h"
#include "configs/ShaderConfigs.h"
#include "configs/SwapChainConfig.h"
#include "configs/TextureConfigs.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <string>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT LogicalDevice : public VulkanObject,
                                            public PtrConstructible<LogicalDevice>,
                                            public std::enable_shared_from_this<LogicalDevice> {
 public:
  LogicalDevice(const std::shared_ptr<PhysicalDevice> &device, vk::UniqueDevice &&vkLogicalDevice,
                std::unordered_map<vk::QueueFlagBits, uint32_t> queueIndices,
                const std::optional<uint32_t> &presentQueueIndex);

  LogicalDevice(const LogicalDevice &other) = delete;
  LogicalDevice &operator=(const LogicalDevice &other) = delete;

  [[nodiscard]] const vk::Device &getVkLogicalDevice() const;
  [[nodiscard]] std::unordered_map<vk::QueueFlagBits, uint32_t> &getQueueIndices();
  [[nodiscard]] vk::Queue getQueue(vk::QueueFlagBits type);
  [[nodiscard]] vk::Queue getPresentQueue();
  [[nodiscard]] const std::optional<uint32_t> &getPresentQueueIndex() const;

  const vk::Device &operator*() const;
  vk::Device const *operator->() const;

  [[nodiscard]] std::shared_ptr<ImageUnique> createImage(ImageConfig &&config);
  [[nodiscard]] std::shared_ptr<SwapChain> createSwapChain(std::shared_ptr<Surface> surface, SwapChainConfig &&config);
  [[nodiscard]] std::shared_ptr<CommandPool> createCommandPool(CommandPoolConfig &&config);
  [[nodiscard]] std::shared_ptr<DescriptorSetLayout> createDescriptorSetLayout(DescriptorSetLayoutConfig &&config);

  [[nodiscard]] std::shared_ptr<Shader> createShader(ShaderConfigFile &&config);
  [[nodiscard]] std::shared_ptr<Shader> createShader(ShaderConfigSrc &&config);
  [[nodiscard]] std::shared_ptr<Shader> createShader(ShaderConfigGlslSrc &&config);
  [[nodiscard]] std::shared_ptr<Shader> createShader(ShaderConfigGlslFile &&config);

  [[nodiscard]] std::shared_ptr<DescriptorPool> createDescriptorPool(DescriptorPoolConfig &&config);
  [[nodiscard]] std::shared_ptr<Fence> createFence(FenceConfig &&config);
  [[nodiscard]] std::shared_ptr<Semaphore> createSemaphore();
  [[nodiscard]] std::shared_ptr<Buffer> createBuffer(BufferConfig &&config, bool allocateImmediately = true);
  [[nodiscard]] std::shared_ptr<Texture> createTexture(FileTextureConfig &&config, CommandPool &commandPool);

  [[nodiscard]] PhysicalDevice &getPhysicalDevice() const;

  void wait();

  std::string info() const override;

 private:
  std::weak_ptr<PhysicalDevice> physDevice;
  vk::UniqueDevice vkLogicalDevice;
  std::unordered_map<vk::QueueFlagBits, uint32_t> queueIndices;
  std::optional<uint32_t> presentQueueIndex;
};
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_LOGICALDEVICE_H
