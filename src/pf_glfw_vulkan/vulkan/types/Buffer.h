//
// Created by petr on 10/19/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_BUFFER_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_BUFFER_H

#include "BufferMapping.h"
#include "VulkanObject.h"
#include "configs/BufferConfig.h"
#include "configs/BufferViewConfig.h"
#include "fwd.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT Buffer : public VulkanObject,
                                     public PtrConstructible<Buffer>,
                                     public std::enable_shared_from_this<Buffer> {
 public:
  Buffer(std::shared_ptr<LogicalDevice> device, BufferConfig &&config, bool allocateImmediately = false);

  void allocate();

  [[nodiscard]] const LogicalDevice &getLogicalDevice() const;
  [[nodiscard]] vk::DeviceSize getSize() const;
  [[nodiscard]] const vk::BufferUsageFlags &getUsageFlags() const;
  [[nodiscard]] vk::SharingMode getSharingMode() const;
  [[nodiscard]] const vk::Buffer &getVkBuffer() const;
  [[nodiscard]] const vk::DeviceMemory &getMemory() const;

  const vk::Buffer &operator*() const;
  vk::Buffer const *operator->() const;

  [[nodiscard]] bool isAllocated() const;

  [[nodiscard]] std::shared_ptr<BufferView> createView(BufferViewConfig &&config);
  [[nodiscard]] std::shared_ptr<BufferMemoryPool> createMemoryPool(BufferMemoryPoolConfig &&config);
  [[nodiscard]] BufferMapping mapping(vk::DeviceSize offset = 0);
  [[nodiscard]] BufferMapping mapping(vk::DeviceSize offset, vk::DeviceSize range);
  [[nodiscard]] std::shared_ptr<BufferMapping> mappingShared(vk::DeviceSize offset = 0);
  [[nodiscard]] std::shared_ptr<BufferMapping> mappingShared(vk::DeviceSize offset, vk::DeviceSize range);

  [[nodiscard]] std::string info() const override;

 private:
  uint32_t findMemoryType(uint32_t memoryTypeBits);

  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::DeviceSize size;
  vk::BufferUsageFlags usageFlags;
  vk::SharingMode sharingMode;

  bool isAllocated_ = false;

  vk::UniqueDeviceMemory vkMemory;
  vk::UniqueBuffer vkBuffer;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_BUFFER_H
